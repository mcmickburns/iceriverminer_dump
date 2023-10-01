#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <ctype.h>
#include <jansson.h>

 
#define STR_VALUE(val) #val
#define STR(name) STR_VALUE(name)

#define PATH_LEN 256
#define MD5_LEN 32



#if JANSSON_MAJOR_VERSION >= 2
#define JSON_LOADS(str, err_ptr) json_loads((str), 0, (err_ptr))
#define JSON_LOADF(str, err_ptr) json_load_file((str), 0, (err_ptr))
#else
#define JSON_LOADS(str, err_ptr) json_loads((str), (err_ptr))
#define JSON_LOADF(str, err_ptr) json_load_file((str), (err_ptr))
#endif


#define B2STR(B) (B)?"true":"false"


static char* sendMessage(char* buf, int bufSize, char* readBuff, int readBuffSize);
static char* sendLogMessage(char *buf, int bufSize, char *readBuff, int readBuffSize, int isCurrent, int *historyCount, int *logBuffSize);
 


void copyfile(char* file, char* dest, char* destFileName);
int check_dest(char* d);

char *rtrim(char *str);
char *ltrim(char *str);
char *trim(char *str);
char *toupperStr(char *str);

 
 

short PORT = 4111; 
char* IP = "127.0.0.1";
// char* IP = "192.168.1.124";
// char* IP = "192.168.1.33";


static char* sendMessage(char* buf, int bufSize, char* readBuff, int readBuffSize){
 
	// typedef struct sockaddr SA;

	 
	int	rv = -1;
	
	// print("sendMessage 11");
 
	
	int	sockfd = -1;
	sockfd = socket(AF_INET, SOCK_STREAM, SOL_TCP);
	if (sockfd == -1)
	{
		printf("socket create error:%s \n", strerror(errno));
		return "Create failed!";
	}
 
 
	// struct sockaddr_in addr;
	// addr.sin_family = AF_INET;
	// addr.sin_port = htons(PORT);
	// addr.sin_addr.s_addr = inet_addr(IP);
	
	struct sockaddr_in  ServerAddr = 
	{ 
		.sin_family = AF_INET , // 地址族  IPV4 协议
		.sin_port = htons(PORT) , // 端口   htons 把本地字节序的 65000 转换为网络字节序 
		.sin_addr.s_addr =  inet_addr(IP)   // IPV4 地址 inet_addr把字符串 "192.168.9.2" 转换成 网络字节序的二进制地址
	};
	
	// printf("sendMessage 111\n");
	// if(connect( sockfd, (struct sockaddr *) &ServerAddr, addrlen))
	if(connect( sockfd, (struct sockaddr *) &ServerAddr, sizeof(ServerAddr)))
	// if(connect(sockfd, (SA*)&addr, sizeof(addr)) == -1)
	{
		printf("socket connect error:%s \n", strerror(errno));
	   return "Connect failed!";
	}
 
	// printf("sendMessage 222\n");
	
	printf("socket[%d] send %d Byte data to server: %s\n\n",sockfd, bufSize, buf);
	
	send(sockfd, buf, bufSize, 0);
 
	// printf("Data sent.\n");

    fd_set readfds;
    struct timeval timeout;
    int ret;

    FD_ZERO(&readfds);
    FD_SET(sockfd, &readfds);

    timeout.tv_sec = 60;
    timeout.tv_usec = 0;
	
	// printf("sendMessage 331\n");
	
	while (1)
	{
		
		// printf("sendMessage 332\n");
		ret = select(sockfd+1, &readfds, NULL, NULL, &timeout);  // 设置超时时间
		if (ret == -1) {  // select失败
			printf("Error in select: %s\n", strerror(errno));
			close(sockfd);
			return "Error in select!";
		} else if (ret == 0) {  // 超时
			printf("Timeout while waiting for data.\n");
			close(sockfd);
			return "Read timeout!";
		}
		
		// printf("sendMessage 333\n");
		rv = read(sockfd, readBuff, readBuffSize);
		// printf("sendMessage 444\n");
		
		if (rv < 0)
		{
			printf("read date from server failure: %s\n", strerror(errno));
		}
		else if (rv == 0)
		{
			printf("socket[%d] get Disconnected\n", sockfd);
		}
		else if (rv > 0)
		{
			printf("socket[%d] read %d Byte data from server: %s\n\n",sockfd, rv, readBuff);
		}
 
 
		break;
 
	}
	
	
	close(sockfd);



	return "success";
	
}




int logSockfd = -1;
static char* sendLogMessage(char *buf, int bufSize, char *readBuff, int readBuffSize, int isCurrent, int *historyCount, int *logBuffSize){

	int	rv = -1;
	
	if(*historyCount == 1 || isCurrent == 1)
	{
		typedef struct sockaddr SA;	
		logSockfd = socket(AF_INET, SOCK_STREAM, 0);
		
		struct sockaddr_in addr;


		addr.sin_family = AF_INET;
		addr.sin_port = htons(PORT);
		addr.sin_addr.s_addr = inet_addr(IP);
		 
		if(connect(logSockfd, (SA*)&addr, sizeof(addr)) == -1){
		   return "connect failed!";
		}
		
		send(logSockfd, buf, bufSize, 0);
		printf("sendLogMessage first send isCurrent:%d. \n", isCurrent);
	}
 
	int totalbyte = 0;

	// printf("sendLogMessage 2\n");
	
	int count = 1;
	char tmpReadBuff[readBuffSize];
	memset(tmpReadBuff, 0, sizeof(tmpReadBuff)/sizeof(char));
	
	
	// char* tmpReadBuff = malloc((int)readBuffSize);
	 
	double len = 1024.0;
	rv = read(logSockfd, (char*)tmpReadBuff, readBuffSize);
	
	// printf("sendLogMessage first count:%d, rv:%d:%ld\n", count++, rv, strlen(tmpReadBuff));
 
	if (rv < 0)
	{
		printf("first read date from server failure: %s\n", strerror(errno));
	}
	else if (rv == 0)
	{
		printf("socket[%d] get Disconnected\n", logSockfd);
	}
	else if (rv > 0)
	{
		// {"id":"log", "ret":{"code":0, "ctime": "2023-02-23 11:09:22", "mtime": "2023-02-23 11:09:22", "len": 602939}}
		
		strcat(readBuff, (char*)tmpReadBuff);
		memset(tmpReadBuff, 0 ,sizeof(tmpReadBuff)/sizeof(char));
		
		printf("socket[%d] first read %d Byte data from server: %s\n\n",logSockfd, rv, readBuff);
	
		json_error_t err;
		json_t *jst, *ret;
		
		jst = JSON_LOADS((const char*)readBuff, &err);
		
		ret = json_object_get(jst, "ret");
		
		len = json_number_value(json_object_get(ret, "len"));	
		printf("init logBuff len: %d\n",(int)len);
	}
 
	char* logBuff = malloc((int)len);
 
	int round = (int)len / 1024;
	int perLogCount = round / 5;// 控制最多只打印10次
	if (perLogCount < 1)
	{
		perLogCount = 1;
	}
	
	while (1)
	{
		// if ((int)len < readBuffSize)
		// {
			// readBuffSize = (int)len;
		// }			
		
		rv = read(logSockfd, (char*)tmpReadBuff, readBuffSize);
		
		if(count % perLogCount  == 1 ) // || rv < readBuffSize
		{
			printf("read count:%d, rv:%d:%d, last totalbyte:%d\n", count, rv, strlen(tmpReadBuff), totalbyte);
		}
		

		if (rv < 0)
		{
			printf("read date from server failure: %s\n", strerror(errno));
			memset(tmpReadBuff, 0, sizeof(tmpReadBuff)/sizeof(char));
			if(count > 1000)
			{
				break;
			}
		}
		else if (rv == 0)
		{
			printf("socket[%d] get Disconnected\n", logSockfd);
			memset(tmpReadBuff, 0, sizeof(tmpReadBuff)/sizeof(char));
			if(count > 1000)
			{
				break;
			}
		}
		else if (rv > 0)
		{
			 
			// strcat(logBuff, tmpReadBuff);
			memcpy(&logBuff[totalbyte], tmpReadBuff, rv);
			totalbyte += rv;
			memset(tmpReadBuff, 0, sizeof(tmpReadBuff)/sizeof(char));
			 
		}
  
		// libserver 每次1024的转过来
		if(rv < 0 || totalbyte >= len)  //|| rv < readBuffSize
		{
			printf("break count:%d, rv:%d, readBuffSize:%d, totalbyte:%d\n",count, rv, readBuffSize, totalbyte);
			
			break;
		}
 
		count++;
	}
	
 
	*logBuffSize = totalbyte;
	
	printf("socket[%d] historyCount:%d, total totalbyte:%d, logBuffSize:%d, strlen(logBuff):%d Byte data from server: %.32s \n\n", 
	logSockfd, *historyCount, totalbyte, *logBuffSize, strlen(logBuff), logBuff);
	
	if(isCurrent == 1 || *historyCount == 3){
		printf("socket[%d] close\n",logSockfd);
		close(logSockfd);
		logSockfd = -1;
	}
	
	*historyCount = *historyCount + 1;
	

	// return "success";
	return logBuff;
	
}


 


//去除尾部空白字符 包括\t \n \r 
/* 标准的空白字符包括： ' ' (0x20) space (SPC) 空格符 '\t' (0x09) horizontal tab (TAB) 水平制表符 '\n' (0x0a) newline (LF) 换行符 '\v' (0x0b) vertical tab (VT) 垂直制表符 '\f' (0x0c) feed (FF) 换页符 '\r' (0x0d) carriage return (CR) 回车符 //windows \r\n linux \n mac \r */
char *rtrim(char *str)
{
    if (str == NULL || *str == '\0')
    {
        return str;
    }
    int len = strlen(str);
    char *p = str + len - 1;
    while (p >= str  && isspace(*p))
    {
        *p = '\0';
        --p;
    }
    return str;
}
//去除首部空格
char *ltrim(char *str)
{
    if (str == NULL || *str == '\0')
    {
        return str;
    }
    int len = 0;
    char *p = str;
    while (*p != '\0' && isspace(*p))
    {
        ++p;
        ++len;
    }
    memmove(str, p, strlen(str) - len + 1);
    return str;
}
//去除首尾空格
char *trim(char *str)
{
    str = rtrim(str);
    str = ltrim(str);
    return str;
}


// 根据输入 hashrateStr ： 120G ， 300T， 这样的字符串，转换算力或计算次数单位
// char gethash(char *hashrateStr, int unitType, int round, char *placeholder, double hashrate_h, char *unit2){
	
	// hashrate_h = 0.0; 
	// char *hashrateHStr = "";
	// int unitindex = 0;
	
	// memcpy((char *)unit2, "H", 1);
	// if(strchr(toupperStr(hashrateStr), "E") != NULL)
	// {
		// memcpy((char *)unit2, "E", 1);
		// unitindex = 6;
	// }
	// else if(strchr(toupperStr(hashrateStr), "P") != NULL)
	// {
		// memcpy((char *)unit2, "P", 1);
		// unitindex = 5;
	// }
	// else if(strchr(toupperStr(hashrateStr), "T") != NULL)
	// {
		// memcpy((char *)unit2, "T", 1);
		// unitindex = 4;
	// }
	// else if(strchr(toupperStr(hashrateStr), "G") != NULL)
	// {
		// memcpy((char *)unit2, "G", 1);
		// unitindex = 3;
	// }
	// else if(strchr(toupperStr(hashrateStr), "M") != NULL)
	// {
		// memcpy((char *)unit2, "M", 1);
		// unitindex = 2;
	// }
	// else if(strchr(toupperStr(hashrateStr), "K") != NULL)
	// {
		// memcpy((char *)unit2, "K", 1);
		// unitindex = 1;
	// }
	// else
	// {
		// memcpy(unit2, "H", 1);
		// unitindex = 0;
	// }
// }

char *toupperStr(char *str)
{
	int ii;
	for (ii = 0; ii < strlen(str); ii++)
	{
		str[ii] = toupper(str[ii]);
	}
	
	return str;
}

 
int check_dest(char* d) {
	struct stat m;
	stat(d, &m);
	if ((m.st_mode & S_IFMT) == S_IFDIR || (m.st_mode & S_IFMT) == S_IFCHR) {
		return 1;
	}
	return 0;
}
 
// file 原文件路径； dest 目标目录
void copyfile(char* file, char* dest, char* destFileName) 
{
	
	printf("copyfile start\n");
	
	if (check_dest(dest) == 0) 
	{
		printf("destination is invalid");
		return;
	}
	
	printf("dest dir OK :%s \n", dest);
	
		
	if (access(file, F_OK) == 0)
    {
        printf("file:%s exists.\n", file);
    }
    else
    {
        printf("file:%s not exists.\n", file);
    }
 
	// char* newFile = (char*)malloc(sizeof(char)); 
	char newFile[1000];
	
	strcpy(newFile, dest);
	
	// printf("newFile 1:%s \n", newFile);
	
	strcat(newFile, "/");
	
	// printf("newFile 2:%s \n", newFile);
	
	strcat(newFile, destFileName);
	printf("newFile 3:%s \n", newFile);
	
	
	int f1 = open(file, O_RDONLY);
	if (f1 < 0) 
	{
		printf("open file %s failed\n", file);
		return;
	}


	int f2 = open(newFile, O_WRONLY | O_CREAT);
	if (f2 < 0) 
	{
		printf("create file %s failed\n", newFile);
		return;
	}
	
	// char buf[1024] = { '\0' };
	// int sz = read(f1, buf, 1024);
	// buf[sz] = '\0';
	// write(f2, buf, strlen(buf));
	
	// char *buffer = (char*)malloc(sizeof(char));
	char buffer[1024];
	
    int slen = 0;
	int bsize = sizeof(buffer);
    int k;
    do{
        memset(buffer,0 , bsize);
        k = read(f1,buffer,1024);
        if(k <= 0) break;
        write(f2,buffer,k);
        //printf("k = %d\tbuffer = %s\n",k,buffer);
        slen = slen + k;
		
    }while(k > 0);
 
	 
	close(f1);
	close(f2);
	
	 
	/*
	// 这个测试过也可以复制
	FILE *f1,*f2;
	f1 = fopen(file,"rb");
	f2 = fopen(newFile,"wb");
	
	if(f1 == NULL) {
        printf("open file %s failed\n", file);
		return;
    }
    if(f2 == NULL) {
        printf("create file %s failed\n", newFile);
		return;
    }
	
	void *buffer = (void *)malloc(2);
    int slen = 0;
    while(1) {
        int op = fread(buffer,1,1,f1);
        if(op <= 0) break;
        fwrite(buffer,1,1,f2);
        slen++;
    }
    free(buffer);
    fclose(f1);
    fclose(f2);
 */
  
	printf("copy file %s (%d bytes)to %s successfully\n", file, slen, newFile);
	
}
 


int CalcFileMD5(char *file_name, char *md5_sum)
{
    #define MD5SUM_CMD_FMT "md5sum %." STR(PATH_LEN) "s 2>/dev/null"
    char cmd[PATH_LEN + sizeof (MD5SUM_CMD_FMT)];
    sprintf(cmd, MD5SUM_CMD_FMT, file_name);
    #undef MD5SUM_CMD_FMT

    FILE *p = popen(cmd, "r");
    if (p == NULL) return 0;

    int i, ch;
    for (i = 0; i < MD5_LEN && isxdigit(ch = fgetc(p)); i++) {
        *md5_sum++ = ch;
    }

    *md5_sum = '\0';
    pclose(p);
    return i == MD5_LEN;
}





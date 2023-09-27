#include    "esp.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
 
#include "utils.h"

static void loginPage(HttpConn *conn, EspAction *action)
{ 
 
	
	// const char* language ;
	// language = espGetCookie(conn, "language"); 
	
	// if(language != NULL && strcmp("en", language) == 0){
		// espRenderView(conn, "login_en.esp", 0);
	// }else{
		// espRenderView(conn, "login.esp", 0);
	// }
		
	espRenderView(conn, "login.esp", 0);
	

}


static void login(HttpConn *conn, EspAction *action)
{
	const char* userName; 
	const char* userPwd;
	userName = param ("user");
	userPwd = param ("pwd");
	
	// char* out = (char*)malloc(sizeof(char) * 64) ; 
	// sprintf(out, "{\"error\":1,\"data\":{\"user\":\"%s\",\"pwd\":\"%s\"},\"message\":\"timeout\"}", userName, userPwd); 
	// render(out);
    
	char buf[1024]={0};
	char out[8192]={0};
	char output[2048]={0};
 
	sprintf((char*)buf, "{\"id\":\"login\",\"user\":\"%s\",\"pass\":\"%s\"}\n", userName, userPwd); 
	
	
	// render((const char*)buf);
	
/*	 
	short PORT = 4111;
	int	rv = -1;
	
	// char* IP = "127.0.0.1";
	char* IP = "192.168.1.33";
	int sockfd;
	typedef struct sockaddr SA;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr(IP);
    if(connect(sockfd, (SA*)&addr, sizeof(addr)) == -1){
       // return "Connect failed!";
	   render("Connect failed!");
    }
 
	// memcpy(buf, "Hello World3\n", sizeof("Hello World3\n"));

	send(sockfd, buf, strlen(buf), 0);
*/	
	
	// js={"id": "login", "user": "asdfasd", "pwd": "asdf"}
	// send: {"id":"login","ret":{"code":1001,"msg":"user not exist"}}

	
	char* result ;
	result = sendMessage(buf, strlen(buf), (char*)(&out), sizeof(out));
	
	// render((const char*)out);
	
	
	if (strcmp("Create failed!", result) == 0 || strcmp("Connect failed!", result) == 0)
	{
		// isErr = 1;
		sprintf((char*)output, "{\"error\":1,\"data\":{\"user\":\"%s\",\"pwd\":\"%s\"},\"message\":\"Connect miner failed!\"}", userName, userPwd); 
	}
	else if( strcmp("Read timeout!", result) == 0 || strcmp("Error in select!", result) == 0 || strlen(out) == 0)
	{
		sprintf((char*)output, "{\"error\":2,\"data\":{\"user\":\"%s\",\"pwd\":\"%s\"},\"message\":\"Miner return failed!\"}", userName, userPwd); 
	}

	// char* out2 = (char*)malloc(strlen(out) - 1) ; 
	// memcpy(out2, out, strlen(out) - 1);
	
	json_error_t err;
	json_t *jst, *ret;
	jst = JSON_LOADS((const char*)out, &err);
	if(!jst)
    {
		sprintf((char*)output, "{\"error\":1,\"data\":{\"user\":\"%s\",\"pwd\":\"%s\"},\"message\":\"server return format error!\"}", userName, userPwd); 
	}
	

	// sprintf((char*)output, "%s:%ld", out, strlen(out));
	
	// memcpy(output, out, sizeof(out) - 2);
	// '{"id":"login","ret":{"code":0}}'.length 31
	// {"id":"login","ret":{"code":0}}
	// :32

	
	// render((const char*)out2);
	
	
	// {"id":"login","ret":{"code":1001,"msg":"user not exist"}}
	//  {"id":"login","ret":{"code":1002,"msg":"password error"}}
	// {"id":"login","ret":{"code":0}}
	
	const char *id, *msg;
	double code;
	id = json_string_value(json_object_get(jst, "id"));	
	// render(id);
	
	ret = json_object_get(jst, "ret");
	code = json_number_value(json_object_get(ret, "code"));	
	msg = json_string_value(json_object_get(ret, "msg"));	
	
	sprintf((char*)output, "{\"error\":%d,\"data\":{\"id\":\"%s\"},\"message\":\"%s\"}", (int)code, id, msg); 
	
	render((const char*)output);
	
	
	
}


static void userPanel(HttpConn *conn, EspAction *action)
{ 
	const char* post; 
	post = param ("post");
	
	
	if(post != NULL && strcmp("4", post) == 0)
	{
		//获取界面信息
		char buf[1024]={0};
		char out[81920]={0};
		char output[81920]={0};
		
		char outputData[8192]={0};
		char outputData2[8192]={0};
		
		
		// {"error":0,"message":"","data":{"model":"none","algo":"no","online":true,"firmver":"2010-07-21 16:35:03","firmtype":"Factory","rtpow":121000000000,"rtpow_hash":"121","rtpow_unit":"GH\/s","avgpow":110000000000,"avgpow_hash":"110","avgpow_unit":"GH\/s","reject":1.02,"runtime":"00:01:17:20","pows_unit":"GH\/s","pows":{"board1":[108,109,109,108,110,111,120,120,98,100,104,110,110,114]},"pows_x":["16:45","16:50","16:55","17:00","17:05","17:10","17:15","17:20","17:25","17:30","17:35","17:40","17:45","17:50"],"powstate":true,"netstate":true,"fanstate":true,"tempstate":false,"fans":[0,0,0,0],"pools":[{"no":1,"addr":"stratum.antpool.com:3333","user":"ccminer","pass":"123","connect":false,"diff":"","priority":1,"accepted":0,"rejected":0,"diffa":0,"diffr":0,"state":0,"lsdiff":0,"lstime":""},{"no":2,"addr":"stratum.antpool.com:443","user":"ccminer2","pass":"123","connect":false,"diff":"","priority":2,"accepted":0,"rejected":0,"diffa":0,"diffr":0,"state":0,"lsdiff":0,"lstime":""},{"no":3,"addr":"stratum.antpool.com:12","user":"ccminer3","pass":"123","connect":false,"diff":"","priority":3,"accepted":0,"rejected":0,"diffa":0,"diffr":0,"state":0,"lsdiff":0,"lstime":""}],"chainnum":0,"boards":[{"no":1,"chipnum":76,"error":0,"freq":660,"rtpow":"130G","idealpow":"141G","tempnum":"0","pcbtemp":"","intmp":59.12,"outtmp":61.38,"state":true,"false":[]},{"no":2,"chipnum":76,"error":0,"freq":660,"rtpow":"124G","idealpow":"141G","tempnum":"0","pcbtemp":"","intmp":55.22,"outtmp":58.17,"state":true,"false":[]},{"no":3,"chipnum":76,"error":0,"freq":660,"rtpow":"136G","idealpow":"141G","tempnum":"0","pcbtemp":"","intmp":60.22,"outtmp":62.05,"state":true,"false":[]}],"refTime":"2023-02-10 17:51:15"}}
		
		
		int isErr = 0;
		sprintf((char*)buf, "{\"id\":\"info\"}\n"); 
		char* result ;
		
		// print("sendMessage 1");
		 
		result = sendMessage(buf, strlen(buf), (char*)(&out), sizeof(out));
		if (strcmp("Create failed!", result) == 0 || strcmp("Connect failed!", result) == 0)
		{
			isErr = 1;
			sprintf((char*)output, "{\"error\":1,\"data\":{},\"message\":\"Connect miner failed!\"}"); 
		}
		else if( strcmp("Read timeout!", result) == 0 || strcmp("Error in select!", result) == 0 || strlen(out) == 0)
		{
			isErr = 1;
			sprintf((char*)output, "{\"error\":2,\"data\":{},\"message\":\"Miner return failed!\"}"); 
		}
		else
		{
			json_error_t err;
			json_t *jst, *ret;
			
			jst = JSON_LOADS((const char*)out, &err);
			
			ret = json_object_get(jst, "ret");
			
			const char *id, *msg;
			double code;
			 
			id = json_string_value(json_object_get(jst, "id"));	
			code = json_number_value(json_object_get(ret, "code"));	
			msg = json_string_value(json_object_get(jst, "msg"));	
			
			if(id == NULL)
			{
				isErr = 1;
				sprintf((char*)output, "{\"error\":3,\"data\":{},\"message\":\"Json decode fail!\"}"); 
			}
			else if((int)code == 0)
			{
				json_object_del(ret, "code");
				json_object_del(ret, "msg");
				void *iter;
				iter = json_object_iter((json_t *)ret);
				while(iter) 
				{
					const char *key;
					const json_t *value;
					key = json_object_iter_key(iter);
					value = json_object_iter_value(iter);
					
					if(key != NULL && strcmp("online", key) == 0)
					{
						sprintf((char*)outputData, "%s,\"%s\":%s", outputData, key, B2STR(json_is_true(value)));
						
					}
					else
					{
						sprintf((char*)outputData, "%s,\"%s\":\"%s\"", outputData, key, json_string_value(value));
					}
 
					iter = json_object_iter_next((json_t *)ret, iter);
					
				}
			}
			else
			{
				isErr = 1;
				sprintf((char*)output, "{\"error\":%d,\"data\":{\"id\":\"%s\"},\"message\":\"%s\"}", (int)code, id, msg); 
			}

			// sprintf((char*)output, "%s:%ld", out, strlen(out));
		}// end of info 基本信息
 	
	
		// getnet 获取IP配置
		if(isErr == 0)
		{
			memset(buf, 0, sizeof(buf)/sizeof(char));
			memset(out, 0 ,sizeof(out)/sizeof(char));
  

			sprintf((char*)buf, "{\"id\":\"getnet\"}\n"); 
			
			result = sendMessage(buf, strlen(buf), (char*)(&out), sizeof(out));
			
			// send: {"id":"getnet", "ret":{"code":0, "nic": "eth0", "mac":"1E:80:A7:59:F7:49", "ip": "192.168.1.99","netmask":"255.255.255.0", "host": "aminer", "dhcp": true, "gateway": "192.168.1.1", "dns": ""}}

			
			if (strcmp("Create failed!", result) == 0 || strcmp("Connect failed!", result) == 0)
			{
				isErr = 1;
				sprintf((char*)output, "{\"error\":1,\"data\":{},\"message\":\"Connect miner failed!\"}"); 
			}
			else if( strcmp("Read timeout!", result) == 0 || strcmp("Error in select!", result) == 0 || strlen(out) == 0)
			{
				isErr = 1;
				sprintf((char*)output, "{\"error\":2,\"data\":{},\"message\":\"Miner return failed!\"}"); 
			}
			else
			{
				json_error_t err;
				json_t *jst, *ret;
				const char *id, *msg;
				double code; 
				
				jst = JSON_LOADS((const char*)out, &err);
				id = json_string_value(json_object_get(jst, "id"));	
				ret = json_object_get(jst, "ret");
				code = json_number_value(json_object_get(ret, "code"));	
				msg = json_string_value(json_object_get(ret, "msg"));	
			 
				if(id == NULL)
				{
					isErr = 1;
					sprintf((char*)output, "{\"error\":3,\"data\":{},\"message\":\"Json decode fail!\"}"); 
				}
				else if((int)code == 0)
				{
					json_object_del(ret, "code");
					 void *iter;
					iter = json_object_iter((json_t *)ret);
					while(iter) 
					{
						const char *key;
						const json_t *value;
						key = json_object_iter_key(iter);
						value = json_object_iter_value(iter);
						
 
						if(key && strcmp("dhcp", key) == 0)
						{
							sprintf((char*)outputData, "%s,\"%s\":%s", outputData, key, B2STR(json_is_true(value)));
						}
						else
						{	
							sprintf((char*)outputData, "%s,\"%s\":\"%s\"", outputData, key, json_string_value(value));
						}
						
						iter = json_object_iter_next((json_t *)ret, iter);
					}
				}
				else
				{
					isErr = 1;
					sprintf((char*)output, "{\"error\":%d,\"data\":{\"id\":\"%s\"},\"message\":\"%s\"}", (int)code, id, msg); 
				}
			}
		}// end of getlocate 获取当前定位状态

		// getlocate 获取当前定位状态：
		if(isErr == 0)
		{
			memset(buf, 0, sizeof(buf)/sizeof(char));
			memset(out, 0 ,sizeof(out)/sizeof(char));
  

			sprintf((char*)buf, "{\"id\":\"getlocate\"}\n"); 
			
			result = sendMessage(buf, strlen(buf), (char*)(&out), sizeof(out));
			
			// send: {"id":"getlocate","ret":{"code":1005,"on":false}}
			
			if (strcmp("Create failed!", result) == 0 || strcmp("Connect failed!", result) == 0)
			{
				isErr = 1;
				sprintf((char*)output, "{\"error\":1,\"data\":{},\"message\":\"Connect miner failed!\"}"); 
			}
			else if( strcmp("Read timeout!", result) == 0 || strcmp("Error in select!", result) == 0 || strlen(out) == 0)
			{
				isErr = 1;
				sprintf((char*)output, "{\"error\":2,\"data\":{},\"message\":\"Miner return failed!\"}"); 
			}
			else
			{
				
				json_error_t err;
				json_t *jst, *ret, *on;
				
				jst = JSON_LOADS((const char*)out, &err);
				
				ret = json_object_get(jst, "ret");
				
				// const char *id, *msg;
				// double code;
				 
				// id = json_string_value(json_object_get(jst, "id"));	
				// code = json_number_value(json_object_get(ret, "code"));	
				// msg = json_string_value(json_object_get(jst, "msg"));	
				
				on = json_object_get(ret, "on");	
				 
				sprintf((char*)outputData, "%s,\"locate\":%s", outputData, B2STR(json_is_true(on)));
				
			}
		}// end of getlocate 获取当前定位状态
		
		
		// boardpow 算力
		if(isErr == 0)
		{
			memset(buf, 0, sizeof(buf)/sizeof(char));
			memset(out, 0 ,sizeof(out)/sizeof(char));
  

			sprintf((char*)buf, "{\"id\":\"boardpow\"}\n"); 
			
			result = sendMessage(buf, strlen(buf), (char*)(&out), sizeof(out));
			// send: {"id": "boardpow", "ret": {"code":0, "rtpow": "121G", "avgpow": "110G", "reject": 1.020000, "runtime": "00:01:17:20", "unit": "G", "pows": [108,109,109,108,110,111,120,120,98,100,104,110,110,114]}}

			if (strcmp("Create failed!", result) == 0 || strcmp("Connect failed!", result) == 0)
			{
				isErr = 1;
				sprintf((char*)output, "{\"error\":1,\"data\":{},\"message\":\"Connect miner failed!\"}"); 
			}
			else if( strcmp("Read timeout!", result) == 0 || strcmp("Error in select!", result) == 0 || strlen(out) == 0)
			{
				isErr = 1;
				sprintf((char*)output, "{\"error\":2,\"data\":{},\"message\":\"Miner return failed!\"}"); 
			}
			else
			{
				
				json_error_t err;
				json_t *jst, *ret;
				
				jst = JSON_LOADS((const char*)out, &err);
				
				ret = json_object_get(jst, "ret");
				
				const char *id, *msg;
				double code;
				 
				id = json_string_value(json_object_get(jst, "id"));	
				code = json_number_value(json_object_get(ret, "code"));	
				msg = json_string_value(json_object_get(ret, "msg"));		
				 
				// 看libserver code 只等于0
				if(id == NULL)
				{
					isErr = 1;
					sprintf((char*)output, "{\"error\":3,\"data\":{},\"message\":\"Json decode fail!\"}"); 
				}
				else if((int)code == 0)
				{
					json_object_del(ret, "code");
					void *iter;
					iter = json_object_iter((json_t *)ret);
					while(iter) 
					{
						const char *key;
						const json_t *value;
						key = json_object_iter_key(iter);
						value = json_object_iter_value(iter);
						
 
						if(key && strcmp("reject", key) == 0)
						{
							sprintf((char*)outputData, "%s,\"%s\":%f", outputData, key, json_number_value(value));
						}
						else if(key && strcmp("pows", key) == 0)
						{
							 
							char pows[10240]={0};
							char pows2[10240]={0};
							
							// 根据pows个数倒退时间x轴， 1个点5分钟
							char powsX[10240]={0};
							char powsX2[10240]={0};
							
							double powValue;
							int interval;
							size_t arrIndex;
							json_t *arrVal;
							
							// int powNum = json_array_size(value);
							// char timestr[6] = "";
							 
							// time_t now, thisMin, minSec;
							// struct tm *p;
							
							// now = time( 0 );
							// thisMin = now - now % 300;
					 

							json_array_foreach(value, arrIndex, arrVal) 
							{
								powValue = json_number_value(arrVal);
								sprintf((char*)pows, "%s%d,", pows, (int)powValue);
					
								interval = arrIndex * 5;
								
								// dzt20230526 不再显示时间， 改成显示时间间隔
								// minSec = thisMin - 300 *  powNum--;
								// p = gmtime(&minSec); //无时区信息,(GMT)时间
								// strftime(timestr, 6, "%H:%M", p);
								
								// strftime(timestr, 6, "%H:%M", p);
								
							 	// sprintf((char*)powsX, "%s\"%s\",", powsX, timestr);
								
								sprintf((char*)powsX, "%s\"%d mins\",", powsX, interval);
								
								// char timestr2[1024]={0};
								// char *p2;
								// p2 = ctime(&minSec); //当地时间，"Tue Dec 14 15:13:04 2021" 截取字符串
								// memcpy(timestr2, p2, strlen(p2));// 有回车符的样子。需要+1长度来截取
								// 测试的机器也是utc8的时区， 如果月日，星期几这里长度不一会导致这个截取时间失败， 还是直接获取 gmtime 比较安全
								// memcpy(timestr2, p2+11, strlen(p2)-20);

								// sprintf((char*)powsX, "%s\"%s\",", powsX, timestr2);
							}
	
							if(strlen(pows) > 0)
							{
								memcpy(pows2, pows, strlen(pows) - 1); // 处理最后逗号
								// TODO  boardpow pows数组 只有一组数据， 但界面展示成的是 board1 对应的数据展示， 其他board 没有示例
								sprintf((char*)outputData, "%s,\"%s\": {\"board1\":[%s]}", outputData, key, pows2);
								
								 
							}	
							
							if(strlen(powsX) > 0)
							{
								memcpy(powsX2, powsX, strlen(powsX) - 1); // 处理最后逗号
								sprintf((char*)outputData, "%s,\"pows_x\":[%s]", outputData, powsX2);
							}
							
						} // end of pows 
						 
						else
						{// 其他字符串字段
							sprintf((char*)outputData, "%s,\"%s\":\"%s\"", outputData, key, json_string_value(value));
						}
 
						iter = json_object_iter_next((json_t *)ret, iter);	
					}
				}
				else
				{
					isErr = 1;
					sprintf((char*)output, "{\"error\":%d,\"data\":{\"id\":\"%s\"},\"message\":\"%s\"}", (int)code, id, msg); 
				}
			}
		}// end of boardpow 算力
		
		// state 异常状况
		if(isErr == 0)
		{
			memset(buf, 0, sizeof(buf)/sizeof(char));
			memset(out, 0 ,sizeof(out)/sizeof(char));
  

			sprintf((char*)buf, "{\"id\":\"state\"}\n"); 
			
			result = sendMessage(buf, strlen(buf), (char*)(&out), sizeof(out));
			// send: {"id": "state", "ret": {"code": 0, "pow": true, "net": true, "fan": true, "temp": false}}
			
			
			if (strcmp("Create failed!", result) == 0 || strcmp("Connect failed!", result) == 0)
			{
				isErr = 1;
				sprintf((char*)output, "{\"error\":1,\"data\":{},\"message\":\"Connect miner failed!\"}"); 
			}
			else if( strcmp("Read timeout!", result) == 0 || strcmp("Error in select!", result) == 0 || strlen(out) == 0)
			{
				isErr = 1;
				sprintf((char*)output, "{\"error\":2,\"data\":{},\"message\":\"Miner return failed!\"}"); 
			}
			else
			{
				
				json_error_t err;
				json_t *jst, *ret;
				
				jst = JSON_LOADS((const char*)out, &err);
				
				ret = json_object_get(jst, "ret");
				
				const char *id, *msg;
				double code;
				 
				id = json_string_value(json_object_get(jst, "id"));	
				code = json_number_value(json_object_get(ret, "code"));	
				msg = json_string_value(json_object_get(ret, "msg"));	

				if(id == NULL)
				{
					isErr = 1;
					sprintf((char*)output, "{\"error\":3,\"data\":{},\"message\":\"Json decode fail!\"}"); 
				}
				else if((int)code == 0)
				{
					json_object_del(ret, "code");
					json_object_del(ret, "msg");
					
					void *iter;
					iter = json_object_iter((json_t *)ret);
					while(iter) 
					{
						const char *key;
						const json_t *value;
						key = json_object_iter_key(iter);
						value = json_object_iter_value(iter);

						sprintf((char*)outputData, "%s,\"%sstate\":%s", outputData, key, B2STR(json_is_true(value)));
						iter = json_object_iter_next((json_t *)ret, iter);
						
					}
				}
				else
				{
					isErr = 1;
					sprintf((char*)output, "{\"error\":%d,\"data\":{\"id\":\"%s\"},\"message\":\"%s\"}", (int)code, id, msg); 
				}
				
			}
		}// end of state 异常状况
		
		
		// fan 风扇
		if(isErr == 0)
		{
			memset(buf, 0, sizeof(buf)/sizeof(char));
			memset(out, 0 ,sizeof(out)/sizeof(char));

			sprintf((char*)buf, "{\"id\":\"fan\"}\n"); 
			
			result = sendMessage(buf, strlen(buf), (char*)(&out), sizeof(out));
			
			// send: {"id":"fan","ret":{"code":0,"fans":[4680, 4681, 5400,5400]}}
			
			if (strcmp("Create failed!", result) == 0 || strcmp("Connect failed!", result) == 0)
			{
				isErr = 1;
				sprintf((char*)output, "{\"error\":1,\"data\":{},\"message\":\"Connect miner failed!\"}"); 
			}
			else if( strcmp("Read timeout!", result) == 0 || strcmp("Error in select!", result) == 0 || strlen(out) == 0)
			{
				isErr = 1;
				sprintf((char*)output, "{\"error\":2,\"data\":{},\"message\":\"Miner return failed!\"}"); 
			}
			else
			{
				
				json_error_t err;
				json_t *jst, *ret, *jfans, *arrVal;
				const char *id, *msg;
				double code;
				
				jst = JSON_LOADS((const char*)out, &err);
				
				id = json_string_value(json_object_get(jst, "id"));
				ret = json_object_get(jst, "ret");				
				code = json_number_value(json_object_get(ret, "code"));	
				msg = json_string_value(json_object_get(ret, "msg"));	
 		 
				if(id == NULL)
				{
					isErr = 1;
					sprintf((char*)output, "{\"error\":3,\"data\":{},\"message\":\"Json decode fail!\"}"); 
				}
				else if((int)code == 0)
				{		
					char fans[4096]={0};
					char fans2[4096]={0};
					double fanspeed;
					size_t arrIndex;
					 
					jfans = json_object_get(ret, "fans");	

					json_array_foreach(jfans, arrIndex, arrVal) 
					{
						fanspeed = json_number_value(arrVal);
						sprintf((char*)fans, "%s%d,", fans, (int)fanspeed);
					}

					if(strlen(fans) > 0)
					{
						memcpy(fans2, fans, strlen(fans) - 1); // 处理最后逗号
						sprintf((char*)outputData, "%s,\"fans\":[%s]", outputData, fans2);
					}	
					 
				}else{
					isErr = 1;
					sprintf((char*)output, "{\"error\":%d,\"data\":{\"id\":\"%s\"},\"message\":\"%s\"}", (int)code, id, msg); 
				}
				
			}	
		}// end of fan 风扇
		
		
		// getpool 矿池
		if(isErr == 0)
		{
			memset(buf, 0, sizeof(buf)/sizeof(char));
			memset(out, 0 ,sizeof(out)/sizeof(char));

			sprintf((char*)buf, "{\"id\":\"getpool\"}\n"); 
			
			result = sendMessage(buf, strlen(buf), (char*)(&out), sizeof(out));
			
			// send: {"id":"getpool","ret":{"code":0,"pools":[{"no": 1, "addr": "stratum.antpool.com:3333", "user": "ccminer","pass":"123", "connect": false, "diff": "", "priority": 1, "accepted": 0, "rejected": 0, "diffa": 0,"diffr": 0, "state": 0, "lsdiff": 0, "lstime": ""},{"no": 2, "addr": "stratum.antpool.com:443", "user": "ccminer2","pass":"123", "connect": false, "diff": "", "priority": 2, "accepted": 0, "rejected": 0, "diffa": 0,"diffr": 0, "state": 0, "lsdiff": 0, "lstime": ""},{"no": 3, "addr": "stratum.antpool.com:12", "user": "ccminer3","pass":"123", "connect": false, "diff": "", "priority": 3, "accepted": 0, "rejected": 0, "diffa": 0,"diffr": 0, "state": 0, "lsdiff": 0, "lstime": ""}]}}

			
			if (strcmp("Create failed!", result) == 0 || strcmp("Connect failed!", result) == 0)
			{
				isErr = 1;
				sprintf((char*)output, "{\"error\":1,\"data\":{},\"message\":\"Connect miner failed!\"}"); 
			}
			else if( strcmp("Read timeout!", result) == 0 || strcmp("Error in select!", result) == 0 || strlen(out) == 0)
			{
				isErr = 1;
				sprintf((char*)output, "{\"error\":2,\"data\":{},\"message\":\"Miner return failed!\"}"); 
			}
			else
			{
				json_error_t err;
				json_t *jst, *ret, *jpools, *jpoolsInfo;
				const char *id, *msg;
				double code;
				
				jst = JSON_LOADS((const char*)out, &err);
				
				id = json_string_value(json_object_get(jst, "id"));
				ret = json_object_get(jst, "ret");				
				code = json_number_value(json_object_get(ret, "code"));	
				msg = json_string_value(json_object_get(ret, "msg"));	
 		 
				if(id == NULL)
				{
					isErr = 1;
					sprintf((char*)output, "{\"error\":3,\"data\":{},\"message\":\"Json decode fail!\"}"); 
				}
				else if((int)code == 0)
				{		
					size_t arrIndex;
					
					jpools = json_object_get(ret, "pools");	
					
					char allPools[4096]={0};
					char allPools2[4096]={0};
						
					json_array_foreach(jpools, arrIndex, jpoolsInfo) 
					{ // 多个矿池数据循环读取
						char pools[4096]={0};
						char pools2[4096]={0};
			 
				
						void *iter;
						iter = json_object_iter((json_t *)jpoolsInfo);
						while(iter) {// 单个矿池数据读取
							const char *key;
							const json_t *value;
							key = json_object_iter_key(iter);
							value = json_object_iter_value(iter);
			
  
							if(key && strcmp("connect", key) == 0)
							{
								sprintf((char*)pools, "%s\"%s\":%s,", pools, key, B2STR(json_is_true(value)));
								
								// sprintf((char*)output, "%s:%s:%s", id, key, B2STR(json_is_true(value)));
								// render((const char*)output);
								// return ;
								
							}
							else if(key && (strcmp("addr", key) == 0 || strcmp("user", key) == 0 || strcmp("pass", key) == 0
								|| strcmp("diff", key) == 0 || strcmp("lstime", key) == 0)) 
							{
								sprintf((char*)pools, "%s\"%s\":\"%s\",", pools, key, json_string_value(value));
							}
							else
							{
								sprintf((char*)pools, "%s\"%s\":%f,", pools, key, json_number_value(value));
							}
		 
							iter = json_object_iter_next((json_t *)jpoolsInfo, iter);
						}
						
						
						if(strlen(pools) > 0)
						{
							memcpy(pools2, pools, strlen(pools) - 1); // 处理最后逗号
							sprintf((char*)allPools, "%s{%s},", allPools, pools2);
						}	
					}

					if(strlen(allPools) > 0)
					{
						memcpy(allPools2, allPools, strlen(allPools) - 1); // 处理最后逗号
						sprintf((char*)outputData, "%s,\"pools\":[%s]", outputData, allPools2);
					}				 
				}
				else
				{
					isErr = 1;
					sprintf((char*)output, "{\"error\":%d,\"data\":{\"id\":\"%s\"},\"message\":\"%s\"}", (int)code, id, msg); 
				}
				
			}	
		}// end of getpool 矿池
		
		
		// board 算力板信息
		if(isErr == 0)
		{
			memset(buf, 0, sizeof(buf)/sizeof(char));
			memset(out, 0 ,sizeof(out)/sizeof(char));

			sprintf((char*)buf, "{\"id\":\"board\"}\n"); 
			
			result = sendMessage(buf, strlen(buf), (char*)(&out), sizeof(out));
			
			// send: {"id":"board", "ret":{"code": 0, "chainnum": 0, "boards": [{"no": 1, "chipnum": 76, "error": 0, "freq": 660, "rtpow": "130G", "idealpow":"141G", "tempnum":"0", "pcbtemp":"", "intmp": 59.120000, "outtmp": 61.380000, "state": true, "false":[]},{"no": 2, "chipnum": 76, "error": 0, "freq": 660, "rtpow": "124G", "idealpow":"141G", "tempnum":"0", "pcbtemp":"", "intmp": 55.220000, "outtmp": 58.170000, "state": true, "false":[]},{"no": 3, "chipnum": 76, "error": 0, "freq": 660, "rtpow": "136G", "idealpow":"141G", "tempnum":"0", "pcbtemp":"", "intmp": 60.220000, "outtmp": 62.050000, "state": true, "false":[]}]}}

			
			if (strcmp("Create failed!", result) == 0 || strcmp("Connect failed!", result) == 0)
			{
				isErr = 1;
				sprintf((char*)output, "{\"error\":1,\"data\":{},\"message\":\"Connect miner failed!\"}"); 
			}
			else if( strcmp("Read timeout!", result) == 0 || strcmp("Error in select!", result) == 0 || strlen(out) == 0)
			{
				isErr = 1;
				sprintf((char*)output, "{\"error\":2,\"data\":{},\"message\":\"Miner return failed!\"}"); 
			}
			else
			{	
				json_error_t err;
				json_t *jst, *ret, *jboards, *jboardsInfo;
				const char *id, *msg;
				double code;
				
				jst = JSON_LOADS((const char*)out, &err);
				
				id = json_string_value(json_object_get(jst, "id"));
				ret = json_object_get(jst, "ret");				
				code = json_number_value(json_object_get(ret, "code"));	
				msg = json_string_value(json_object_get(ret, "msg"));	
 		 
				if(id == NULL)
				{
					isErr = 1;
					sprintf((char*)output, "{\"error\":3,\"data\":{},\"message\":\"Json decode fail!\"}"); 
				}
				else if((int)code == 0)
				{		
					size_t arrIndex;
					
					jboards = json_object_get(ret, "boards");	
					
					char allBoards[4096]={0};
					char allBoards2[4096]={0};
						
					json_array_foreach(jboards, arrIndex, jboardsInfo) 
					{ // 多个数据循环读取
						char boards[4096]={0};
						char boards2[4096]={0};
			 
				
						void *iter;
						iter = json_object_iter((json_t *)jboardsInfo);
						while(iter) 
						{// 单个数据读取
							const char *key;
							const json_t *value;
							key = json_object_iter_key(iter);
							value = json_object_iter_value(iter);
			
  
							if(key && strcmp("state", key) == 0)
							{
								sprintf((char*)boards, "%s\"%s\":%s,", boards, key, B2STR(json_is_true(value)));
								
								// sprintf((char*)output, "%s:%s:%s", id, key, B2STR(json_is_true(value)));
								// render((const char*)output);
								// return ;
								
							}
							else if(key && strcmp("false", key) == 0)
							{ 
								// false 显示对应board上的芯片是否有坏， for example:
								// false:[20, 30], 第20（对应芯片index 19）， 第30（对应芯片index 29）的芯片有异常
	
								// sprintf((char*)boards, "%s\"%s\":%s,", boards, key, B2STR(json_is_true(value)));
								// sprintf((char*)boards, "%s\"%s\":\"\",", boards, key);
								 
								// sprintf((char*)boards, "%s\"%s\":[20, 30],", boards, key);
								
								// sprintf((char*)output, "%s:%s:%s", id, key, B2STR(json_is_true(value)));
								// render((const char*)output);
								// return ;
								
								if(json_is_array(value) && json_array_size(value) > 0)
								{
									json_t *jAbChipInx;
									size_t abChipInx;
									char abChips[4096]={0};
									char abChips2[4096]={0};
									double abChipInxVal;
									json_array_foreach(value, abChipInx, jAbChipInx) 
									{
										abChipInxVal = json_number_value(jAbChipInx);
										sprintf((char*)abChips, "%s%d,", abChips, (int)abChipInxVal);
									}
									
									if(strlen(abChips) > 0)
									{
										memcpy(abChips2, abChips, strlen(abChips) - 1); // 处理最后逗号
										sprintf((char*)boards, "%s\"%s\":[%s],", boards, key, abChips2);
									}
							  
								}
								else
								{
									// 没有的话返回空字符串， 否则界面报错
									sprintf((char*)boards, "%s\"%s\":\"\",", boards, key);
								}
						
								
							}
							else if(key && (strcmp("rtpow", key) == 0 || strcmp("idealpow", key) == 0 || strcmp("tempnum", key) == 0
								|| strcmp("pcbtemp", key) == 0 || strcmp("avgpow", key) == 0)) 
							{
								sprintf((char*)boards, "%s\"%s\":\"%s\",", boards, key, json_string_value(value));
							}
							else
							{
								sprintf((char*)boards, "%s\"%s\":%f,", boards, key, json_number_value(value));
							}
		 
							iter = json_object_iter_next((json_t *)jboardsInfo, iter);
						}
						
						
						if(strlen(boards) > 0)
						{
							memcpy(boards2, boards, strlen(boards) - 1); // 处理最后逗号
							sprintf((char*)allBoards, "%s{%s},", allBoards, boards2);
						}	
					}

					if(strlen(allBoards) > 0)
					{
						memcpy(allBoards2, allBoards, strlen(allBoards) - 1); // 处理最后逗号
						sprintf((char*)outputData, "%s,\"boards\":[%s]", outputData, allBoards2);
					}
		 	
					 
				}
				else
				{
					isErr = 1;
					sprintf((char*)output, "{\"error\":%d,\"data\":{\"id\":\"%s\"},\"message\":\"%s\"}", (int)code, id, msg); 
				}
				
			}	
		}// end of board 算力板信息
 
	
		if(isErr == 0)
		{
			time_t now_time;
			struct tm *info;
			char buffer[80];
			time( &now_time );
			info = localtime( &now_time );
			strftime(buffer, 80, "%Y-%m-%d %H:%M:%S %Z", info);
			 		
			sprintf((char*)outputData, "%s,\"refTime\":\"%s\"", outputData, buffer);
			
			memcpy(outputData2, &outputData[1], strlen(outputData)-1);
			sprintf((char*)output, "{\"error\":0,\"data\":{%s},\"message\":\"\"}", outputData2);
		}
 
		render((const char*)output);
		
	} // end of getinfo
	
	else if(post != NULL && strcmp("5", post) == 0)
	{// 定位矿机
		
		char buf[1024]={0};
		char out[4096]={0};
		char output[4096]={0};
		 
		const char *locate; 
		 
		locate = trim((char*)param("locate"));
		
		int boolLocate = 0;
		if (strcmp("1", locate) == 0)
		{
			boolLocate = 1;
		}
		
		sprintf((char*)buf, "{\"id\":\"setlocate\", \"on\":%s}\n", (B2STR(boolLocate))); 
		
		char* result ;
		result = sendMessage(buf, strlen(buf), (char*)(&out), sizeof(out));
		
		// {"id": "setlocate", "ret": {"code": 0}}


		if (strcmp("Create failed!", result) == 0 || strcmp("Connect failed!", result) == 0)
		{
			// isErr = 1;
			sprintf((char*)output, "{\"error\":1,\"data\":{},\"message\":\"Connect miner failed!\"}"); 
		}
		else if( strcmp("Read timeout!", result) == 0 || strcmp("Error in select!", result) == 0 || strlen(out) == 0)
		{
			// isErr = 1;
			sprintf((char*)output, "{\"error\":2,\"data\":{},\"message\":\"Miner return failed!\"}"); 
		}
		else
		{
			json_error_t err;
			json_t *jst, *ret;
			
			jst = JSON_LOADS((const char*)out, &err);
			
			ret = json_object_get(jst, "ret");
			
			const char *id, *msg;
			double code;
			 
			id = json_string_value(json_object_get(jst, "id"));	
			code = json_number_value(json_object_get(ret, "code"));	
			msg = json_string_value(json_object_get(ret, "msg"));	
 
  
			if(id == NULL)
			{
				// isErr = 1;
				sprintf((char*)output, "{\"error\":3,\"data\":{},\"message\":\"Json decode fail!\"}"); 
			}
			else if((int)code == 0)
			{
				sprintf((char*)output, "{\"error\":0,\"data\":{},\"message\":\"%s\"}", msg);
			}
			else
			{ 
				if(msg != NULL)
				{
					sprintf((char*)output, "{\"error\":%d,\"data\":{\"id\":\"%s\"},\"message\":\"%s\"}", (int)code, id, msg); 
				}
				else
				{
					sprintf((char*)output, "{\"error\":%d,\"data\":{\"id\":\"%s\"},\"message\":\"set locate failed\"}", (int)code, id); 
				}
				
			}
		}
 
		
		render((const char*)output);
	}
	// 6是登录， 已经换了链接实现了
	else if(post != NULL && strcmp("7", post) == 0)
	{// 检查状态
		//测试网络
		char buf[1024]={0};
		char out[4096]={0};
		// char out2[1024]={0};
		char output[4096]={0};
		 
		sprintf((char*)buf, "{\"id\":\"hello\"}\n"); 
		char* result ;
		
 
		result = sendMessage(buf, strlen(buf), (char*)(&out), sizeof(out));
		
		// {"id":"hello", "ret":{"code":0, "msg": "world"}}


		if (strcmp("Create failed!", result) == 0 || strcmp("Connect failed!", result) == 0)
		{
			sprintf((char*)output, "{\"error\":1,\"data\":{},\"message\":\"Connect miner failed!\"}"); 
		}
		else if( strcmp("Read timeout!", result) == 0 || strcmp("Error in select!", result) == 0 || strlen(out) == 0)
		{
			// isErr = 1;
			sprintf((char*)output, "{\"error\":2,\"data\":{},\"message\":\"Miner return failed!\"}"); 
		}
		else
		{
			json_error_t err;
			json_t *jst, *ret;
			
			// memcpy(out2, out, strlen(out)-1);
			
			jst = JSON_LOADS((const char*)out, &err);
			
			ret = json_object_get(jst, "ret");
			
			const char *id, *msg;
			double code;
			 
			id = json_string_value(json_object_get(jst, "id"));	
			code = json_number_value(json_object_get(ret, "code"));	
			msg = json_string_value(json_object_get(ret, "msg"));	
			
			// json_object_del(ret, "code");
			// json_object_del(ret, "msg");
			
			// sprintf((char*)output, "%s", out);
			
			
			if(id == NULL)
			{
				// isErr = 1;
				sprintf((char*)output, "{\"error\":3,\"data\":{},\"message\":\"Json decode fail!\"}"); 
			}
			else if((int)code == 0)
			{
				// TODO msg 内容输出到界面乱码，导致界面json解释失败。 这里成功的话 msg不输出也可以
				sprintf((char*)output, "{\"error\":0,\"data\":{},\"message\":\"\"}");
				// sprintf((char*)output, "{\"error\":0,\"data\":\"%s\"}", msg);
			}
			else
			{
				 
				if(msg != NULL)
				{
					sprintf((char*)output, "{\"error\":%d,\"data\":{\"id\":\"%s\"},\"message\":\"%s\"}", (int)code, id, msg); 
				}
				else
				{
					sprintf((char*)output, "{\"error\":%d,\"data\":{\"id\":\"%s\"},\"message\":\"test failed\"}", (int)code, id); 
				}
				
			}
		}
  
		render((const char*)output);
	}
	else if(post != NULL && strcmp("3", post) == 0)
	{	
		// 重启
		char buf[1024]={0};
		char out[4096]={0};
		char output[4096]={0};
 
		// {"id": "restart", "ret": {"code": 0 }}
		
		 
		sprintf((char*)buf, "{\"id\":\"restart\"}\n"); 
		char* result ;
 
		result = sendMessage(buf, strlen(buf), (char*)(&out), sizeof(out));
		if (strcmp("Create failed!", result) == 0 || strcmp("Connect failed!", result) == 0)
		{
			sprintf((char*)output, "{\"error\":1,\"data\":{},\"message\":\"Connect miner failed!\"}"); 
		}
		else if( strcmp("Read timeout!", result) == 0 || strcmp("Error in select!", result) == 0 || strlen(out) == 0)
		{
			// isErr = 1;
			sprintf((char*)output, "{\"error\":2,\"data\":{},\"message\":\"Miner return failed!\"}"); 
		}
		else
		{
			json_error_t err;
			json_t *jst, *ret;
			
			jst = JSON_LOADS((const char*)out, &err);
			
			ret = json_object_get(jst, "ret");
			
			const char *id, *msg;
			double code;
			 
			id = json_string_value(json_object_get(jst, "id"));	
			code = json_number_value(json_object_get(ret, "code"));	
			msg = json_string_value(json_object_get(ret, "msg"));	
			
			// json_object_del(ret, "code");
			// json_object_del(ret, "msg");
			
			if(id == NULL)
			{
				// isErr = 1;
				sprintf((char*)output, "{\"error\":3,\"data\":{},\"message\":\"Json decode fail!\"}"); 
			}
			else if((int)code == 0)
			{
				sprintf((char*)output, "{\"error\":0,\"data\":{},\"message\":\"%s\"}", msg);
				// TODO msg 内容输出到界面乱码，导致界面json解释失败。 这里成功的话 msg不输出也可以
				// sprintf((char*)output, "{\"error\":0,\"data\":{},\"message\":\"\"}");
			}
			else
			{ 
				if(msg != NULL)
				{
					sprintf((char*)output, "{\"error\":%d,\"data\":{\"id\":\"%s\"},\"message\":\"%s\"}", (int)code, id, msg); 
				}
				else
				{
					sprintf((char*)output, "{\"error\":%d,\"data\":{\"id\":\"%s\"},\"message\":\"set locate failed\"}", (int)code, id); 
				}
				
			}
		}
 
		
		render((const char*)output);

	}// end of restart
	else if(post != NULL && strcmp("2", post) == 0)
	{
		// 恢复出厂设置
		char buf[1024]={0};
		char out[4096]={0};
		char output[4096]={0};
	 
		sprintf((char*)buf, "{\"id\":\"resetfactory\"}\n"); 
		
		char* result ;
		result = sendMessage(buf, strlen(buf), (char*)(&out), sizeof(out));
 
		if (strcmp("Create failed!", result) == 0 || strcmp("Connect failed!", result) == 0)
		{
			sprintf((char*)output, "{\"error\":1,\"data\":{},\"message\":\"Connect miner failed!\"}"); 
		}
		else if( strcmp("Read timeout!", result) == 0 || strcmp("Error in select!", result) == 0 || strlen(out) == 0)
		{
			// isErr = 1;
			sprintf((char*)output, "{\"error\":2,\"data\":{},\"message\":\"Miner return failed!\"}"); 
		}
		else
		{
			json_error_t err;
			json_t *jst, *ret;
			
			jst = JSON_LOADS((const char*)out, &err);
			
			ret = json_object_get(jst, "ret");
			
			const char *id, *msg;
			double code;
			 
			id = json_string_value(json_object_get(jst, "id"));	
			code = json_number_value(json_object_get(ret, "code"));	
			msg = json_string_value(json_object_get(ret, "msg"));	
 
			if(id == NULL)
			{
				// isErr = 1;
				sprintf((char*)output, "{\"error\":3,\"data\":{},\"message\":\"Json decode fail!\"}"); 
			}
			else if((int)code == 0)
			{
				sprintf((char*)output, "{\"error\":0,\"data\":{},\"message\":\"%s\"}", msg);
			}
			else
			{ 
				if(msg != NULL)
				{
					sprintf((char*)output, "{\"error\":%d,\"data\":{\"id\":\"%s\"},\"message\":\"%s\"}", (int)code, id, msg); 
				}
				else
				{
					sprintf((char*)output, "{\"error\":%d,\"data\":{\"id\":\"%s\"},\"message\":\"set locate failed\"}", (int)code, id); 
				}
				
			}
		}
  
		render((const char*)output);
	} // end of resetfactory
	
	else
	{
		render("{\"data\":\"userpanel\"}");
		 
	}
}



static void firpage(HttpConn *conn, EspAction *action)
{ 
	espRenderView(conn, "view/fir.esp", 0);
}

static void firConfig(HttpConn *conn, EspAction *action)
{ 
	const char* post; 
	post = param ("post");
	if(post != NULL && strcmp("2", post) == 0){
		//上传固件
		
		
		char output[8192]={0};
 
			
		MprList *files = espGetUploads (conn);
		// MprList *files = conn->rx->files

		if(files->length == 0)
		{
			 
			sprintf((char*)output, "{\"error\":1,\"data\":[],\"message\":\"请选择文件\"}"); 
		}
		else
		{
			//需要将文件上传到主机
			HttpUploadFile  *file;
			// MprKey          *kp;
			
			// sleep(10);  
			 
			// char* destFile = (char*)malloc(sizeof(char));
			// char* destDir = (char*)malloc(sizeof(char));
			
			   
			// if((destDir = getcwd(NULL, 0)) == NULL)  
			// {  
				 // sprintf((char*)output, "{\"error\":1,\"data\":[],\"message\":\"请选择文件\"}"); 
			// }  
			 
			
			
			// memcpy(destFile, "test123.cnf", strlen("test123.cnf"));
			// memcpy(destDir, "/root/lolo/zttest/appweb/bginweb2/web", strlen("/root/lolo/zttest/appweb/bginweb2/web"));
			// memcpy(destFile, "test123.cnf", strlen("test123.cnf"));
			
			// memcpy(destDir, "uploads", strlen("uploads"));
			
			// destDir = getcwd(NULL, 0);
			
			char destDir[1000];
			char destFile[1000];
			getcwd(destDir, 1000);

			// printf("destDir %s\n", destDir);
			
			strcat(destDir, "/uploads");
			
			printf("destDir2 %s\n", destDir);
			
			
			for (int i=0; i<files->length; i++) {
				file = files->items[i];
				// render("NAME %s\n", file->name);
				// render("FILENAME %s\n", file->filename);
				// render("CLIENT_NAME %s\n", file->clientFilename);
				printf("CLIENT_NAME %s\n", file->clientFilename);
				// render("TYPE %s\n", file->contentType);
				// render("SIZE %d\n", file->size);
				printf("SIZE %d\n", file->size);
 
				// copyfile((char *)file->filename, destDir, destFile);	
				copyfile((char *)file->filename, destDir, (char *)file->clientFilename);
			 
			}
			
	
			strcpy(destFile, destDir);	
			strcat(destFile, "/");
			strcat(destFile, (char *)file->clientFilename);
			if (access(destFile, F_OK) != 0)
			{
				 
				sprintf((char*)output, "{\"error\":1,\"data\":[],\"message\":\"文件上传失败\"}"); 
			}
			else
			{
				char md5[MD5_LEN + 1];

				// printf("Success! MD5 len: %d, file name: %s\n", MD5_LEN, destFile);
				
				if (!CalcFileMD5(destFile, md5)) {
					puts("Error occured!");
				} else {
					printf("Success! MD5 sum is: %s\n", md5);
				}
			
				
				char buf[1024]={0};
				char out[8192]={0};
	
				char* result ;
 
				const char* keepconfig; 
				keepconfig = trim((char*)param("keepconfig"));
				int keep = 0;
				if (strcmp("true", keepconfig) == 0)
				{
					keep = 1;
				}
			  
				sprintf((char*)buf, "{\"id\":\"firmupdate\", \"keepconfig\":%s, \"file\":\"%s\", \"filemd5\":\"%s\"}\n", (B2STR(keep)), destFile, md5); 
				
				result = sendMessage(buf, strlen(buf), (char*)(&out), sizeof(out));
				if (strcmp("Create failed!", result) == 0 || strcmp("Connect failed!", result) == 0)
				{
					sprintf((char*)output, "{\"error\":1,\"data\":{},\"message\":\"Connect miner failed!\"}"); 
				}
				else if( strcmp("Read timeout!", result) == 0 || strcmp("Error in select!", result) == 0 || strlen(out) == 0)
				{
					// isErr = 1;
					sprintf((char*)output, "{\"error\":2,\"data\":{},\"message\":\"Miner return failed!\"}"); 
				}
				else
				{
					json_error_t err;
					json_t *jst, *ret;
					
					jst = JSON_LOADS((const char*)out, &err);
					
					ret = json_object_get(jst, "ret");
					
					const char *id, *msg;
					double code;
					 
					id = json_string_value(json_object_get(jst, "id"));	
					code = json_number_value(json_object_get(ret, "code"));	
					msg = json_string_value(json_object_get(ret, "msg"));	
					
					// json_object_del(ret, "code");
					// json_object_del(ret, "msg");
					
					if(id == NULL)
					{
						// isErr = 1;
						sprintf((char*)output, "{\"error\":3,\"data\":{},\"message\":\"Json decode fail!\"}"); 
					}
					else if((int)code == 0)
					{
						sprintf((char*)output, "{\"error\":0,\"data\":{},\"message\":\"\"}"); 
					}
					else
					{
						sprintf((char*)output, "{\"error\":%d,\"data\":{\"id\":\"%s\"},\"message\":\"%s\"}", (int)code, id, msg); 
					}
				}	
				
			}
			
		}	
 
 
		render((const char*)output);
		// render("{\"data\":\"firConfig1\"}");
		
	}else{
		
		render("{\"data\":\"firConfig\"}");
	}
	
}



static void ippage(HttpConn *conn, EspAction *action)
{ 
	espRenderView(conn, "view/ip.esp", 0);
}


static void ipConfig(HttpConn *conn, EspAction *action)
{ 

	const char* post; 
	post = param ("post");
	 
	if(post != NULL && strcmp("1", post) == 0)
	{
		//获取界面信息
		char buf[1024]={0};
		char out[8192]={0};
		char output[8192]={0};
		
		char outputData[8192]={0};
		char outputData2[8192]={0};
		
 
		int isErr = 0;
		sprintf((char*)buf, "{\"id\":\"getnet\"}\n"); 
		char* result ;
 
			
		result = sendMessage(buf, strlen(buf), (char*)(&out), sizeof(out));
		
		// {"id":"getnet","ret":{"code":0,"nic": "eth0", "mac":"", "ip": "192.168.1.124 172.17.0.1","netmask":"", "host": "ubuntu", "dhcp": false, "gateway": "192.168.1.1", "dns": "127.0.0.53"}}

 
		if (strcmp("Create failed!", result) == 0 || strcmp("Connect failed!", result) == 0)
		{
			isErr = 1;
			sprintf((char*)output, "{\"error\":1,\"data\":{},\"message\":\"Connect miner failed!\"}"); 
		}
		else if( strcmp("Read timeout!", result) == 0 || strcmp("Error in select!", result) == 0 || strlen(out) == 0)
		{
			isErr = 1;
			sprintf((char*)output, "{\"error\":2,\"data\":{},\"message\":\"Miner return failed!\"}"); 
		}
		else
		{
			json_error_t err;
			json_t *jst, *ret;
			
			jst = JSON_LOADS((const char*)out, &err);
			
			ret = json_object_get(jst, "ret");
			
			const char *id, *msg;
			double code;
			 
			id = json_string_value(json_object_get(jst, "id"));	
			code = json_number_value(json_object_get(ret, "code"));	
			msg = json_string_value(json_object_get(ret, "msg"));	
 	
			if(id == NULL)
			{
				isErr = 1;
				sprintf((char*)output, "{\"error\":3,\"data\":{},\"message\":\"Json decode fail!\"}"); 
			}
			else if((int)code == 0)
			{
				json_object_del(ret, "code");
				json_object_del(ret, "msg");
			
				void *iter;
				iter = json_object_iter((json_t *)ret);
				while(iter) 
				{
					const char *key;
					const json_t *value;
					key = json_object_iter_key(iter);
					value = json_object_iter_value(iter);
					
					if(key != NULL && strcmp("dhcp", key) == 0)
					{
						sprintf((char*)outputData, "%s,\"%s\":%s", outputData, key, B2STR(json_is_true(value)));
						
					}
					else
					{
						sprintf((char*)outputData, "%s,\"%s\":\"%s\"", outputData, key, json_string_value(value));
					}
 
					iter = json_object_iter_next((json_t *)ret, iter);
					
				}
			}
			else
			{
				isErr = 1;
				sprintf((char*)output, "{\"error\":%d,\"data\":{\"id\":\"%s\"},\"message\":\"%s\"}", (int)code, id, msg); 
			}

			// sprintf((char*)output, "%s:%ld", out, strlen(out));

		}
		
  
		if(isErr == 0)
		{
			memcpy(outputData2, &outputData[1], strlen(outputData)-1);
			sprintf((char*)output, "{\"error\":0,\"data\":{%s},\"message\":\"\"}", outputData2);
		}
		
		render((const char*)output);
	}// end of getnet
	
	else if(post != NULL && strcmp("2", post) == 0){
		// render("{\"data\":\"ipConfig1\"}");
		
		char output[8192]={0};
		const char *host, *agreement, *ip, *netmask, *gateway, *dns; 
		 
		host = trim((char*)param("host"));
		agreement = trim((char*)param("agreement"));
		ip = trim((char*)param("ip"));
		netmask = trim((char*)param("netmask"));
		gateway = trim((char*)param("gateway"));
		dns = trim((char*)param("dns"));
  
		int dhcp = 0;
		if (strcmp("dhcp", agreement) == 0)
		{
			dhcp = 1;
		}
			
	 
		if(host == NULL || strlen(host) == 0 || ip == NULL || strlen(ip) == 0 || netmask == NULL || strlen(netmask) == 0 
		|| gateway == NULL || strlen(gateway) == 0)
		{
			sprintf((char*)output, "{\"error\":1,\"data\":{},\"message\":\"主机名,IP地址,子网掩码,网关,不能为空\"}"); 
		}
		else  
		{	
			char buf[1024]={0};
			char out[8192]={0};
			char* result ;
			
			sprintf((char*)buf, "{\"id\":\"setnet\", \"dhcp\":%s, \"ip\":\"%s\", \"netmask\":\"%s\", \"host\":\"%s\", \"gateway\":\"%s\", \"dns\":\"%s\"}\n", (B2STR(dhcp)), ip, netmask, host, gateway, dns); 

			result = sendMessage(buf, strlen(buf), (char*)(&out), sizeof(out));
			if (strcmp("Create failed!", result) == 0 || strcmp("Connect failed!", result) == 0)
			{
				sprintf((char*)output, "{\"error\":1,\"data\":{},\"message\":\"Connect miner failed!\"}"); 
			}
			else if( strcmp("Read timeout!", result) == 0 || strcmp("Error in select!", result) == 0 || strlen(out) == 0)
			{
				// isErr = 1;
				sprintf((char*)output, "{\"error\":2,\"data\":{},\"message\":\"Miner return failed!\"}"); 
			}
			else
			{
				// render((const char*)out);
				
				json_error_t err;
				json_t *jst, *ret;
				
				jst = JSON_LOADS((const char*)out, &err);
				
				ret = json_object_get(jst, "ret");
				
				const char *id, *msg;
				double code;
				 
				id = json_string_value(json_object_get(jst, "id"));	
				code = json_number_value(json_object_get(ret, "code"));	
				msg = json_string_value(json_object_get(ret, "msg"));	
				
				
				// render((const char*)msg);
				
				
				// json_object_del(ret, "code");
				// json_object_del(ret, "msg");
				
				if(id == NULL)
				{
					// isErr = 1;
					sprintf((char*)output, "{\"error\":3,\"data\":{},\"message\":\"Json decode fail!\"}"); 
				}
				else if((int)code == 0)
				{
					sprintf((char*)output, "{\"error\":0,\"data\":{},\"message\":\"\"}"); 
				}
				else
				{
					sprintf((char*)output, "{\"error\":%d,\"data\":{\"id\":\"%s\"},\"message\":\"%s\"}", (int)code, id, msg); 
				}
			}	
		}	
		
		render((const char*)output);
	 
	}else{
		
		render("{\"data\":\"ipConfig2\"}");
	}
	
	
	
}




static void logpage(HttpConn *conn, EspAction *action)
{ 
	espRenderView(conn, "view/log.esp", 0);
}


static void machinepage(HttpConn *conn, EspAction *action)
{ 
	espRenderView(conn, "view/machine.esp", 0);
}

static void machineConfig(HttpConn *conn, EspAction *action)
{ 
	
	
	const char* post; 
	post = param ("post");

	//获取矿池信息
	if(post != NULL && strcmp("1", post) == 0)
	{
		//获取界面信息
		char buf[1024]={0};
		char out[8192]={0};
		char output[8192]={0};
		
		char outputData[4096]={0};
		char outputData2[4096]={0};
		
		
		int isErr = 0;
		char* result ;
 
		sprintf((char*)buf, "{\"id\":\"getpool\"}\n"); 
		
		result = sendMessage(buf, strlen(buf), (char*)(&out), sizeof(out));
		
		// send: {"id":"getpool","ret":{"code":0,"pools":[{"no": 1, "addr": "stratum.antpool.com:3333", "user": "ccminer","pass":"123", "connect": false, "diff": "", "priority": 1, "accepted": 0, "rejected": 0, "diffa": 0,"diffr": 0, "state": 0, "lsdiff": 0, "lstime": ""},{"no": 2, "addr": "stratum.antpool.com:443", "user": "ccminer2","pass":"123", "connect": false, "diff": "", "priority": 2, "accepted": 0, "rejected": 0, "diffa": 0,"diffr": 0, "state": 0, "lsdiff": 0, "lstime": ""},{"no": 3, "addr": "stratum.antpool.com:12", "user": "ccminer3","pass":"123", "connect": false, "diff": "", "priority": 3, "accepted": 0, "rejected": 0, "diffa": 0,"diffr": 0, "state": 0, "lsdiff": 0, "lstime": ""}]}}

		
		if (strcmp("Create failed!", result) == 0 || strcmp("Connect failed!", result) == 0)
		{
			isErr = 1;
			sprintf((char*)output, "{\"error\":1,\"data\":{},\"message\":\"Connect miner failed!\"}"); 
		}
		else if( strcmp("Read timeout!", result) == 0 || strcmp("Error in select!", result) == 0 || strlen(out) == 0)
		{
			isErr = 1;
			sprintf((char*)output, "{\"error\":2,\"data\":{},\"message\":\"Miner return failed!\"}"); 
		}
		else
		{
			json_error_t err;
			json_t *jst, *ret, *jpools, *jpoolsInfo;
			const char *id, *msg;
			double code;
			
			jst = JSON_LOADS((const char*)out, &err);
			
			id = json_string_value(json_object_get(jst, "id"));
			ret = json_object_get(jst, "ret");				
			code = json_number_value(json_object_get(ret, "code"));	
			msg = json_string_value(json_object_get(ret, "msg"));	
	 
			if(id == NULL)
			{
				isErr = 1;
				sprintf((char*)output, "{\"error\":3,\"data\":{},\"message\":\"Json decode fail!\"}"); 
			}
			else if((int)code == 0)
			{		
				size_t arrIndex;
				
				jpools = json_object_get(ret, "pools");	
				
				char allPools[4096]={0};
				char allPools2[4096]={0};
					
				json_array_foreach(jpools, arrIndex, jpoolsInfo) 
				{ // 多个矿池数据循环读取
					char pools[4096]={0};
					char pools2[4096]={0};
		 
			
					void *iter;
					iter = json_object_iter((json_t *)jpoolsInfo);
					while(iter) {// 单个矿池数据读取
						const char *key;
						const json_t *value;
						key = json_object_iter_key(iter);
						value = json_object_iter_value(iter);
		

						if(key && strcmp("connect", key) == 0)
						{
							sprintf((char*)pools, "%s\"%s\":%s,", pools, key, B2STR(json_is_true(value)));
							
							// sprintf((char*)output, "%s:%s:%s", id, key, B2STR(json_is_true(value)));
							// render((const char*)output);
							// return ;
							
						}
						else if(key && (strcmp("addr", key) == 0 || strcmp("user", key) == 0 || strcmp("pass", key) == 0
							|| strcmp("diff", key) == 0 || strcmp("lstime", key) == 0)) 
						{
							sprintf((char*)pools, "%s\"%s\":\"%s\",", pools, key, json_string_value(value));
						}
						else
						{
							sprintf((char*)pools, "%s\"%s\":%f,", pools, key, json_number_value(value));
						}
	 
						iter = json_object_iter_next((json_t *)jpoolsInfo, iter);
					}
					
					
					if(strlen(pools) > 0)
					{
						memcpy(pools2, pools, strlen(pools) - 1); // 处理最后逗号
						sprintf((char*)allPools, "%s{%s},", allPools, pools2);
					}	
				}

				if(strlen(allPools) > 0)
				{
					memcpy(allPools2, allPools, strlen(allPools) - 1); // 处理最后逗号
					sprintf((char*)outputData, "%s,\"pools\":[%s]", outputData, allPools2);
				}
		
				 
			}
			else
			{
				isErr = 1;
				sprintf((char*)output, "{\"error\":%d,\"data\":{\"id\":\"%s\"},\"message\":\"%s\"}", (int)code, id, msg); 
			}
		}


		// get 硬件配置
		if(isErr == 0)
		{
			memset(buf, 0, sizeof(buf)/sizeof(char));
			memset(out, 0 ,sizeof(out)/sizeof(char));
  

			sprintf((char*)buf, "{\"id\":\"gethw\"}\n"); 
			
			result = sendMessage(buf, strlen(buf), (char*)(&out), sizeof(out));
		 
			
			if (strcmp("Create failed!", result) == 0 || strcmp("Connect failed!", result) == 0)
			{
				isErr = 1;
				sprintf((char*)output, "{\"error\":1,\"data\":{},\"message\":\"Connect miner failed!\"}"); 
			}
			else if( strcmp("Read timeout!", result) == 0 || strcmp("Error in select!", result) == 0 || strlen(out) == 0)
			{
				isErr = 1;
				sprintf((char*)output, "{\"error\":2,\"data\":{},\"message\":\"Miner return failed!\"}"); 
			}
			else
			{
				// {“id”:”gethw”, “ret”: {“code”:0, “getratio”:50,”getmode”:1}}
				json_error_t err;
				json_t *jst, *ret;
				
				jst = JSON_LOADS((const char*)out, &err);
				
				ret = json_object_get(jst, "ret");
				
				const char *id, *msg;
				double code;
				 
				id = json_string_value(json_object_get(jst, "id"));	
				code = json_number_value(json_object_get(ret, "code"));	
				msg = json_string_value(json_object_get(ret, "msg"));	

				if(id == NULL)
				{
					isErr = 1;
					sprintf((char*)output, "{\"error\":3,\"data\":{},\"message\":\"Json decode fail!\"}"); 
				}
				else if((int)code == 0)
				{
					json_object_del(ret, "code");
					json_object_del(ret, "msg");
  
					sprintf((char*)outputData, "%s,\"%s\":%d", outputData, "ratio", (int)json_number_value(json_object_get(ret, "getratio")));
					sprintf((char*)outputData, "%s,\"%s\":%d", outputData, "mode", (int)json_number_value(json_object_get(ret, "getmode")));
	
				}
				else
				{
					isErr = 1;
					sprintf((char*)output, "{\"error\":%d,\"data\":{\"id\":\"%s\"},\"message\":\"%s\"}", (int)code, id, msg); 
				}
				
			}
		}// end of get 硬件配置
				
		
		memcpy(outputData2, &outputData[1], strlen(outputData)-1);
		
		
		if(isErr == 0){
			sprintf((char*)output, "{\"error\":0,\"data\":{%s},\"message\":\"\"}", outputData2);
		}
		
		render((const char*)output);
		
	}// end of getpool
	
	else if(post != NULL && strcmp("2", post) == 0)
	{
		// 修改矿池信息
		char buf[2048]={0};
		char out[4096]={0};
		char output[4096]={0};
	 
		int isErr = 0, isSuccess=0;
		char* result ;
 
		const char *pool1address, *pool1miner, *pool1pwd; 
		const char *pool2address, *pool2miner, *pool2pwd; 
		const char *pool3address, *pool3miner, *pool3pwd; 
		 
		pool1address = trim((char*)param("pool1address"));
		pool1miner = trim((char*)param("pool1miner"));
		pool1pwd = trim((char*)param("pool1pwd"));
		
		pool2address = trim((char*)param("pool2address"));
		pool2miner = trim((char*)param("pool2miner"));
		pool2pwd = trim((char*)param("pool2pwd"));
		
		pool3address = trim((char*)param("pool3address"));
		pool3miner = trim((char*)param("pool3miner"));
		pool3pwd = trim((char*)param("pool3pwd"));
 
		
		sprintf((char*)buf, 
		"{\"id\":\"setpool\", \"pools\":[{\"no\":1, \"addr\":\"%s\", \"user\":\"%s\", \"pass\":\"%s\"}, {\"no\":2, \"addr\":\"%s\", \"user\":\"%s\", \"pass\":\"%s\"}, {\"no\":3, \"addr\":\"%s\", \"user\":\"%s\", \"pass\":\"%s\"}]}\n", 
		pool1address, pool1miner, pool1pwd, pool2address, pool2miner, pool2pwd, pool3address, pool3miner, pool3pwd
		); 
		
		
		result = sendMessage(buf, strlen(buf), (char*)(&out), sizeof(out));
		
		// {"id":"setpool", "ret":{"code":0}}
		
		if (strcmp("Create failed!", result) == 0 || strcmp("Connect failed!", result) == 0)
		{
			isErr = 1;
			sprintf((char*)output, "{\"error\":1,\"data\":{},\"message\":\"Connect miner failed!\"}"); 
		}
		else if( strcmp("Read timeout!", result) == 0 || strcmp("Error in select!", result) == 0 || strlen(out) == 0)
		{
			isErr = 1;
			sprintf((char*)output, "{\"error\":2,\"data\":{},\"message\":\"Miner return failed!\"}"); 
		}
		else
		{
			json_error_t err;
			json_t *jst, *ret;
			
			
			// sprintf((char*)out, "123123%s", out); 
			
			jst = JSON_LOADS((const char*)out, &err);
			
			ret = json_object_get(jst, "ret");
			
			const char *id, *msg;
			double code;
		 
			id = json_string_value(json_object_get(jst, "id"));	
			code = json_number_value(json_object_get(ret, "code"));	
			msg = json_string_value(json_object_get(ret, "msg"));	
			
			// json_object_del(ret, "code");
			// json_object_del(ret, "msg");

			// print("id=%s, msg=%s, code=%d, out=%s", id, msg, (int)code, out);
			if(id == NULL)
			{
				isErr = 1;
				sprintf((char*)output, "{\"error\":3,\"data\":{},\"message\":\"Json decode fail!\"}"); 
			}
			else if((int)code != 0)
			{
				isErr = 1;
				sprintf((char*)output, "{\"error\":%d,\"data\":{\"id\":\"%s\"},\"message\":\"%s\"}", (int)code, id, msg); 
			}
			 
		}

		// 设置风扇频率
		if(isErr == 0)
		{
			memset(buf, 0, sizeof(buf)/sizeof(char));
			memset(out, 0 ,sizeof(out)/sizeof(char));
	
			const char *fancontrol, *fanratio, *fanmode; 
			fancontrol = trim((char*)param("fancontrol"));
			fanratio = trim((char*)param("fanratio"));
			fanmode = trim((char*)param("fanmode"));
			
			int fancontrolB = 0;
			if(fancontrol != NULL && strcmp("on", fancontrol) == 0)
			{
				fancontrolB = 1;
			}
			
			char *mode;
			if(fanmode == NULL || strcmp("", fanmode) == 0)
			{
				 
				mode = malloc(strlen("normal"));

				memcpy(mode, "normal", strlen("normal"));
			}else
			{
				mode = malloc(strlen(fanmode));
				memcpy(mode, fanmode, strlen(fanmode));
			}

			sprintf((char*)buf, "{\"id\":\"sethw\", \"fan\":{\"control\":%s, \"ratio\":%s}, \"mode\":\"%s\"}\n", 
			B2STR(fancontrolB), fanratio, mode
			); 
			
			result = sendMessage(buf, strlen(buf), (char*)(&out), sizeof(out));
			
			// send: {"id":"board", "ret":{"code": 0, "chainnum": 0, "boards": [{"no": 1, "chipnum": 76, "error": 0, "freq": 660, "rtpow": "130G", "idealpow":"141G", "tempnum":"0", "pcbtemp":"", "intmp": 59.120000, "outtmp": 61.380000, "state": true, "false":[]},{"no": 2, "chipnum": 76, "error": 0, "freq": 660, "rtpow": "124G", "idealpow":"141G", "tempnum":"0", "pcbtemp":"", "intmp": 55.220000, "outtmp": 58.170000, "state": true, "false":[]},{"no": 3, "chipnum": 76, "error": 0, "freq": 660, "rtpow": "136G", "idealpow":"141G", "tempnum":"0", "pcbtemp":"", "intmp": 60.220000, "outtmp": 62.050000, "state": true, "false":[]}]}}

			
			if (strcmp("Create failed!", result) == 0 || strcmp("Connect failed!", result) == 0)
			{
				isErr = 1;
				sprintf((char*)output, "{\"error\":1,\"data\":{},\"message\":\"Connect miner failed!\"}"); 
			}
			else if( strcmp("Read timeout!", result) == 0 || strcmp("Error in select!", result) == 0 || strlen(out) == 0)
			{
				isErr = 1;
				sprintf((char*)output, "{\"error\":2,\"data\":{},\"message\":\"Miner return failed!\"}"); 
			}
			else
			{
				json_error_t err;
				json_t *jst, *ret;
				
				jst = JSON_LOADS((const char*)out, &err);
				
				ret = json_object_get(jst, "ret");
				
				const char *id, *msg;
				double code;
			 
				id = json_string_value(json_object_get(jst, "id"));	
				code = json_number_value(json_object_get(ret, "code"));	
				msg = json_string_value(json_object_get(ret, "msg"));	
				 
				if(id == NULL)
				{
					isErr = 1;
					sprintf((char*)output, "{\"error\":3,\"data\":{},\"message\":\"Json decode fail!\"}"); 
				}
				else if((int)code != 0)
				{
					isErr = 1;
					sprintf((char*)output, "{\"error\":%d,\"data\":{\"id\":\"%s\"},\"message\":\"%s\"}", (int)code, id, msg); 
				}else
				{
					isSuccess = 1;
				}
			}	
		}
		
		if(isSuccess == 1)
		{
			sprintf((char*)output, "{\"error\":0,\"data\":{},\"message\":\"\"}"); 
		}
		else if(isErr == 0)
		{// 未知原因没有进入成功分支
			sprintf((char*)output, "{\"error\":2,\"data\":{},\"message\":\"操作失败\"}"); 
		}


		render((const char*)output);

	}
	else
	{
		render("{\"data\":\"machineConfig\"}");
	}
	
	
}



static void systempage(HttpConn *conn, EspAction *action)
{ 
	espRenderView(conn, "view/system.esp", 0);
}

static void systemConfig(HttpConn *conn, EspAction *action)
{ 
	const char* post; 
	post = param ("post");
 
	if(post != NULL && strcmp("2", post) == 0)
	{
		const char* nowpwd; 
		const char* newpwd;
		const char* compwd;
		nowpwd = trim((char*)param("nowpwd"));
		newpwd = trim((char*)param("newpwd"));
		compwd = trim((char*)param("compwd"));
		
		
		char output[8192]={0};
		
		
		if(nowpwd == NULL || newpwd == NULL || strlen(nowpwd) == 0 || strlen(newpwd) == 0)
		{
			sprintf((char*)output, "{\"error\":1,\"data\":{},\"message\":\"当前密码或者新密码错误\"}"); 
		}
		else if (nowpwd == newpwd)
		{	
			sprintf((char*)output, "{\"error\":1,\"data\":{},\"message\":\"当前密码和新密码不能相同\"}"); 
		}
		else if (strcmp(newpwd, compwd) != 0)
		{	
			sprintf((char*)output, "{\"error\":1,\"data\":{},\"message\":\"两次输入的密码不相同\"}"); 
		}	
		else
		{
			char buf[1024]={0};
			char out[4096]={0};
			 
			sprintf((char*)buf, "{\"id\":\"changepass\",\"pass\":\"%s\",\"newpass\":\"%s\"}\n", nowpwd, newpwd); 
			
			char* result ;
			result = sendMessage(buf, strlen(buf), (char*)(&out), sizeof(out));
			
			// {"id":"changepass", "ret":{"code":0}}
			// {"id":"changepass", "ret": {"code": 1002, "msg":"password error"}}
			// {"id":"changepass", "ret": {"code": 1017, "msg":"invalid newpass"}}
				
 		
			if (strcmp("Create failed!", result) == 0 || strcmp("Connect failed!", result) == 0)
			{
				sprintf((char*)output, "{\"error\":1,\"data\":{},\"message\":\"Connect miner failed!\"}"); 
			}
			else if( strcmp("Read timeout!", result) == 0 || strcmp("Error in select!", result) == 0 || strlen(out) == 0)
			{
				// isErr = 1;
				sprintf((char*)output, "{\"error\":2,\"data\":{},\"message\":\"Miner return failed!\"}"); 
			}
			else
			{
				json_error_t err;
				json_t *jst, *ret;
				
				jst = JSON_LOADS((const char*)out, &err);
				
				ret = json_object_get(jst, "ret");
				
				const char *id, *msg;
				double code;
			 
				id = json_string_value(json_object_get(jst, "id"));	
				code = json_number_value(json_object_get(ret, "code"));	
				msg = json_string_value(json_object_get(ret, "msg"));	
				
				// json_object_del(ret, "code");
				// json_object_del(ret, "msg");

				// sprintf((char*)output, "%s:%s:%d", id, msg, (int)code);
		 
				 
				if(id == NULL)
				{
					 
					sprintf((char*)output, "{\"error\":3,\"data\":{},\"message\":\"Json decode fail!\"}"); 
				}
				else if((int)code == 0)
				{
					sprintf((char*)output, "{\"error\":0,\"data\":{},\"message\":\"\"}"); 
				}
				else
				{
					sprintf((char*)output, "{\"error\":%d,\"data\":{\"id\":\"%s\"},\"message\":\"%s\"}", (int)code, id, msg); 
				}
			}		
			
		}
 
		render((const char*)output);
	}
	else
	{
		
		render("{\"data\":\"systemConfig\"}");
	}
}



static void logConfig(HttpConn *conn, EspAction *action)
{ 
	const char* post; 
	post = param ("post");
 
	if(post != NULL && strcmp("1", post) == 0)
	{
		 //获取当前日志
		// char output[8192]={0};
		char *output = (char*)malloc(1024);
		
		char buf[1024]={0};
		char out[65536]={0};
		 
		
		sprintf((char*)buf, "{\"id\":\"log\",\"history\":false}\n"); 
		
		char* result = malloc(sizeof(char));
		// result = malloc(sizeof(char));
		 
		int logbuffSize ;
		int historyCount = 1;	
		result = sendLogMessage(buf, strlen(buf), (char*)(&out), sizeof(out), 1, (int *)(&historyCount), (int *)(&logbuffSize));
		//  {"id":"log", "ret":{"code":0, "ctime": "2023-02-14 04:09:53", "mtime": "2023-02-14 04:09:53", "len": 2630955}}
 
		// print("sendLogMessage 4.0 out:%s\n", out);
		char* logbuff = result;
		// print("sendLogMessage 5.0  logbuff:%.32s\n", logbuff);
		
		
		if (strcmp("Create failed!", result) == 0 || strcmp("Connect failed!", result) == 0)
		{
			sprintf((char*)output, "{\"error\":1,\"data\":{},\"message\":\"Connect miner failed!\"}"); 
		}
		else if( strcmp("Read timeout!", result) == 0 || strcmp("Error in select!", result) == 0 || strlen(out) == 0)
		{
			// isErr = 1;
			sprintf((char*)output, "{\"error\":2,\"data\":{},\"message\":\"Miner return failed!\"}"); 
		}
		else
		{
			 
			json_error_t err;
			json_t *jst, *ret;
  
			jst = JSON_LOADS((const char*)out, &err);
			 
			ret = json_object_get(jst, "ret");
			
			const char *id, *msg;
			double code;
			print("sendLogMessage 7, len all logbuff:%d, log32:%.32s\n", strlen(logbuff), logbuff);
			id = json_string_value(json_object_get(jst, "id"));	
			code = json_number_value(json_object_get(ret, "code"));	
			msg = json_string_value(json_object_get(ret, "msg"));	
			 
			if(id == NULL)
			{
				// isErr = 1;
				sprintf((char*)output, "{\"error\":3,\"data\":{},\"message\":\"Json decode fail!\"}"); 
			}
			else if((int)code == 0)
			{
				// logbuff 换行符转义
				char* logbuff2 = (char*)malloc((int)(logbuffSize * 2));
				
				int li = 0;
				int li2 = 0;
				int countL1 = 0;
				int countL2 = 0;
				int countL3 = 0;	
				int countL4 = 0;	
				int countL5 = 0;	
				char c = '\0';
				memcpy(&c, &logbuff[li], 1);

				while(c != '\0')
				{
					// 转义
					if(c == '\n')
					{
						// print("sendLogMessage 8.1, li: %d, li2: %d\n", li, li2);
						memcpy(&logbuff2[li2], "<br/>", 5);
						countL1++;
						li2+=5;
					}
					else if(c == '%')
					{
						// print("sendLogMessage 8.2, li: %d, li2: %d\n", li, li2);
						memcpy(&logbuff2[li2], "%%", 2);
						countL2++;
						li2+=2;
					}
					else if(c == '"')
					{
						 
						memcpy(&logbuff2[li2], "\\\"", 2);
						countL3++;
						li2+=2;
					}
					else if(c == '\\')
					{
						 
						memcpy(&logbuff2[li2], "\\\\", 2);
						countL3++;
						li2+=2;
					}
					else if(c == '\t')
					{
						memcpy(&logbuff2[li2], "&nbsp;&nbsp;", 12);
						countL5++;
						li2+=12;
					}
					// htmlspecialchars
					else if(c == '<')
					{
						 
						memcpy(&logbuff2[li2], "&lt;", 4);
						countL4++;
						li2+=4;
					}
					else if(c == '>')
					{
						 
						memcpy(&logbuff2[li2], "&gt;", 4);
						countL4++;
						li2+=4;
					}
					else
					{
						// logbuff2[li2] = logbuff[li];
						memcpy(&logbuff2[li2], &logbuff[li], 1);
						li2++;
					}

					li++;
					memcpy(&c, &logbuff[li], 1);
				}
 
				// logbuff2[li2] = '\0';
				// memcpy(&logbuff2[li2], '\0', 1);
				
				print("sendLogMessage 9, li: %d, li2: %d, c1:%d, c2:%d, c3:%d, c4:%d, c5:%d, logbuff2 len:%d\n", 
				li, li2, countL1, countL2, countL3, countL4, countL5, strlen(logbuff2));
				
				
				if(li2+50 > 1024)
				{
					output = (char*)malloc((int)(li2+50));
					// output[(int)(li2+50)]={0};
				}
				
				sprintf((char*)output, "{\"error\":0,\"data\":{\"text\":\"%s\"},\"message\":\"%d\"}", logbuff2, logbuffSize); 
			}
			else
			{
				sprintf((char*)output, "{\"error\":%d,\"data\":{\"id\":\"%s\"},\"message\":\"%s\"}", (int)code, id, msg); 
			}
		}		
		 
			
		
		render((const char*)output);
		
		
	}// end of 获取当前日志
	else if(post != NULL && strcmp("2", post) == 0)
	{
		// 获取历史日志
		// 历史日志的话最多会返回3次
 
		// char output[8192]={0};
		char *output = (char*)malloc(1024);
		char buf[1024]={0};
		char out[65536]={0};
 
		sprintf((char*)buf, "{\"id\":\"log\",\"history\":true}\n"); 
		int historyCount = 1;	
		
		char* result1 = malloc(sizeof(char));
		int logbuffSize1=0;
		result1 = sendLogMessage(buf, strlen(buf), (char*)(&out), sizeof(out), 0, (int *)(&historyCount), (int *)(&logbuffSize1));
		
		char* result2 = malloc(sizeof(char));
		memset(out, 0 ,sizeof(out)/sizeof(char));
		int logbuffSize2=0;
		result2 = sendLogMessage(buf, strlen(buf), (char*)(&out), sizeof(out), 0, (int *)(&historyCount), (int *)(&logbuffSize2));
		
		
		char* result3 = malloc(sizeof(char));
		memset(out, 0 ,sizeof(out)/sizeof(char));
		int logbuffSize3=0;
		result3 = sendLogMessage(buf, strlen(buf), (char*)(&out), sizeof(out), 0, (int *)(&historyCount), (int *)(&logbuffSize3));
		
		// print("sendLogMessage 5, historyCount:%d\n", historyCount);
		int logbuffSize = logbuffSize1 + logbuffSize2 + logbuffSize3;
		
		//  {"id":"log", "ret":{"code":0, "ctime": "2023-02-14 04:09:53", "mtime": "2023-02-14 04:09:53", "len": 2630955}}
		char* result = malloc(logbuffSize);
		
		if(logbuffSize1 > 0)
		{
			memcpy(&result[0], result1, logbuffSize1);
		}
		
		// print("sendLogMessage 5.1\n");
		
		if(logbuffSize2 > 0)
		{
			memcpy(&result[logbuffSize1], result2, logbuffSize2);
		}
		
		// print("sendLogMessage 5.2\n");
		
		if(logbuffSize3 > 0)
		{
			memcpy(&result[logbuffSize1+logbuffSize2], result3, logbuffSize3);
		}
		
		// print("sendLogMessage 5.3\n");
		
		
		char* logbuff = result;
		
		print("sendLogMessage 6.0 size1:%d:%d, size2:%d:%d, size3:%d:%d\n", 
		logbuffSize1, strlen(result1), logbuffSize2, strlen(result2), logbuffSize3, strlen(result3));
		 
		if (strcmp("Create failed!", result) == 0 || strcmp("Connect failed!", result) == 0 || strlen(out) == 0)
		{
			sprintf((char*)output, "{\"error\":1,\"data\":{},\"message\":\"Connect miner failed!\"}"); 
		}
		// else if( strcmp("Read timeout!", result) == 0 || strcmp("Error in select!", result) == 0 || strlen(out) == 0)
		// {
			// isErr = 1;
			// sprintf((char*)output, "{\"error\":2,\"data\":{},\"message\":\"Miner return failed!\"}"); 
		// }
		else
		{
			 
			json_error_t err;
			json_t *jst, *ret;
			
			jst = JSON_LOADS((const char*)out, &err);
			
			ret = json_object_get(jst, "ret");
			
			const char *id, *msg;
			double code;
			
			print("sendLogMessage 7, len all logbuff:%d, log32:%.32s\n", strlen(logbuff), logbuff);
			
			id = json_string_value(json_object_get(jst, "id"));	
			code = json_number_value(json_object_get(ret, "code"));	
			msg = json_string_value(json_object_get(ret, "msg"));	
			 
 		
			if(id == NULL)
			{
				// isErr = 1;
				sprintf((char*)output, "{\"error\":3,\"data\":{},\"message\":\"Json decode fail!\"}"); 
			}
			else if((int)code == 0)
			{
				// print("sendLogMessage 8 \n");
				
				// logbuff 换行符等转义 
				char* logbuff2 = (char*)malloc((int)(logbuffSize * 2));
			 
				int li = 0;
				int li2 = 0;
				int countL1 = 0;
				int countL2 = 0;
				int countL3 = 0;					 
				int countL4 = 0;
				int countL5 = 0;
				char c = '\0';
				memcpy(&c, &logbuff[li], 1);
	 	
				while(c != '\0')
				{
					// 转义
					if(c == '\n')
					{
						// print("sendLogMessage 8.1, li: %d, li2: %d\n", li, li2);
						memcpy(&logbuff2[li2], "<br/>", 5);
						countL1++;
						li2+=5;
					}
					else if(c == '%')
					{
						// print("sendLogMessage 8.2, li: %d, li2: %d\n", li, li2);
						memcpy(&logbuff2[li2], "%%", 2);
						countL2++;
						li2+=2;
					}
					else if(c == '"')
					{
						 
						memcpy(&logbuff2[li2], "\\\"", 2);
						countL3++;
						li2+=2;
					}
					else if(c == '\\')
					{
						 
						memcpy(&logbuff2[li2], "\\\\", 2);
						countL3++;
						li2+=2;
					}
					else if(c == '\t')
					{
						memcpy(&logbuff2[li2], "&nbsp;&nbsp;", 12);
						countL5++;
						li2+=12;
					}
					// htmlspecialchars
					else if(c == '<')
					{
						 
						memcpy(&logbuff2[li2], "&lt;", 4);
						countL4++;
						li2+=4;
					}
					else if(c == '>')
					{
						 
						memcpy(&logbuff2[li2], "&gt;", 4);
						countL4++;
						li2+=4;
					}
					else
					{
						 
						memcpy(&logbuff2[li2], &logbuff[li], 1);
						li2++;
					}

					li++;
					memcpy(&c, &logbuff[li], 1);
				}
 
				// logbuff2[li2] = '\0';
				// memcpy(&logbuff2[li2], '\0', 1);
				
				// print("sendLogMessage 9, li: %d, li2: %d, logbuff2 len:%ld\n", li, li2, strlen(logbuff));
				 
				print("sendLogMessage 9, li: %d, li2: %d, c1:%d, c2:%d, c3:%d, c4:%d, c5:%d, logbuff2 len:%d\n", 
				li, li2, countL1, countL2, countL3, countL4, countL5, strlen(logbuff2));
				
				if(li2+50 > 1024)
				{
					output = (char*)malloc((int)(li2+50));
					
					
				}
				
				sprintf((char*)output, "{\"error\":0,\"data\":{\"text\":\"%s\"},\"message\":\"%d\"}", logbuff2, logbuffSize); 
			}
			else
			{
				sprintf((char*)output, "{\"error\":%d,\"data\":{\"id\":\"%s\"},\"message\":\"%s\"}", (int)code, id, msg); 
			}
		}		
 
		render((const char*)output);
		
	}	
	else
	{
		
		render("{\"data\":\"logConfig\"}");
	}
}


static void userpage(HttpConn *conn, EspAction *action)
{ 
	espRenderView(conn, "view/user.esp", 0);
}



// ESP_EXPORT int esp_controller_app_user(HttpRoute *route, MprModule *module) {
// dzt20230209 appname时不时会变
ESP_EXPORT int esp_controller_espapp_user(HttpRoute *route, MprModule *module) {
	
 
    espDefineAction(route, "user/login", loginPage);
	espDefineAction(route, "user/loginpost", login);
	
	espDefineAction(route, "user/userpanel", userPanel);
 


	espDefineAction(route, "user/fir", firpage);
	espDefineAction(route, "user/firconfig", firConfig);
	
	espDefineAction(route, "user/ip", ippage);
	espDefineAction(route, "user/ipconfig", ipConfig);
	
	
	espDefineAction(route, "user/log", logpage);
	espDefineAction(route, "user/logconfig", logConfig);
	
	
	espDefineAction(route, "user/machine", machinepage);
	espDefineAction(route, "user/machineconfig", machineConfig);
	
	
	espDefineAction(route, "user/system", systempage);
	espDefineAction(route, "user/systemconfig", systemConfig);
	
	espDefineAction(route, "user/user", userpage);
	
	
	
    return 0;

}
 
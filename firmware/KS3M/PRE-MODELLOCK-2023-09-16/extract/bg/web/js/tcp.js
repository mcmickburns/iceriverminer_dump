
//webSocket 服务端地址
var wsUrl = 'ws://localhost:4111/'
//webSocket 对象
var ws;
//webSocket 尝试重新创建webSocket 定时
var reconnectTimeOut;
//心跳重试次数  服务端3次无响应就断开重连
var heartCheckNum = 0;
//webSocket 链接锁，用来保证只有一个客户端与服务端只生成一个连接。
var lockReconnect = false;
//webSocket 关闭的类型 1默认。 2息屏关闭 
var closeWsType = 1;
//判断浏览器支持
if ("WebSocket" in window) {
	console.log("支持WebSocket")
} else {
	alert("该浏览器不支持WebSocket")
}
//创建webSocket
var createWebSocket = function (wsUrl) {
	//console.log(wsUrl)
	try {
		//初始化webSocket连接
		ws = new WebSocket(wsUrl);
		webSocketInit();
	} catch (e) {  //失败
		alert("createWebSocket catch", [e]);
		//尝试webSocket重连
		lockReconnect = false;
		webSocketReconnect(wsUrl);
	}
};
//初始化webSocket连接，成功后执行
var webSocketInit = function () {
	//断开webSocket连接成功触发事件
	ws.onclose = function (event) {
		//alert("连接已关闭。。。");
		//尝试webSocket重连
		lockReconnect = false;
		webSocketReconnect(wsUrl);
	};
	//发生错误时执行的回调函数
	ws.onerror = function (event) {
		//alert("连接错误。。。", [event]);
		//尝试webSocket重连
		lockReconnect = false;
		webSocketReconnect(wsUrl);
	};
	//连接建立成功,发送信息
	ws.onopen = function (event) {
		//例如
		var message = '{"id":"login","user":"admin","pass":"123456"}\n';
		console.log(message)
		ws.send(message); 
 
		//心跳检测启动
		heartCheck.start();
	};
	//收到来自服务端的消息时被调用
	ws.onmessage = function (event) {
		//let date = new Date();
		//let newdate = date.toLocaleString('chinese', {hour12: false});   //获取24小时制，中国时间，打印出   2019/01/03/  08:40:32
		//console.log("接收到 WebSocket消息:", [event, newdate]);
		//var data=json.parse(event);
		//处理你的业务
		//处理你的业务
		//处理你的业务
		//处理你的业务
 
		if (event.data == "1") {
			heartCheckNum = 0;
			//console.log("接收到服务端的心跳回应:", event.data);
		}else{
			//处理收到的消息.
			console.log(JSON.stringify(event.data));
			//alert("消息:"+JSON.stringify(event.data))
		}
		//接收一次后台推送的消息，即进行一次心跳检测重置
		heartCheck.reset();
	};
};
 
//webSocket重试
var webSocketReconnect = function (url) {
	console.log("webSocket 连接断开，正在尝试重新建立连接。。。");
	if(closeWsType == 2){
			return;
	}
	if (lockReconnect) {
		return;
	}
	lockReconnect = true;
	heartCheckNum = 0;
	heartCheck.stop();
	//js中清楚setTimeout的定时触发设置，之所以加个timer，是为了方便第二次赋值给timer。
	//也就是说直接clearTImeout（timer）则timer就不存在了 再次访问就是error了。
	//而timer&&clearTimeout(timer)则将timer 变成undefined
	reconnectTimeOut && clearTimeout(reconnectTimeOut);
	reconnectTimeOut = setTimeout(function () {
		createWebSocket(url);
	}, 4000)
};
 
/*
 *心跳检测:
 *发送方按照一定规则（周期性发送、空闲发送等等）向接收方发送固定格式的消息，接受方收到消息后回复一个固定格式的消息 ，
 *如果长时间没有收到，则认为当前连接失效，将其断开。
 *注：发送方可以是客户端或者服务端，根据实际情况而定，常见是客户端作为发送方。
 *webSocket一般是间隔90秒内无操作会自动断开，因此，需要加入一个心跳机制，以防止ws断开
 *这里为3秒，倒计时3秒内无操作则进行一次访问，有操作则重置计时器。
 */
var heartCheck = {
	timeout: 3000,//3秒
	timeoutObj: null,
	reset: function () {
		//接收成功一次推送，就将心跳检测的倒计时重置为30秒
		clearTimeout(this.timeoutObj);//重置倒计时
		this.start();
	},
	start: function () {
		//启动心跳检测机制，设置倒计时30秒一次
		this.timeoutObj = setTimeout(function () {
			//console.log("webSocket  心跳。。。" + heartCheckNum);
			//心跳
			//与服务端定制ping pong,客户端发送0,服务端回应1 服务端三次没回应 就断开重连
			if (heartCheckNum === 3) {
				//关闭链接  链接断开以后就会自动重试，所以不需要其他处理
				ws.close();
			} else {
				//readyState 表示连接状态，可以是以下值：
				//0 - 表示连接尚未建立。
				//1 - 表示连接已建立，可以进行通信。
				//2 - 表示连接正在进行关闭。
				//3 - 表示连接已经关闭或者连接不能打开。
				//if (ws.readyState === 1) {
				//}
				ws.send("0");
				heartCheckNum++;
			}
			heartCheck.reset();
		}, this.timeout)
	},
	stop: function () {
		//接收成功一次推送，就将心跳检测的倒计时重置为30秒
		clearTimeout(this.timeoutObj);//重置倒计时
	},
	//onopen连接上，就开始start及时，如果在定时时间范围内，onmessage获取到了服务端消息，
	//就重置reset倒计时，距离上次从后端获取消息30秒后，执行心跳检测，看是不是断了。
};
//监听浏览器关闭 断开ws
window.onbeforeunload = function () {
	if (ws) {
		ws.close();
	}
}
window.addEventListener('pagehide', function (e) {   
	if (ws) {
		ws.close();
		closeWsType = 2;
	}
},false);
document.addEventListener('visibilitychange', function () {
	// 用户息屏、或者切到后台运行 （离开页面）
	if (document.hidden) {
		if (ws) {
		  ws.close();
		  closeWsType = 2;
		}
	}else{
		closeWsType = 1;
		if (ws.readyState === 1) {
		}else{//息屏打开重连
			createWebSocket(wsUrl);
		}
	}
})
//开始创建webSocket连接
//createWebSocket(wsUrl);











translates_en={
		"在线":"online",
		"离线":"offline",
		"正常":"Normal",
		"异常":"Abnormal",
		"算力曲线图":"Miner hashrate",
		"左键图像缩放,按住ctrl和左键可以滑动图像":"Left click to zoom the image. Press and hold ctrl and left click to slide the image",
		"矿机没有连接":"The machine is not connected",
		"提示":"Prompt",
		"确认恢复出厂设置":"Confirm factory reset",
		"确定":"OK",
		"取消":"Cancel",
		"操作成功":"Operation succeeded",
		"请求超时":"Request timeout",
		"确认重启矿机":"Confirm restarting the mining machine",
		"天":"d",
		"时":"h",
		"分":"m",
		"秒":"s",
		"矿机定位":"Locate miner",
		"MAC地址":"MAC",
	
		"子网掩码":"Subnet mask",
		"升级固件":"Update Firmware",
		"请选择文件":"Please select a file",
		"登录名或密码不能为空":"Name or password cannot be empty",
		"芯片状态":"Chip Status",
		"等待中":"Waiting",
		"机器已离线":"Machine is offline",
		"确认登出账号":"Logout confirm",
		
		"用户界面":"User interface",
		"用户面板":"User Panel",
		"矿机设置":"Mining setting",
		"IP设置":"IP Settings",
		"系统":"System",
		"矿机日志":"Mining log",
		"算法":"Algorithm",
		"连接中":"Connected",
		"刷新时间":"Refresh time",
		"中文":"cn",
		"英文":"en",
		"固件版本":"Firmware version",
		"版本信息":"Version",
		"IP地址":"IP",
		"MAC":"MAC",
		"固件类型":"Firmware type",
		"恢复出厂设置":"Restore factory settings",
		"重启矿机":"Restart",
		"实时算力":"Real time hash",
		"网络状态":"Network status",
		"风扇转速":"Fan speed",
		"矿机温度":"Miner temp.",
		"平均总算力":"Average total hash",
		"矿池拒绝率":"Pool rejection rate",
		"矿机运行时间":"Miner running time",
		"矿池":"Pool",
		"挖矿地址":"Mining address",
		"矿工名":"Miner",
		"矿池连接":"Pool state",
		"Diff":"Diff",
		"Priority":"Priority",
		"Accepted":"Accepted",
		"DiffA":"DiffA",
		"DiffR":"DiffR",
		"Rejected":"Rejected",
		"LSDiff":"LSDiff",
		"LSTime":"LSTime",
		"算力板":"Hash board",
		"算力板状态":"Hash board",
		"芯片数量":"Number of chips",
		"硬件错误":"Hardware error",
		"运行频率":"Operating frequency",
		"理论算力":"Theoretical Hash",
		"进风口温度":"Air inlet temperature",
		"出风口温度":"Air outlet temperature",
		"温度1":"TEMP 1",
		"温度2":"TEMP 2",
		"芯片状态":"Chip Status",
		"风扇":"Fans",
		"风扇1转速":"Fan 1",
		"风扇2转速":"Fan 2",
		"风扇3转速":"Fan 3",
		"风扇4转速":"Fan 4",
		"矿池配置":"Pool configuration",
		"密码":"Password",
		"选填":"Optional",
		"硬件配置":"Hardware configuration",
		"IP配置":"IP configuration",
		"网络信息":"Network information",
		"主机名":"Host name",
		"协议":"Protocol",
		"子网掩码":"Subnet mask",
		"网关":"Gateway",
		"DNS 服务器":"DNS server",
		"保存":"Save",
		"修改密码":"Reset password",
		"固件升级":"Firmware upgrade",
		"固件文件":"Firmware file",
		"保留配置":"Keep the settings",
		"选择文件":"Select File",
		"登录界面":"Login",
		"登录":"Login",
		"登录名":"Name",
		"当前密码或者新密码错误":"Current password or new password is incorrect",
		"两次输入的密码不相同":"The passwords entered twice are different",
 
		"风扇转速百分比":"Fan speed(percent)",
		"工作模式":"Mode",
		"睡眠":"Sleep",
		"当前密码":"Current password",
		"新密码":"New password",
		"确认密码":"Confirm password",
		"当前日志":"Current log",
		"历史日志":"History Log",
		"升级固件":"Update",
		"不能为空":"Cannot be empty",
		"当前密码和新密码不能相同":"Current password and new password cannot be the same",
		"登出":"logout",
		"请选择文件":"Please select a file",
		"文件上传失败":"File upload failed",
		"复制完成":"Copy success",
		"复制失败":"Copy failed",
		"主机名,IP地址,子网掩码,网关,不能为空":"Machine name, IP, Subnet mask, Gateway cannot be empty",
		"文件超过100M， 请重新选择":"The file exceeds 100M, please select again",
		"上传文件格式错误":"Upload file format error",
		"矿池地址":"Pool addr.", 
		"钱包地址/矿工名":"Wallet/Worker", 
		"展开":"Expand",
		"用户设置":"User setting",
		"首页":"Home", 
		"未连接":"Unconnected", 
		"5分钟算力":"5 mins hashrate", 
		"15分钟算力":"15 mins hashrate", 
		"30分钟算力":"30 mins hashrate", 
};


function t(s, lan=""){
	if(lan == ""){
		lan = getCookie('language');
		if(lan == ""){
			lan = "en";
			setCookie('language', lan);
		}
	}
	
	if(translates_en.hasOwnProperty(s) && lan=="en"){
		if(translates_en[s]!="")
			return translates_en[s];
		else
			return s;
	}
	else
		return s;
	
	
}


function tranlateAll(){
	var lan = getCookie('language');
	if (lan == ""){
		lan = "en";
		setCookie('language', lan);
		document.title = t(document.title, lan);
		$(".languagecss").val(lan);
	}else{
		document.title = t(document.title, lan);
		$(".languagecss").val(lan);
	}
	
	$(".lan-trans").each(function(){
		$(this).html(t($(this).html(), lan));
	});
}



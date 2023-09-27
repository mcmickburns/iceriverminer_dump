$(document).ready(function(){
	
	$(".left .userMenu").click(function(){
		menu();
		userMenu();
	});
	$(".left .fpgaMenu").click(function(){
		menu();
		fpgaMenu();
	});
	$(".left .ipMenu").click(function(){
		menu();
		ipMenu();
	});
	$(".left .sysMenu").click(function(){
		menu();
		sysMenu();
	});
	$(".left .firMenu").click(function(){
		menu();
		firMenu();
	});
	$(".left .logMenu").click(function(){
		menu();
		logMenu();
	});

	var lan=getCookie('language');
	if(lan != ""){
		
		$(".right .languagecss").val();
	}
	
	$(".right .languagecss").change(function(){
		var p1=$(this).children('option:selected').val();
		setCookie("language",p1,60*60*24*1000);
		window.location.reload();
	});
	
	
	
	
	$(".content7 .restorecss").click(function(){
		restore();
	});
	
	$(".content7 .rebootcss").click(function(){
		reboot();
	});
	
	$(".content1 .logoutcss").click(function(){
		bootbox.confirm({
			title : t(""),
			message: t("确认登出账号")+"?", 
			buttons: {
				confirm: {label: t("确定")},
				cancel:{label:t("取消")}
					},        
			callback: function(result) {
				if(result) {
					delCookie("ctime");
					window.location.href="/user/login";
			    }else{
					return;
			    };
			}
		});
	});
	
	$(document).on("click",".machine_top .switch-box-slider",function(){
		 var checked=0;
		 if($(this).hasClass("checked1")){
			 checked=0;
		 }
		 else{
			 checked=1;
		 }
		 locate(checked);
	});
	
	var ctime=getCookie('ctime');
	if(ctime!=1){
		window.location.href="/user/login";
	}else{
		
		
		// debugger
		//getlist();
		interval();
		userMenu();
	}
 
});

function getlist(){
	
	$.ajax({
  		 url: '/user/userpanel',
  	     type:'POST',
  	     dataType:'json',
  		 data: {"post":1},
  		 async: true,
  		 timeout:200000,
  	     success:function(re){  	    	 
  	    	 login(re);
  	    	 // content1switchbox(re.data);
  	    	 if(re.error!=0 || re.data==""){
  	    		setStatus(0);
  	    	 }
  	    	 else{
  	    		 //界面数据显示
  	    		content1(re.data);
  	    		content7(re.data);
  	    		 
  	    	 }
  	     },
	     error:function(XMLHttpRequest, textStatus, errorThrown) {
	    	 if(textStatus == 'timeout'){
	    		 console.log(new Date().toGMTString()+' /user/userpanel:'+XMLHttpRequest.status+': '+t("请求超时"));
	    	 }
	    	 else{
	    		 // bootbox.alert(XMLHttpRequest.status+": "+textStatus);
	    		 console.log(new Date().toGMTString()+' /user/userpanel:'+XMLHttpRequest.status+": "+textStatus);
	    	 } 
	     }});
}

function content1(data){
	
	var fpgatype="";
	if(data.hasOwnProperty("model"))
		fpgatype=data.model;
	
	var algo="";
	if(data.hasOwnProperty("algo"))
		algo=data.algo;
	
	$(".right .content1 .fpgatypecss").html(fpgatype);
  	$(".right .content1 .algocss2").html(algo);
  	
	var refTime="";

	// 用本地时间代替
	// if(data.hasOwnProperty("refTime"))
		// refTime=data.refTime;

	const date = new Date();
	// console.log(formatDateTime(date));
	refTime = formatDateTime(date);
	
  	$(".right .content1 .algocss3").html(refTime);
  		
  	setStatus(1);
  	/*var status=0;
	if(data.hasOwnProperty("online")){
		status=data.online;
	}
	if(status==true){
  		$(".right .content1 .statuscss").html(t("在线"));
  		$(".right .content1 .statuscss").removeClass("statusLinecss");
  		$(".right .content1 .statuscss").removeClass("statusOffcss");
  		$(".right .content1 .statuscss").addClass("statusOncss");
	}
	else{
  		$(".right .content1 .statuscss").html(t("离线"));
  		$(".right .content1 .statuscss").removeClass("statusLinecss");
  		$(".right .content1 .statuscss").removeClass("statusOncss");
  		$(".right .content1 .statuscss").addClass("statusOffcss");
	}*/
	
	var fpgatype="";
	if(data.hasOwnProperty("model"))
		fpgatype=data.model;	
	$(".right .content5 .fpgatypecss").html(fpgatype);
	  		 	
}

function content1switchbox(data){
	// debugger
	var locate=0;
	if(data.hasOwnProperty("locate"))
		locate=data.locate;	
	$(".machine_top .linediv").html("");
	var temp="";
	var checkedhtml="checked2";
	var checked="";
	if(locate==1){
		checkedhtml="checked1";
		checked="checked";
	}
	//temp+='<label for="info" class="switch-box-label">'+t("矿机定位")+'</label>&nbsp;&nbsp;&nbsp;&nbsp;';
	temp+='<input id="line" class="switch-box-input" data-key="line" type="checkbox" '+checked+'/>';
	temp+='<label for="line" class="switch-box-slider '+checkedhtml+'"></label>';
	$(".machine_top .linediv").append(temp);
}

function content7(data){
	
	var ip="";
	if(data.hasOwnProperty("ip"))
		ip=data.ip;
	$(".right .content7 .ipcss").html(ip);
  		 
	var mac="";
	if(data.hasOwnProperty("mac"))
		mac=data.mac;
	$(".right .content7 .maccss").html(mac);	
	
	var firmware_version="";
	if(data.hasOwnProperty("firmver1")){
		firmware_version+=data.firmver1;
	}
	if(data.hasOwnProperty("firmver2")){
		firmware_version+= " "+data.firmver2;
	}
	if(data.hasOwnProperty("softver1")){
		firmware_version+= " "+data.softver1;
	}
	if(data.hasOwnProperty("softver2")){
		firmware_version+= " "+data.softver2;
	}
	$(".right .content7 .firmwareVersioncss").html(firmware_version);

	var firmware_type="";
	if(data.hasOwnProperty("firmtype"))
		firmware_type=data.firmtype;
	$(".right .content7 .firmwareTypecss").html(firmware_type);
	
}

function userMenu(){
	var oDate = new Date();var iM1 = oDate.getTime();
	$(".left .userMenu").addClass("menucssStatus");
	$.ajax({
		 url: '/user/user',
	     type:'GET',
	     dataType:'html',
		 data: {},
		 cache:false,
		 async: true,
		 timeout:200000,
	     success:function(re){
	    	 $(".right .srcollcss").append(re);
			 tranlateAll();
	    	 var oDate = new Date();var iM2 = oDate.getTime();
	    	 console.log("user "+(iM2-iM1)+"ms");
	    	 getlist2();
	     },
	     error:function(XMLHttpRequest, textStatus, errorThrown) {
	    	 loaded();
	    	 if(textStatus == 'timeout'){
	    		 console.log(XMLHttpRequest.status+": "+t("请求超时"));
	    	 }
	    	 else{
	    		 console.log(XMLHttpRequest.status+": "+textStatus);
	    	 } 
	     }});
}

function fpgaMenu(){
	var oDate = new Date();var iM1 = oDate.getTime();
	$(".left .fpgaMenu").addClass("menucssStatus");
	$.ajax({
		 url: '/user/machine',
	     type:'GET',
	     dataType:'html',
		 data: {},
		 async: true,
		 timeout:60000,
	     success:function(re){
	    	 $(".right .srcollcss").html(re);
			 tranlateAll();
	    	 var oDate = new Date();var iM2 = oDate.getTime();
	    	 console.log("fpga "+(iM2-iM1)+"ms");
	    	 machine_getlist();
	     },
	     error:function(XMLHttpRequest, textStatus, errorThrown) {
	    	 loaded();
	    	 if(textStatus == 'timeout'){
	    		 console.log(XMLHttpRequest.status+": "+t("请求超时"));
				 bootbox.alert(t("请求超时"));
	    	 }
	    	 else{
	    		 console.log(XMLHttpRequest.status+": "+textStatus);
	    	 } 
	     }});
}

function ipMenu(){
	var oDate = new Date();var iM1 = oDate.getTime();
	$(".left .ipMenu").addClass("menucssStatus");
	$.ajax({
		 url: '/user/ip',
	     type:'GET',
	     dataType:'html',
		 data: {},
		 async: true,
		 timeout:60000,
	     success:function(re){
	    	 $(".right .srcollcss").html(re);
			 tranlateAll();
	    	 var oDate = new Date();var iM2 = oDate.getTime();
	    	 console.log("ip "+(iM2-iM1)+"ms");
	    	 ip_getlist();
	     },
	     error:function(XMLHttpRequest, textStatus, errorThrown) {
	    	 loaded();
	    	 if(textStatus == 'timeout'){
	    		 console.log(XMLHttpRequest.status+": "+t("请求超时"));
				 bootbox.alert(t("请求超时"));
	    	 }
	    	 else{
	    		 console.log(XMLHttpRequest.status+": "+textStatus);
	    	 } 
	     }});
}

function sysMenu(){
	var oDate = new Date();var iM1 = oDate.getTime();
	$(".left .sysMenu").addClass("menucssStatus");
	$.ajax({
		 url: '/user/system',
	     type:'GET',
	     dataType:'html',
		 data: {},
		 async: true,
		 timeout:60000,
	     success:function(re){
	    	 $(".right .srcollcss").html(re);
			 tranlateAll();
	    	 loaded();
	    	 var oDate = new Date();var iM2 = oDate.getTime();
	    	 console.log("sys "+(iM2-iM1)+"ms");
	     },
	     error:function(XMLHttpRequest, textStatus, errorThrown) {
	    	 loaded();
	    	 if(textStatus == 'timeout'){
	    		 console.log(XMLHttpRequest.status+": "+t("请求超时"));
				 bootbox.alert(t("请求超时"));
	    	 }
	    	 else{
	    		 console.log(XMLHttpRequest.status+": "+textStatus);
	    	 } 
	     }});
}

function firMenu(){
	var oDate = new Date();var iM1 = oDate.getTime();
	$(".left .firMenu").addClass("menucssStatus");
	$.ajax({
		 url: '/user/fir',
	     type:'GET',
	     dataType:'html',
		 data: {},
		 async: true,
		 timeout:60000,
	     success:function(re){
	    	 $(".right .srcollcss").html(re);
			 tranlateAll();
	    	 loaded();
			 
	    	 var oDate = new Date();var iM2 = oDate.getTime();
	    	 console.log("fir "+(iM2-iM1)+"ms");
	     },
	     error:function(XMLHttpRequest, textStatus, errorThrown) {
	    	 loaded();
	    	 if(textStatus == 'timeout'){
	    		 console.log(XMLHttpRequest.status+": "+t("请求超时"));
				 bootbox.alert(t("请求超时"));
	    	 }
	    	 else{
	    		 console.log(XMLHttpRequest.status+": "+textStatus);
	    	 } 
	     }});
}

function logMenu(){
	var oDate = new Date();var iM1 = oDate.getTime();
	$(".left .logMenu").addClass("menucssStatus");
	$.ajax({
		 url: '/user/log',
	     type:'GET',
	     dataType:'html',
		 data: {},
		 async: true,
		 timeout:60000,
	     success:function(re){
	    	 $(".right .srcollcss").html(re);
			 tranlateAll();
	    	 var oDate = new Date();var iM2 = oDate.getTime();
	    	 console.log("log "+(iM2-iM1)+"ms");
	    	 log_getlist();
	    	 loaded();
	     },
	     error:function(XMLHttpRequest, textStatus, errorThrown) {
	    	 loaded();
	    	 if(textStatus == 'timeout'){
	    		 console.log(XMLHttpRequest.status+": "+t("请求超时"));
				 bootbox.alert(t("请求超时"));
	    	 }
	    	 else{
	    		 console.log(XMLHttpRequest.status+": "+textStatus);
	    	 } 
	     }});
}

function restore(){

	var status=$(".right .content1 .statuscss").html();
	if(status!=t("在线")){
		bootbox.alert(t("矿机没有连接"));
		return false;
	}
	
	bootbox.confirm({
		title : t(""),
		message: t("确认恢复出厂设置")+"?", 
		buttons: {
			confirm: {label: t("确定")},
			cancel:{label:t("取消")}
				},        
		callback: function(result) {
			if(result) {	
				loading(1);
				$.ajax({
			 		 url: '/user/userpanel',
			 	     type:'POST',
			 	     dataType:'json',
			 		 data: {"post":2},
			 		 async: true,
			 		 timeout:60000,
			 	     success:function(re){
			 	    	login(re);
			 	    	 if(re.error!=0)
			 	    		 bootbox.alert(re.message);
			 	    	 else
			 	    		 bootbox.alert(t("操作成功"));
			 	    	loaded(1);
			 	     },
				     error:function(XMLHttpRequest, textStatus, errorThrown) {
				    	 loaded(1);
				    	 if(textStatus == 'timeout'){
				    		 bootbox.alert(XMLHttpRequest.status+": "+t("请求超时"));
				    	 }
				    	 else{
				    		 bootbox.alert(XMLHttpRequest.status+": "+textStatus);
				    	 } 
				     }});
		    }else{
				return;
		    };
		}
	});
	
	

	
}

function reboot(){
	var status=$(".right .content1 .statuscss").html();
	if(status!=t("在线")){
		bootbox.alert(t("矿机没有连接"));
		return false;
	}
	
	
	bootbox.confirm({
		title : t(""),
		message: t("确认重启矿机")+"?", 
		buttons: {
			confirm: {label: t("确定")},
			cancel:{label:t("取消")}
				},        
		callback: function(result) {
			if(result) {	
				loading(1);
				$.ajax({
			 		 url: '/user/userpanel',
			 	     type:'POST',
			 	     dataType:'json',
			 		 data: {"post":3},
			 		 async: true,
			 		 timeout:60000,
			 	     success:function(re){
			 	    	login(re);
			 	    	 if(re.error!=0)
			 	    		 bootbox.alert(re.message);
			 	    	 else
			 	    		 bootbox.alert(t("操作成功"));
			 	    	loaded(1);
			 	     },
				     error:function(XMLHttpRequest, textStatus, errorThrown) {
				    	 loaded(1);
				    	 if(textStatus == 'timeout'){
				    		 bootbox.alert(XMLHttpRequest.status+": "+t("请求超时"));
				    	 }
				    	 else{
				    		 bootbox.alert(XMLHttpRequest.status+": "+textStatus);
				    	 } 
				     }});
		    }else{
				return;
		    };
		}
	});

}


function locate(locate){
	
	var status=$(".right .content1 .statuscss").html();
	if(status!=t("在线")){
		bootbox.alert(t("矿机没有连接"));
		return false;
	}
	loading(1);
	$.ajax({
 		 url: '/user/userpanel',
 	     type:'POST',
 	     dataType:'json',
 		 data: {"post":5,"locate":locate},
 		 async: true,
 		 timeout:60000, // 这个操作比较耗时
 	     success:function(re){
 	    	login(re);
 	    	 if(re.error!=0){
 	    		 bootbox.alert(re.message);
 	    		 locate=0;
 	    	 }
 	    	 
 	   		 if(locate==0){
 				 $(".machine_top .switch-box-slider").removeClass("checked1");
 				 $(".machine_top .switch-box-slider").addClass("checked2");
 			 }
 			 else{
 				 $(".machine_top .switch-box-slider").removeClass("checked2");
 				 $(".machine_top .switch-box-slider").addClass("checked1");
 			 }
 	   		loaded(1);
 	     },
	     error:function(XMLHttpRequest, textStatus, errorThrown) {
	    	 loaded(1);
	    	 if(textStatus == 'timeout'){
	    		 console.log(new Date().toGMTString()+' /user/userpanel:'+XMLHttpRequest.status+': '+t("请求超时"));
				 bootbox.alert(t("请求超时"));
	    	 }
	    	 else{
	    		 console.log(new Date().toGMTString()+' /user/userpanel:'+XMLHttpRequest.status+": "+textStatus);
	    	 } 
	     }});
}

function menu(){
	loading();
	$(".right .srcollcss").html('');
	$(".left .fpgaMenu").removeClass("menucssStatus");
	$(".left .userMenu").removeClass("menucssStatus");
	$(".left .ipMenu").removeClass("menucssStatus");
	$(".left .sysMenu").removeClass("menucssStatus");
	$(".left .firMenu").removeClass("menucssStatus");
	$(".left .logMenu").removeClass("menucssStatus");
}
function setStatus(type){
	if(type==1){
		$(".right .content1 .statuscss").html(t("在线"));
	  	$(".right .content1 .statuscss").removeClass("statusLinecss");
	  	$(".right .content1 .statuscss").removeClass("statusOffcss");
	  	$(".right .content1 .statuscss").addClass("statusOncss");
	}
	else{
  		$(".right .content1 .statuscss").html(t("离线"));
  		$(".right .content1 .statuscss").removeClass("statusLinecss");
  		$(".right .content1 .statuscss").removeClass("statusOncss");
  		$(".right .content1 .statuscss").addClass("statusOffcss");
	}
}
function setCookie(cname,cvalue,exdays)
{
  var d = new Date();
  d.setTime(d.getTime()+(exdays));  //exdays*24*60*60*1000
  var expires = "expires="+d.toGMTString();
  document.cookie = cname + "=" + cvalue + "; " + expires;

}
function getCookie(cname)
{
  var name = cname + "=";
  var ca = document.cookie.split(';');
  for(var i=0; i<ca.length; i++) 
  {
    var c = ca[i].trim();
    if (c.indexOf(name)==0) return c.substring(name.length,c.length);
  }
  return "";
}
function delCookie(name)
{
	var exp = new Date();
	exp.setTime(exp.getTime() - 1);
	var cval=getCookie(name);
	if(cval!=null)
		document.cookie= name + "="+cval+";expires="+exp.toGMTString();

}
function loading(obj){
	//等待中
	if(obj==null){
		//$(".right .bardiv").removeClass("hidden");
	}
	else if(obj==1){
		$(".right .bardiv").addClass("bardivOpacity");
		$(".right .bardiv").removeClass("hidden");
	}
	else
		$(obj).html("<div style='font-size: 22px;font-weight: bold;color: #6e736f;'>"+t("等待中")+"...</div>");
}
function loaded(obj){
	//等待完成
	if(obj==null)
		setTimeout(function () {$(".right .bardiv").addClass("hidden");}, 50);
	else if(obj==1){
		setTimeout(function () {$(".right .bardiv").addClass("hidden");$(".right .bardiv").removeClass("bardivOpacity");}, 50);
	}
	else
		$(obj).empty();
}
function login(code){
	var ctime=getCookie('ctime');
	if(ctime!=1 || code==null){
		delCookie("ctime");
		window.location.href="/user/login";
	}
	else if(code.error==1004){
		delCookie("ctime");
		window.location.href="/user/login";
	}
	else if(code.error>=7001 && code.error<=7003){
		//离线
  		$(".right .content1 .statuscss").html(t("离线"));
  		$(".right .content1 .statuscss").removeClass("statusLinecss");
  		$(".right .content1 .statuscss").addClass("statusOffcss");
  		loaded();
  		bootbox.alert(t("机器已离线"));
  		console.log(code.message);
  		
  		setStatus(0);
 
	}
	else{
		setCookie("ctime",1,60*10*1000);
		setStatus(1);
	}
}
function interval(){
	//定时检查登录或者刷新矿机信息
	setInterval(()=>{
		test();
//		getlist();
	},300000);

}
function test(){
	var ctime=getCookie('ctime');
	if(ctime!=1)
		window.location.href="/user/login";
	$.ajax({
		 url: '/user/userpanel',
	     type:'POST',
	     dataType:'json',
		 data: {"post":7},
		 async: true,
		 timeout:20000,
	     success:function(re){
	    	login(re);
	     },
	     error:function(XMLHttpRequest, textStatus, errorThrown) {
	    	 if(textStatus == 'timeout'){
	    		 console.log(new Date().toGMTString()+' /user/userpanel:'+XMLHttpRequest.status+': '+t("请求超时"));
	    	 }
	    	 else{
	    		 console.log(new Date().toGMTString()+' /user/userpanel:'+XMLHttpRequest.status+": "+textStatus);
	    	 } 
	     }});
} 

function formatDateTime(date) {
  const year = date.getFullYear();
  const month = date.getMonth() + 1;
  const day = date.getDate();
  const hour = date.getHours();
  const minute = date.getMinutes();
  const second = date.getSeconds();
  return `${year}-${pad(month)}-${pad(day)} ${pad(hour)}:${pad(minute)}:${pad(second)}`;
}
 
function pad(num) {
  return num.toString().padStart(2, '0');
}

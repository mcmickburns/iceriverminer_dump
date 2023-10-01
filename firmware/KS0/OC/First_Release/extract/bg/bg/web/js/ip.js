$(document).ready(function(){
	
	$(document).on("click",".ip_main .foot .ip_save",function(){
		ip_save();
	});
	
	//ip_getlist();	
});

function ip_getlist(){
	var oDate = new Date();var iM1 = oDate.getTime();
	$.ajax({
  		 url: '/user/ipconfig',
  	     type:'POST',
  	     dataType:'json',
  		 data: {"post":1},
  		 async: true,
  		 timeout:60000,
  	     success:function(re){
   	    	var oDate = new Date();var iM2 = oDate.getTime();
  	    	console.log("ip-ajax1 "+(iM2-iM1)+"ms");
  	    	login(re);
  	    	ip_content(re.data);
  	    	loaded();
  	    	var oDate = new Date();var iM3 = oDate.getTime();
  	    	console.log("ip-ajax2 "+(iM3-iM2)+"ms");
  	     },
	     error:function(XMLHttpRequest, textStatus, errorThrown) {
	    	 loaded();
	    	 if(textStatus == 'timeout'){
	    		 console.log(new Date().toGMTString()+' /user/ipconfig:'+XMLHttpRequest.status+': '+t("请求超时"));
				 bootbox.alert(t("请求超时"));
	    	 }
	    	 else{
	    		 console.log(new Date().toGMTString()+' /user/ipconfig:'+XMLHttpRequest.status+": "+textStatus);
	    	 } 
	     }});
}


function ip_content(data){
	
	var nic="";
	if(data.hasOwnProperty("nic"))
		nic=data.nic;
	
	var mac="";
	if(data.hasOwnProperty("mac"))
		mac=data.mac;
	
	var ip="";
	if(data.hasOwnProperty("ip"))
		ip=data.ip;
	$(".ip_main input[name=ip]").val(ip);
	
	var netmask="";
	if(data.hasOwnProperty("netmask"))
		netmask=data.netmask;
	$(".ip_main input[name=netmask]").val(netmask);
	
	$(".ip_main .info").append(nic+"<br/>"+t("MAC地址")+": "+mac+"<br/>"+t("IP地址")+": "+ip+"<br/>"+t("子网掩码")+": "+netmask);
	
	var host="";
	if(data.hasOwnProperty("host"))
		host=data.host;
	$(".ip_main input[name=host]").val(host);
	
	var gateway="";
	if(data.hasOwnProperty("gateway"))
		gateway=data.gateway;
	$(".ip_main input[name=gateway]").val(gateway);
	
	var dns="";
	if(data.hasOwnProperty("dns"))
		dns=data.dns;
	$(".ip_main input[name=dns]").val(dns);
	
	var dhcp=true;
	if(data.hasOwnProperty("dhcp"))
		dhcp=data.dhcp;
	if(dhcp==true)
		$(".ip_main select[name=agreement]").val("dhcp");
	else
		$(".ip_main select[name=agreement]").val("static");
	
}


function ip_save(){
	
	var status=$(".right .content1 .statuscss").html();
	if(status!=t("在线")){
		bootbox.alert(t("矿机没有连接"));
		return false;
	}
	
	var data=$("#form1").serialize();
	data=data+"&post=2";
	loading(1);
	$.ajax({
 		 url: '/user/ipconfig',
 	     type:'POST',
 	     dataType:'json',
 		 data: data,
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
	    		 console.log(new Date().toGMTString()+' /user/ipconfig:'+XMLHttpRequest.status+': '+t("请求超时"));
				 bootbox.alert(t("请求超时"));
	    	 }
	    	 else{
	    		 console.log(new Date().toGMTString()+' /user/ipconfig:'+XMLHttpRequest.status+": "+textStatus);
	    	 } 
	     }});
}














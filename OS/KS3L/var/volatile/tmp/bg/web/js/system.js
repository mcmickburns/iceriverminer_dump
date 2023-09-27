$(document).ready(function(){
	
	$(document).on("click",".system_main .foot .system_save",function(){
		system_save();
	});
	
});


function system_save(){
	
	var status=$(".right .content1 .statuscss").html();
	if(status!=t("在线")){
		bootbox.alert(t("矿机没有连接"));
		return false;
	}
	
	var data=$("#form1").serialize();
	data=data+"&post=2";
	loading(1);
	$.ajax({
 		 url: '/user/systemconfig',
 	     type:'POST',
 	     dataType:'json',
 		 data: data,
 		 async: true,
 		 timeout:60000,
 	     success:function(re){
 	    	login(re);
 	    	 if(re.error!=0)
 	    		 bootbox.alert(t(re.message));
 	    	 else{
				 
				bootbox.alert({title:'',message:t("操作成功"),callback:function(){
					$(".system_main input[name=nowpwd]").val("");
					$(".system_main input[name=newpwd]").val("");
					$(".system_main input[name=compwd]").val("");
					delCookie("ctime");
					window.location.href="/user/login";
	    		}});
 
 	    	 }
 	    	loaded(1);
 	     },
	     error:function(XMLHttpRequest, textStatus, errorThrown) {
	    	 loaded(1);
	    	 if(textStatus == 'timeout'){
	    		 console.log(new Date().toGMTString()+' /user/systemconfig:'+XMLHttpRequest.status+': '+t("请求超时"));
				 bootbox.alert(t("请求超时"));
	    	 }
	    	 else{
	    		 console.log(new Date().toGMTString()+' /user/systemconfig:'+XMLHttpRequest.status+": "+textStatus);
	    	 } 
	     }});
}
$(document).ready(function(){		
	$(".login_main .login_div .bottom .loginBtn").click(function(){
		login_in();
	});
	
	$(".login_main .login_div .bottom input[name=user]").keyup(function(e){
		e.preventDefault();
		if(e.keyCode===13){
			$(".login_main .login_div .bottom .loginBtn").click();
		}
	});
	
	$(".login_main .login_div .bottom input[name=pwd]").keyup(function(e){
		e.preventDefault();
		if(e.keyCode===13){
			$(".login_main .login_div .bottom .loginBtn").click();
		}
	});
	
	tranlateAll();
	check();
});

function check(){
	var ctime=getCookie('ctime');
	if(ctime==1)
		window.location.href="/";
}
function loading(){
	//等待中
	$(".bardiv").removeClass("hidden");
}
function loaded(){
	//等待完成
	setTimeout(function () {$(".bardiv").addClass("hidden");}, 500);
}

function login_in(){
	
	var user=$("input[name=user]").val();
	var pwd=$("input[name=pwd]").val();
	
	if(user=="" || pwd==""){
		bootbox.alert(t("登录名或密码不能为空"));
		return false;
	}
	 
	loading();
	$.ajax({
		 url: '/user/loginpost',
	     type:'POST',
	     dataType:'json',
		 data: {"post":6,"user":user,"pwd":pwd},
		 async: true,
		 timeout:20000,
	     success:function(re){
			if(typeof re.error == 'undefined'){
			  
			  bootbox.alert(t("操作失败"));
			}else 
			if(re.error!=0)
	    		 bootbox.alert(re.message);
	    	 else{
	    		 bootbox.alert(t("操作成功"));
	    		 
	    		 setCookie("ctime",1,10*60*1000);
	    		 
	    		 setTimeout(function () {
	    			 window.location.href="/";
	    		 }, 100);
	    	 }
	    	 loaded();
	     },
	     error:function(XMLHttpRequest, textStatus, errorThrown) {
	    	 loaded();
	    	 if(textStatus == 'timeout'){
	    		 bootbox.alert(XMLHttpRequest.status+": "+t("请求超时"));
	    	 }
	    	 else{
	    		 bootbox.alert(XMLHttpRequest.status+": "+textStatus);
	    	 } 
	     }});
}



function setCookie(cname,cvalue,exdays)
{
  var d = new Date();
  d.setTime(d.getTime()+(exdays));  //exdays*24*60*60*1000
  var expires = "expires="+d.toGMTString();
  document.cookie = cname + "=" + cvalue + "; " + expires+"; path=/";

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
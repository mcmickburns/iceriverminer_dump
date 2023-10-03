$(document).ready(function(){	
	
	$(document).on("click",".log_main #tab #tab-header li",function(){
		$(".log_main #tab #tab-content").children().eq($("#tab-header .selected").attr("data-dom")).css('display','none');
		$(".log_main #tab #tab-header .selected").removeClass("selected");
		
		$(this).addClass("selected");
		$(".log_main #tab #tab-content").children().eq($(this).attr("data-dom")).css('display','block');

		if($(this).attr("data-dom")==0){
			log_getlist();
		}
		else if($(this).attr("data-dom")==1){
			getloghistory();
		}
	});
	
	//log_getlist();	
});

function log_getlist(){
	$.ajax({
  		 url: '/user/logconfig',
  	     type:'POST',
  	     dataType:'json',
  		 data: {"post":1},
  		 async: true,
  		 timeout:200000,
  		 beforeSend:function(XMLHttpRequest){ 
   			loading(".log_main #tab .nowlog");
         },
  	     success:function(re){
  	    	login(re);
  	    	if(re.error!=0 || re.data==""){
  	    		$(".log_main #tab .nowlog").html("没有日志");
  	    		return false;
  	    	}
  	    	log_content(re.data);
  	     },
	     error:function(XMLHttpRequest, textStatus, errorThrown) {
	    	 loaded(".log_main #tab .nowlog");
	    	 if(textStatus == 'timeout'){
	    		 console.log(new Date().toGMTString()+' /user/logconfig:'+XMLHttpRequest.status+': '+t("请求超时"));
				 bootbox.alert(t("请求超时"));
	    	 }
	    	 else{
	    		 console.log(new Date().toGMTString()+' /user/logconfig:'+XMLHttpRequest.status+": "+textStatus+": "+errorThrown);
	    	 } 
	     }});
}

function log_content(data){
	
	if(data=="" || data==null || data==undefined)
		return false;
	
	var temp="";
	$.each(data, function(i,j) {
		temp+=j;
	});
	
	$(".log_main #tab .nowlog").html(temp);
	
}

function getloghistory(){
	$.ajax({
  		 url: '/user/logconfig',
  	     type:'POST',
  	     dataType:'json',
  		 data: {"post":2},
  		 async: true,
  		 timeout:200000,
  		 beforeSend:function(XMLHttpRequest){ //函数执行期间显示等待画面
  			loading(".log_main #tab .historylog");
         },
  	     success:function(re){
  	    	login(re);
   	    	if(re.error!=0 || re.data==""){
   	    		$(".log_main #tab .historylog").html("没有日志");
  	    		return false;
  	    	}
  	    	log_content2(re.data);
  	     },
	     error:function(XMLHttpRequest, textStatus, errorThrown) {
	    	 loaded(".log_main #tab .historylog");
	    	 if(textStatus == 'timeout'){
	    		 console.log(new Date().toGMTString()+' /user/logconfig:'+XMLHttpRequest.status+': '+t("请求超时"));
				 bootbox.alert(t("请求超时"));
	    	 }
	    	 else{
	    		 console.log(new Date().toGMTString()+' /user/logconfig:'+XMLHttpRequest.status+": "+textStatus+": "+errorThrown);
	    	 } 
	     }});
}

function log_content2(data){
	
	if(data=="" || data==null || data==undefined)
		return false;
	
	var temp="";
	$.each(data, function(i,j) {
		temp+=j;
	});
	
	$(".log_main #tab .historylog").html(temp);
	
}






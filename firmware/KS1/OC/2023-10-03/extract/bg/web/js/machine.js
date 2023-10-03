$(document).ready(function(){
	
	$(document).on("click",".machine_main .machine_foot .machine_save_pools",function(){
		machine_save_pools();
	});
	
	$(document).on("click",".machine_main .machine_foot .machine_save_fansetting",function(){
		machine_save_fansetting();
	});
	
	//machine_getlist();	
});

function machine_getlist(){
	var oDate = new Date();var iM1 = oDate.getTime();
	$.ajax({
  		 url: '/user/machineconfig',
  	     type:'POST',
  	     dataType:'json',
  		 data: {"post":1},
  		 async: true,
  		 timeout:60000,
  	     success:function(re){
   	    	var oDate = new Date();var iM2 = oDate.getTime();
  	    	console.log("fpga-ajax1 "+(iM2-iM1)+"ms");
  	    	login(re);
  	    	machine_content(re.data);
  	    	loaded();
  	    	var oDate = new Date();var iM3 = oDate.getTime();
  	    	console.log("fpga-ajax2 "+(iM3-iM2)+"ms");
  	     },
	     error:function(XMLHttpRequest, textStatus, errorThrown) {
	    	 loaded();
	    	 if(textStatus == 'timeout'){
	    		 console.log(new Date().toGMTString()+' /user/machineconfig:'+XMLHttpRequest.status+': '+t("请求超时"));
				 bootbox.alert(t("请求超时"));
	    	 }
	    	 else{
	    		 console.log(new Date().toGMTString()+' /user/machineconfig:'+XMLHttpRequest.status+": "+textStatus);
	    	 } 
	     }});
}


function machine_content(data){
	
	if(data.hasOwnProperty("pools")){
		
		$.each(data.pools, function(i,j) {
			
			var num=j.no;
			
			$("input[name=pool"+num+"address]").val(j.addr);
			$("input[name=pool"+num+"miner]").val(j.user);
			$("input[name=pool"+num+"pwd]").val(j.pass);

		});
	}
	
	if(data.hasOwnProperty("mode")){
		if(data.mode == 1){
			$("select[name=fanmode]").val("normal");
		}else{
			$("select[name=fanmode]").val("sleep");
		}
	}
	
	if(data.hasOwnProperty("ratio")){
		$("input[name=fanratio]").val(data.ratio);
	}
	
}

function machine_save_pools(){
	
	var status=$(".right .content1 .statuscss").html();
	if(status!=t("在线")){
		bootbox.alert(t("矿机没有连接"));
		return false;
	}
	loading(1);
	var data=$("#form1").serialize();
	data=data+"&post=2";
	
	$.ajax({
 		 url: '/user/machineconfig',
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
	    	 if(textStatus == 'timeout'){
	    		 console.log(new Date().toGMTString()+' /user/machineconfig:'+XMLHttpRequest.status+': '+t("请求超时"));
				 bootbox.alert(t("请求超时"));
	    	 }
	    	 else{
	    		 console.log(new Date().toGMTString()+' /user/machineconfig:'+XMLHttpRequest.status+": "+textStatus);
	    	 } 
	    	 loaded(1);
	     }});
}




function machine_save_fansetting(){
	
	var status=$(".right .content1 .statuscss").html();
	if(status!=t("在线")){
		bootbox.alert(t("矿机没有连接"));
		return false;
	}
	loading(1);
	var data=$("#form1").serialize();
	data=data+"&post=3";
	
	$.ajax({
 		 url: '/user/machineconfig',
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
	    	 if(textStatus == 'timeout'){
	    		 console.log(new Date().toGMTString()+' /user/machineconfig:'+XMLHttpRequest.status+': '+t("请求超时"));
				 bootbox.alert(t("请求超时"));
	    	 }
	    	 else{
	    		 console.log(new Date().toGMTString()+' /user/machineconfig:'+XMLHttpRequest.status+": "+textStatus);
	    	 } 
	    	 loaded(1);
	     }});
}




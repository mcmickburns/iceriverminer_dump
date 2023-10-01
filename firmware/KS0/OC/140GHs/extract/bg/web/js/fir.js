$(document).ready(function(){
	
	$(document).on("click",".fir_main .foot .fir_save",function(){
		fir_save();
	});
	
	$(document).on("change","#fileinp",function(){
		$("#filetext").val($("#fileinp").val());
	});
	
	
});


function fir_save(){
	
	var status=$(".right .content1 .statuscss").html();
	if(status!=t("在线")){
		bootbox.alert(t("矿机没有连接"));
		return false;
	}
	
	var filetext=$(".fir_main #filetext").val();
	if(filetext==""){
		 bootbox.alert(t("请选择文件"));
		 return false;
	}
	
	var keepconfig=$("input[name=keepconfig]").prop('checked');
	
	var files = $('#fileinp')[0].files[0];
 
	if(typeof files.size == 'number' && files.size > 104857600){
		bootbox.alert(t("文件超过100M， 请重新选择"));
		return false;
	}
	
	if(typeof files.type != 'string' || (files.type != 'application/x-tar' && files.type != 'application/x-gzip') 
		&& (files.type  == "" && files.name.indexOf(".bgz") === -1)){
		bootbox.alert(t("上传文件格式错误"));
		return false;
	}
	
	
	var fd = new FormData();
	fd.append('file',files);
	
	loading(1);
	$.ajax({
 		 url: '/user/firconfig?post=2&keepconfig='+keepconfig,
 	     type:'POST',
 	     dataType:'json',
 	     processData:false,
 	     contentType:false,
 		 data: fd,
 		 async: true,
 		 timeout:200000,
		success:function(re){
			 loaded(1);
 	    	 login(re);
 	    	 if(re.error!=0){
 	    		 bootbox.alert(t(re.message));
 	    	 }else{
				var file = document.querySelector('input[type=file]');
				file.value = '';
				$(".fir_main #filetext").val("");

				bootbox.alert({title:t(""), message:t("操作成功"), callback: function(r) {
					reboot();	
				}});
 	    	 }
 	    	
 	     },
	     error:function(XMLHttpRequest, textStatus, errorThrown) {
	    	 loaded(1);
	    	 if(textStatus == 'timeout'){
	    		 console.log(new Date().toGMTString()+' /fpga/userpanel:'+XMLHttpRequest.status+': '+t("请求超时"));
				 bootbox.alert(t("请求超时"));
	    	 }
	    	 else{
				 bootbox.alert(t("文件上传失败"));
	    		 // console.log(new Date().toGMTString()+' /fpga/userpanel:'+XMLHttpRequest.status+": "+textStatus);
	    	 } 
	     }});
}
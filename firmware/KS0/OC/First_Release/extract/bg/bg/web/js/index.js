$(document).ready(function(){
	$(document).on("click",".right .content5 .boardcss .broadstatuscss",function(){
		var obj=$(this).attr("data-id");
		if($("."+obj).hasClass("hidden")){
			$("."+obj).removeClass("hidden");
		}
		else{
			$("."+obj).addClass("hidden");
		}
	});
	
	tranlateAll();
	//getlist2();	
});

function getlist2(){
	loading(1);
	var oDate = new Date();var iM1 = oDate.getTime();
	$.ajax({
  		 url: '/user/userpanel',
  	     type:'POST',
  	     dataType:'json',
  		 data: {"post":4},
  		 async: true,
  		 timeout:200000,
  	     success:function(re){
  	    	var oDate = new Date();var iM2 = oDate.getTime();
  	    	console.log("user-ajax1 "+(iM2-iM1)+"ms");
		    login(re);
  	    	content1switchbox(re.data);
  	    	if(re.error!=0 || re.data==""){
  	    		setStatus(0);
				bootbox.alert(t("机器已离线"));
				console.log(re.message);
  	    	}
  	    	 else{
  	    		 //界面数据显示
   	    		content1(re.data);
  	    		content7(re.data);
  	    		 
  	    		content2(re.data);
  	    		content3(re.data);
  	    		content4(re.data);
  	    		content5(re.data);
  	    		content6(re.data);
  	    		 
  	    	 }
  	    	loaded();
  	    	var oDate = new Date();var iM3 = oDate.getTime();
  	    	console.log("user-ajax2 "+(iM3-iM2)+"ms");
  	     },
	     error:function(XMLHttpRequest, textStatus, errorThrown) {
	    	 loaded();
	    	 if(textStatus == 'timeout'){
	    		 console.log(new Date().toGMTString()+' /user/userpanel:'+XMLHttpRequest.status+': '+t("请求超时"));
	    	 }
	    	 else{
	    		 // bootbox.alert(XMLHttpRequest.status+": "+textStatus);
	    		 console.log(new Date().toGMTString()+' /user/userpanel:'+XMLHttpRequest.status+": "+textStatus);
	    	 } 
	     }});
}

function content2(data){
	//状态
	var speed=0;
	if(data.hasOwnProperty("powstate"))
		speed=data.powstate;
	if(speed==true){
  		$(".right .content2 .panlcss .speedcss").removeClass("content2radiusRedcss");
  		$(".right .content2 .panlcss .speedcss").addClass("content2radiusGreencss");
  		$(".right .content2 .panlcss .speedcss").html(t("正常"));
	}
	else{
  		$(".right .content2 .panlcss .speedcss").removeClass("content2radiusGreencss");
  		$(".right .content2 .panlcss .speedcss").addClass("content2radiusRedcss");
  		$(".right .content2 .panlcss .speedcss").html(t("异常"));
	}
	
	var netstatus=0;
	if(data.hasOwnProperty("netstate"))
		netstatus=data.netstate;
	if(netstatus==true){
  		$(".right .content2 .panlcss .netstatuscss").removeClass("content2radiusRedcss");
  		$(".right .content2 .panlcss .netstatuscss").addClass("content2radiusGreencss");
  		$(".right .content2 .panlcss .netstatuscss").html(t("正常"));
	}
	else{
  		$(".right .content2 .panlcss .netstatuscss").removeClass("content2radiusGreencss");
  		$(".right .content2 .panlcss .netstatuscss").addClass("content2radiusRedcss");
  		$(".right .content2 .panlcss .netstatuscss").html(t("异常"));
	}
	
	var vol=0;
	if(data.hasOwnProperty("fanstate"))
		vol=data.fanstate;
	if(vol==true){
  		$(".right .content2 .panlcss .volcss").removeClass("content2radiusRedcss");
  		$(".right .content2 .panlcss .volcss").addClass("content2radiusGreencss");
  		$(".right .content2 .panlcss .volcss").html(t("正常"));
	}
	else{
  		$(".right .content2 .panlcss .volcss").removeClass("content2radiusGreencss");
  		$(".right .content2 .panlcss .volcss").addClass("content2radiusRedcss");
  		$(".right .content2 .panlcss .volcss").html(t("异常"));
	}
	
	var tem=0;
	if(data.hasOwnProperty("tempstate"))
		tem=data.tempstate;
	if(tem==true){
  		$(".right .content2 .panlcss .temcss").removeClass("content2radiusRedcss");
  		$(".right .content2 .panlcss .temcss").addClass("content2radiusGreencss");
  		$(".right .content2 .panlcss .temcss").html(t("正常"));
	}
	else{
  		$(".right .content2 .panlcss .temcss").removeClass("content2radiusGreencss");
  		$(".right .content2 .panlcss .temcss").addClass("content2radiusRedcss");
  		$(".right .content2 .panlcss .temcss").html(t("异常"));
	}
	
	
	//算力状态
	var speed=0;
 
	// 兼容
	if(typeof data.rtpow_hash == "undefined" ){ 
		var gr = gethash(data.rtpow, 1, 2);
		data.rtpow = gethash2(data.rtpow, "h", 0);
		data["rtpow_hash"] = gr["speed"];
		data["rtpow_unit"] = gr["unit"];
	}
	
	if(typeof data.avgpow_hash == "undefined" ){ 
		var ga = gethash(data.avgpow, 1, 2);
		data.avgpow = gethash2(data.avgpow, "h", 0);
		data["avgpow_hash"] = ga["speed"];
		data["avgpow_unit"] = ga["unit"];
	}
	 
	if(data.hasOwnProperty("rtpow_hash"))
		speed=data.rtpow_hash;
	$(".right .content2 .panlcss .nowspeedcss").html(speed);
	var speedunit="";
	if(data.hasOwnProperty("rtpow_unit"))
		speedunit=data.rtpow_unit;
	$(".right .content2 .panlcss .nowspeedunitcss").html(speedunit);
	
	
	var speedsvg=0;
	if(data.hasOwnProperty("avgpow_hash"))
		speedsvg=data.avgpow_hash;
	$(".right .content2 .panlcss .svgspeedcss").html(speedsvg);
	var speedsvgunit="";
	if(data.hasOwnProperty("avgpow_unit"))
		speedsvgunit=data.avgpow_unit;
	$(".right .content2 .panlcss .svgspeedunitcss").html(speedsvgunit);
	
	var reject="0.00";
	if(data.hasOwnProperty("reject"))
		reject=data.reject;
	$(".right .content2 .panlcss .rejectcss").html(reject);
	
	var runtime="-";
	if(data.hasOwnProperty("runtime")){
		runtime="";
		var arr = data.runtime.split(":");
		runtime=runtime+arr[0]+"&nbsp;<span class='lan-trans runtime2css'>"+t("天")+"</span>&nbsp;";
		runtime=runtime+arr[1]+"&nbsp;<span class='lan-trans runtime2css'>"+t("时")+"</span>&nbsp;";
		runtime=runtime+arr[2]+"&nbsp;<span class='lan-trans runtime2css'>"+t("分")+"</span>&nbsp;";
		runtime=runtime+arr[3]+"&nbsp;<span class='lan-trans runtime2css'>"+t("秒")+"</span>&nbsp;";
	}
	$(".right .content2 .panlcss .runtimecss").html(runtime);
	
}

function content3(data){
 

	if(data.hasOwnProperty("pows") && data.hasOwnProperty("pows_x")){
		
		var tmpPows = [];
		tmpPows["board1"] = [];
		var tmpPows_x = [];
		$.each(data.pows.board1, function(i,j) {
			if(j < 0){
				return false;
			}
			
			tmpPows["board1"][i] = j;
			tmpPows_x[i] = data.pows_x[i];
		});
		
		
		var pows_unit_temp = "";
		if(data.pows_unit!=undefined && data.pows_unit!=null){
			pows_unit_temp = data.pows_unit;
		}else if(data.unit != undefined && data.unit){// 兼容
			if(data.unit == "H"){
				pows_unit_temp = "H/s";	
			}else{
				pows_unit_temp = data.unit+"H/s";		
			}
		}
		 
		// highcharts(data.pows_x,data.pows,t("算力曲线图"),"historyofboard",pows_unit_temp);
		highcharts(tmpPows_x,tmpPows,t("算力曲线图"),"historyofboard",pows_unit_temp);
		
	}
	
}

function content4(data){
	//矿池状态
	if(data.hasOwnProperty("pools")){
		
		$.each(data.pools, function(i,j) {
			var temp="";
			temp+="<td>"+j.no+"</td>";
			temp+="<td>"+j.addr+"</td>";
			temp+="<td style='word-break: break-all;'>"+j.user+"</td>";
			if(j.connect==true)
				temp+="<td><div class='poolstatuscss statusOncss'>"+t("连接中")+"</div></td>";
			else
				temp+="<td><div class='poolstatuscss statusOffcss'>"+t("未连接")+"</div></td>";
			
			temp+="<td>"+j.diff+"</td>";
			temp+="<td>"+j.priority+"</td>";
			temp+="<td>"+j.accepted+"</td>";
			temp+="<td>"+j.rejected+"</td>";
			temp="<tr>"+temp+"</tr>";
			$(".right .content4 .poolcss tbody").append(temp);
		});
		
		
		
	}
}

function content5(data){
	//算力板状态
	if(data.hasOwnProperty("boards")){
		
		if(data.boards.length > 1){
			$.each(data.boards, function(i,j) {
				if(j.no == -1){
					return ;
				}
				
				var temp="";
				temp+="<td>"+j.no+"</td>";
				temp+="<td>"+j.avgpow+"</td>";
				temp+="<td>"+j.intmp+" ℃</td>";
				temp+="<td>"+j.outtmp+" ℃</td>";
				temp="<tr>"+temp+"</tr>";
			
				$(".right .content5 .boardcss tbody").append(temp);
				
			});
			
		}else{
			var temp="";
			temp+="<td>"+data.boards[0].no+"</td>";
			
			
			if(typeof data.avgpow_hash == "undefined" ){ 
				var ga = gethash(data.avgpow, 1, 2);
				data.avgpow = gethash2(data.avgpow, "h", 0);
				data["avgpow_hash"] = ga["speed"];
				data["avgpow_unit"] = ga["unit"];
			}
			
			temp+="<td>"+data["avgpow_hash"]+" "+data["avgpow_unit"]+"</td>";
	 
			temp+="<td>"+data.boards[0].intmp+" ℃</td>";
			temp+="<td>"+data.boards[0].outtmp+" ℃</td>";


			temp="<tr>"+temp+"</tr>";
			
			
			$(".right .content5 .boardcss tbody").append(temp);
			
		}
		
		
		
	}
	
}

function content6(data){
	//风扇状态
	var temp="<td>Speed(r/min)</td>";
	var num=0;
	if(data.hasOwnProperty("fans")){
		$.each(data.fans, function(i,j) {
			if(num>=2){
				return;
			}
			
			num++;
			temp+="<td>"+j+"</td>";
 		});

	}
	// else{
		// temp+="<td>-</td><td>-</td><td>-</td><td>-</td>";
	// }
	// for(i=num;i<2;num++){
		// temp+="<td>-</td>";
	// }
	temp="<tr>"+temp+"</tr>";
	$(".right .content6 .fancss tbody").append(temp);

}


function highcharts(x,y,ti,z,u){
	var zz="#"+z;
	$(zz).css("display","inline-block");
	setTimeout(function () {
			var chart = null;		
			Highcharts.setOptions({
				global: {
					useUTC: false
				}
			});

			chart = Highcharts.chart(z, {
				chart: {
					zoomType: 'x',        //缩放
					panning: true,        //开始平移
					panKey: 'ctrl',        //平移键
					type: 'spline',       //类型
		            borderWidth: 0,
		            plotBorderWidth: 0,
				},
				title: {
					text: ti
				},
				subtitle: {
					text: t("左键图像缩放,按住ctrl和左键可以滑动图像")
				},
				credits: {
					enabled: false          //右下角广告
				},
				xAxis: {
					categories: x,
					crosshair: {     //十字
						width: 1,
						color: '#9d9d9d'
					},
					/*tickInterval: 2,*/
				},
				yAxis: {
					title: {
						text: u
					},
					min: 0,
					minorGridLineWidth: 0,
					gridLineWidth: '2px',
					alternateGridColor: null,
					crosshair: {           //十字
						width: 1,
						color: '#9d9d9d',
						dashStyle: 'Dash'
					},
    				labels: {
    					formatter: function () {
    						return this.value + u ;
    					}
    				},
				},
				tooltip: {        //提示框
					formatter: function () {
						var s = '<span style="font-size:12px;">chain0: '+this.point.y+' '+u+'</span>';
						return s;
					},
// 					valueSuffix: ' '
				},
				plotOptions: {     //线条
					spline: {
						lineWidth: 2,
						states: {
							hover: {
								lineWidth: 3
							}
						},
						marker: {     //点点
							enabled: false
						},
					}
				},
				series: [
							// {          
								// name: 'chain0',
								// data: y.board0,
								// showInLegend: true,     //图像下面的图例
							// }
							// ,
							{          
								name: t("算力曲线图"),
								data: y.board1,
								showInLegend: true,     //图像下面的图例
							}
							// ,
							// {          
								// name: 'chain2',
								// data: y.board2,
								// showInLegend: true,     //图像下面的图例
							// }
						],
			});
	}, 1);
};


function gethash(hashrate, isShowUint=0, round=3, spaceholder=""){

	var hashrate_temp=0;
	var hashrate_zhuan=0;

	var unitindex = 0;
	var unit2="H";

	//转h/s
	hashrateF = parseFloat(hashrate);
	if(hashrate.toLowerCase().indexOf('e') !== -1){
		hashrate_temp = hashrateF * Math.pow(10, 18);
		unitindex = 6;
	}
	else if(hashrate.toLowerCase().indexOf('p') !== -1){
		hashrate_temp = hashrateF * Math.pow(10, 15);
		unitindex = 5;
	}
	else if(hashrate.toLowerCase().indexOf('t') !== -1){
		hashrate_temp = hashrateF * Math.pow(10, 12); 
		unitindex = 4;
	}
	else if(hashrate.toLowerCase().indexOf('g') !== -1){
		hashrate_temp = hashrateF * Math.pow(10, 9); 
		unitindex = 3;
	}
	else if(hashrate.toLowerCase().indexOf('m') !== -1){
		hashrate_temp = hashrateF * Math.pow(10, 6); 
		unitindex = 2;
	}
	else if(hashrate.toLowerCase().indexOf('k') !== -1){
		hashrate_temp = hashrateF * Math.pow(10, 3); 
		unitindex = 1;
	}else{
		hashrate_temp = hashrateF;
	}
 
	if(unitindex==1)
		unit2="K";
	else if(unitindex==2)
		unit2="M";
	else if(unitindex==3)
		unit2="G";
	else if(unitindex==4)
		unit2="T";
	else if(unitindex==5)
		unit2="P";
	else if(unitindex==6)
		unit2="E";

	if(isShowUint==1){
		if(unit2 == "H")
			unit2+="/s";
		else
			unit2+="H/s";
	}
 
	var powNum = Math.pow(10,round);
	result = [];
	result["speed"] = Math.round(hashrate_temp / Math.pow(10,unitindex*3) * powNum) / powNum;
	result["unit"] = spaceholder + unit2;
	return result;

}

function gethash2(hashrate, outUnit, isShowUint=1){
	var hashrate_temp=0;
	var hashrate_zhuan=0;
	
	//转h/s
	hashrateF = parseFloat(hashrate);
	if(hashrate.toLowerCase().indexOf('e') !== -1){
		hashrate_temp = hashrateF * Math.pow(10, 18);
	}
	else if(hashrate.toLowerCase().indexOf('p') !== -1){
		hashrate_temp = hashrateF * Math.pow(10, 15);
	}
	else if(hashrate.toLowerCase().indexOf('t') !== -1){
		hashrate_temp = hashrateF * Math.pow(10, 12); 
	}
	else if(hashrate.toLowerCase().indexOf('g') !== -1){
		hashrate_temp = hashrateF * Math.pow(10, 9); 
	}
	else if(hashrate.toLowerCase().indexOf('m') !== -1){
		hashrate_temp = hashrateF * Math.pow(10, 6); 
	}
	else if(hashrate.toLowerCase().indexOf('k') !== -1){
		hashrate_temp = hashrateF * Math.pow(10, 3); 
	}else{
		hashrate_temp = hashrateF;
	}
			
	//根据type返回
	if(outUnit.toLowerCase().indexOf('e') !== -1){
		hashrate_zhuan = Math.round(hashrate_temp/Math.pow(10,18) * 10000)/10000;
		if(isShowUint == 1)
			hashrate_zhuan = hashrate_zhuan + " Eh/s";
	}
	else if(outUnit.toLowerCase().indexOf('p') !== -1){
		hashrate_zhuan = Math.round(hashrate_temp/Math.pow(10,15) * 10000)/10000;
		if(isShowUint == 1)
			hashrate_zhuan = hashrate_zhuan + " Ph/s";
	}
	else if(outUnit.toLowerCase().indexOf('t') !== -1){
		hashrate_zhuan = Math.round(hashrate_temp/Math.pow(10,12) * 10000)/10000;
		if(isShowUint == 1)
			hashrate_zhuan = hashrate_zhuan + " Th/s";
	}
	else if(outUnit.toLowerCase().indexOf('g') !== -1){
		hashrate_zhuan = Math.round(hashrate_temp/Math.pow(10,9) * 10000)/10000;
		if(isShowUint == 1)
			hashrate_zhuan = hashrate_zhuan + " Gh/s";	
	}
	else if(outUnit.toLowerCase().indexOf('m') !== -1){
		hashrate_zhuan = Math.round(hashrate_temp/Math.pow(10,6) * 10000)/10000;
		if(isShowUint == 1)
			hashrate_zhuan = hashrate_zhuan + " Mh/s";
	}
	else if(outUnit.toLowerCase().indexOf('k') !== -1){
		hashrate_zhuan = Math.round(hashrate_temp/Math.pow(10,3) * 10000)/10000;
		if(isShowUint == 1)
			hashrate_zhuan = hashrate_zhuan + " Kh/s";
	}
	else{
		hashrate_zhuan = Math.round(hashrate_temp * 10000)/10000;
		if(isShowUint == 1)
			hashrate_zhuan = hashrate_zhuan + " h/s";
	}

	return hashrate_zhuan;

}













<p>前言：完结撒花~本篇内容在原有的项目基础上添加了获取北京时间的功能，并对OLED显示屏的显示内容进行完善修改。<br> 想实现的功能大部分已经完成了，虽然这个实验比较简单，不能独立支撑起一个项目，不过未来会将其作为一个小功能嵌入到其他的应用开发中。加油加油！！！<br> </p>
<div class="toc">
 <h3><a name="t0" one-link-mark="yes"></a>文章目录</h3>
 <ul><li><a href="#1_3" target="_self" one-link-mark="yes">1、摘要</a></li><li><a href="#2_7" target="_self" one-link-mark="yes">2、硬件准备</a></li><li><ul><li><a href="#21_9" target="_self" one-link-mark="yes">2.1、商品链接</a></li></ul>
  </li><li><a href="#3_15" target="_self" one-link-mark="yes">3、软件准备</a></li><li><a href="#4_19" target="_self" one-link-mark="yes">4、硬件连线</a></li><li><a href="#5_42" target="_self" one-link-mark="yes">5、代码解析</a></li><li><ul><li><a href="#51_43" target="_self" one-link-mark="yes">5.1、获取实时时间程序</a></li><li><a href="#53_170" target="_self" one-link-mark="yes">5.3、项目代码逻辑</a></li></ul>
  </li><li><a href="#6_177" target="_self" one-link-mark="yes">6、运行结果</a></li><li><a href="#7_181" target="_self" one-link-mark="yes">7、源程序</a></li><li><ul><li><a href="#71_182" target="_self" one-link-mark="yes">7.1、百度网盘</a></li><li><a href="#72Github_185" target="_self" one-link-mark="yes">7.2、Github地址</a></li></ul>
 </li></ul>
</div>
<p></p> 
<h1><a name="t1" one-link-mark="yes"></a><a id="1_3" one-link-mark="yes"></a>1、摘要</h1> 
<p>本章节要实现的功能为：<br> 将<a href="https://so.csdn.net/so/search?q=ESP8266&amp;spm=1001.2101.3001.7020" target="_blank" class="hl hl-1" data-report-view="{&quot;spm&quot;:&quot;1001.2101.3001.7020&quot;,&quot;dest&quot;:&quot;https://so.csdn.net/so/search?q=ESP8266&amp;spm=1001.2101.3001.7020&quot;}" data-report-click="{&quot;spm&quot;:&quot;1001.2101.3001.7020&quot;,&quot;dest&quot;:&quot;https://so.csdn.net/so/search?q=ESP8266&amp;spm=1001.2101.3001.7020&quot;}" one-link-mark="yes">ESP8266</a>获取到的天气、时间数据进行处理然后通过OLED显示。<br> 与获取天气的方法类似，获取时间也是通过访问API得到时间数据，得到数据后，通过定时器计时，实现时钟功能。</p> 
<h1><a name="t2" one-link-mark="yes"></a><a id="2_7" one-link-mark="yes"></a>2、硬件准备</h1> 
<p>硬件设备由单片机最小系统板，OLED屏幕以及ESP8266wifi模块组成。</p> 
<h2><a name="t3" one-link-mark="yes"></a><a id="21_9" one-link-mark="yes"></a>2.1、商品链接</h2> 
<p>最小系统板：<a href="https://s.click.taobao.com/9Reevmu" one-link-mark="yes">购买链接</a><br> USB转TTL(种类有点多，随便选一个就行，我用的是CH340这个芯片的)：<a href="https://s.click.taobao.com/IH4t2nu" one-link-mark="yes">购买链接</a><br> ESP8266：<a href="https://s.click.taobao.com/78Qs2nu" one-link-mark="yes">购买链接</a><br> OLED（我用的是0.96寸4针，I2C接口）：<a href="https://s.click.taobao.com/Jn4t2nu" one-link-mark="yes">购买链接</a><br> ST-Link V2下载线：<a href="https://s.click.taobao.com/JNY3vmu" one-link-mark="yes">购买链接</a></p> 
<h1><a name="t4" one-link-mark="yes"></a><a id="3_15" one-link-mark="yes"></a>3、软件准备</h1> 
<p>Keil编译器<br> VSCode编译器<br> XCOM串口调试助手</p> 
<h1><a name="t5" one-link-mark="yes"></a><a id="4_19" one-link-mark="yes"></a>4、硬件连线</h1> 
<div class="table-box"><table><thead><tr><th>MCU</th><th>ESP8266</th></tr></thead><tbody><tr><td>3.3V</td><td>VCC</td></tr><tr><td>GND</td><td>GND</td></tr><tr><td>PB10</td><td>RXD</td></tr><tr><td>PB11</td><td>TXD</td></tr><tr><td>3.3V</td><td>IO</td></tr><tr><td>3.3V</td><td>RST</td></tr></tbody></table></div> 
<div class="table-box"><table><thead><tr><th>MCU</th><th>USB转TTL</th></tr></thead><tbody><tr><td>5V</td><td>VCC</td></tr><tr><td>GND</td><td>GND</td></tr><tr><td>PA9</td><td>RXD</td></tr><tr><td>PA10</td><td>TXD</td></tr></tbody></table></div> 
<div class="table-box"><table><thead><tr><th>MCU</th><th>OLED</th></tr></thead><tbody><tr><td>5V</td><td>VCC</td></tr><tr><td>GND</td><td>GND</td></tr><tr><td>PB15</td><td>SDA</td></tr><tr><td>PB13</td><td>SCL</td></tr></tbody></table></div>
<h1><a name="t6" one-link-mark="yes"></a><a id="5_42" one-link-mark="yes"></a>5、代码解析</h1> 
<h2><a name="t7" one-link-mark="yes"></a><a id="51_43" one-link-mark="yes">

### 获取实时时间程序
![](https://gitee.com/lemonhubchat/blog-image/raw/master/img/AT2.png)
```c
/*********************************************************************************
* Function Name    ： get_beijing_time,获取时间
* Parameter		   ： 
* Return Value     ： 返回：0---获取成功，1---获取失败
* Function Explain ： 
* Create Date      ： 2021/6/5 by zzh
**********************************************************************************/
u8 get_beijing_time(void)
{
	u8 *p;
	u8 res;
	
	u8 *resp;
	u8 *p_end;
	u8 ipbuf[16]; 	//IP缓存
	p=mymalloc(SRAMIN,40);							//申请40字节内存
	resp=mymalloc(SRAMIN,10);
	p_end=mymalloc(SRAMIN,40);
	
	sprintf((char*)p,"AT+CIPSTART=\"TCP\",\"%s\",%s",TIME_SERVERIP,TIME_PORTNUM);    //配置目标TCP服务器
	printf("%s",p);
	res = esp8266_send_cmd(p,"OK",200);//连接到目标TCP服务器
	if(res==1)
	{
		myfree(SRAMIN,p);
		return 1;
	}
	delay_ms(300);
	esp8266_send_cmd("AT+CIPMODE=1","OK",100);      //传输模式为：透传	
//	atk_8266_get_wanip(ipbuf);//获取WAN IP
	
//	sprintf((char*)p,"IP地址:%s 端口:%s",ipbuf,(u8*)TIME_PORTNUM);
//	
//	//Show_Str(30,65,200,12,p,12,0);				//显示IP地址和端口	
//	 printf("设备 %s\r\n",p);
//	
//	USART3_RX_STA=0;
	esp8266_send_cmd("AT+CIPSEND","OK",100);         //开始透传
	printf("start trans...\r\n");

	u3_printf("GET /time15.asp HTTP/1.1Host:www.beijing-time.org\n\n");

	delay_ms(20);//延时20ms返回的是指令发送成功的状态
	USART3_RX_STA=0;	//清零串口3数据
	delay_ms(1000);
	if(USART3_RX_STA&0X8000)		//此时再次接到一次数据，为天气的数据
	{ 
		USART3_RX_BUF[USART3_RX_STA&0X7FFF]=0;//添加结束符
	} 
	
	printf("USART3_RX_BUF=%s\r\n",USART3_RX_BUF);	
	//USART3_RX_BUF 为时间信息
	if(USART3_RX_STA & 0x8000)
	{
			resp="Date";
			USART3_RX_BUF[USART3_RX_STA & 0x7ff] = 0;
			printf("get_tim_srt：%s\r\n",USART3_RX_BUF);
			if(strstr((char*)USART3_RX_BUF,(char*)resp)) 
			{       
				resp="GMT";
				p_end = (u8*)strstr((char*)USART3_RX_BUF,(char*)resp);
				p = p_end - 9; 
				printf("get_net_str %s\r\n",p);
				nwt.hour = ((*p - 0x30)*10 + (*(p+1) - 0x30) + 8) % 24;  //GMT0-->GMT8

				nwt.min = ((*(p+3) - 0x30)*10 + (*(p+4) - 0x30)) % 60;

				nwt.sec = ((*(p+6) - 0x30)*10 + (*(p+7) - 0x30)) % 60;

				nwt.year = ((*(p-5) - 0x30)*1000 + (*(p-4) - 0x30)*100+ (*(p-3) - 0x30)*10+ (*(p-2) - 0x30)); 

				nwt.date = ((*(p-12) - 0x30)*10 + (*(p-11) - 0x30)); 

				if        ((u8*)strstr((char*)USART3_RX_BUF,(char*) "Jan")) nwt.month=1; 
				else if   ((u8*)strstr((char*)USART3_RX_BUF,(char*) "Feb")) nwt.month=2; 
				else if   ((u8*)strstr((char*)USART3_RX_BUF,(char*) "Mar")) nwt.month=3; 
				else if   ((u8*)strstr((char*)USART3_RX_BUF,(char*) "Apr")) nwt.month=4; 
				else if   ((u8*)strstr((char*)USART3_RX_BUF,(char*) "May")) nwt.month=5; 
				else if   ((u8*)strstr((char*)USART3_RX_BUF,(char*) "Jun")) nwt.month=6; 
				else if   ((u8*)strstr((char*)USART3_RX_BUF,(char*) "Jul")) nwt.month=7; 
				else if   ((u8*)strstr((char*)USART3_RX_BUF,(char*) "Aug")) nwt.month=8; 
				else if   ((u8*)strstr((char*)USART3_RX_BUF,(char*) "Sep")) nwt.month=9; 
				else if   ((u8*)strstr((char*)USART3_RX_BUF,(char*) "Oct")) nwt.month=10; 
				else if   ((u8*)strstr((char*)USART3_RX_BUF,(char*) "Nov")) nwt.month=11; 
				else if   ((u8*)strstr((char*)USART3_RX_BUF,(char*) "Dec")) nwt.month=12;


				printf("nwt.year = %d\r\n",nwt.year);
				printf("nwt.month = %d\r\n",nwt.month);
				printf("nwt.date = %d\r\n",nwt.date);  //获取data 28日

				printf("nwt.hour = %d\r\n",nwt.hour);
				printf("nwt.min = %d\r\n",nwt.min);
				printf("nwt.sec = %d\r\n",nwt.sec);



				USART3_RX_STA = 0;


				printf("uddate:nettime!!!");
//				RTC_Set(nwt.year,nwt.month ,nwt.date ,nwt.hour ,nwt.min,nwt.sec);
		}
		USART3_RX_STA = 0;																
		myfree(SRAMIN,resp);
		myfree(SRAMIN,p_end);
																
						
    }               
	printf("\r\n\r\n");
	esp8266_quit_trans();//退出透传
	esp8266_send_cmd("AT+CIPCLOSE","OK",50);         //关闭连接
	myfree(SRAMIN,p);
	return 0;
}

```

5.3、项目代码逻辑</h2> 
<p>基本的代码已经介绍完了，其他的操作就是调用这些函数实现功能而已，这边就不全部列出来了，感觉没什么意义。我把我的代码的逻辑分享一下吧，具体代码我会附在文末，大家可以详细看看。<br> <strong>初始化函数-&gt;OLED显示状态-&gt;通过ESP8266获取数据-&gt;OLED状态更新<br> 按键按下触发中断-&gt;通过ESP8266获取数据-&gt;OLED状态更新<br> 定时器触发-&gt;sec秒数自增</strong></p> 
<h1><a name="t9" one-link-mark="yes"></a><a id="6_177" one-link-mark="yes"></a>6、运行结果</h1> 
<p>设备上电后，等待ESP8266初始化，获取数据后进行解析，将状态显示到OLED屏幕上。当按下按键后，会重新获取，更新天气数据。<br> <img src="https://img-blog.csdnimg.cn/20210605154524234.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2V0aGFuXzMz,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"></p> 
<h1><a name="t10" one-link-mark="yes"></a><a id="7_181" one-link-mark="yes"></a>7、源程序</h1> 
<h2><a name="t11" one-link-mark="yes"></a><a id="71_182" one-link-mark="yes"></a>7.1、百度网盘</h2> 
<p>链接：<a href="https://pan.baidu.com/s/1m16EzF6AS_jB2YBGIOxtNQ" one-link-mark="yes"><span class="one-pan-tip one-pan-tip-lock" one-id="m16EzF6AS_jB2YBGIOxtNQ" one-source="baidu" one-tip-mark="yes">https://pan.baidu.com/s/1m16EzF6AS_jB2YBGIOxtNQ</span> </a><br> 提取码：w7i2</p> 


<article class="baidu_pl">
        <div id="article_content" class="article_content clearfix">
        <link rel="stylesheet" href="https://csdnimg.cn/release/blogv2/dist/mdeditor/css/editerView/ck_htmledit_views-d7093e7f7c.css">
                <div id="content_views" class="markdown_views prism-atom-one-dark">
                    <svg xmlns="http://www.w3.org/2000/svg" style="display: none;">
                        <path stroke-linecap="round" d="M5,0 0,2.5 5,5z" id="raphael-marker-block" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></path>
                    </svg>
                    <p>前言：上一章节我们通过串口调试助手，成功获取到天气数据，这一节我们将通过MCU的串口发送、接收功能，实现MCU获取天气数据。</p> 
<p>传送门：<a href="https://blog.csdn.net/ethan_33/article/details/117330349#comments_16710057" one-link-mark="yes">基于STM32F103的网络天气时钟(1)---------通过串口获取天气</a><br> </p>
<div class="toc">
 <h3><a name="t0" one-link-mark="yes"></a>文章目录</h3>
 <ul><li><a href="#1_4" target="_self" one-link-mark="yes">1、摘要</a></li><li><a href="#2_6" target="_self" one-link-mark="yes">2、硬件准备</a></li><li><ul><li><a href="#21_WIFI_8" target="_self" one-link-mark="yes">2.1 、WIFI模块</a></li><li><a href="#22USBTTL_10" target="_self" one-link-mark="yes">2.2、USB转TTL模块</a></li><li><a href="#23STM32_12" target="_self" one-link-mark="yes">2.3、STM32最小系统板</a></li><li><a href="#24_16" target="_self" one-link-mark="yes">2.4、商品链接</a></li></ul>
  </li><li><a href="#3_23" target="_self" one-link-mark="yes">3、软件准备</a></li><li><a href="#4_30" target="_self" one-link-mark="yes">4、硬件连线</a></li><li><a href="#5_48" target="_self" one-link-mark="yes">5、代码解析</a></li><li><ul><li><a href="#51ESP8266_51" target="_self" one-link-mark="yes">5.1、ESP8266初始化程序</a></li><li><a href="#52_95" target="_self" one-link-mark="yes">5.2、获取实时天气程序</a></li></ul>
  </li><li><a href="#6_152" target="_self" one-link-mark="yes">6、运行结果</a></li><li><a href="#7_156" target="_self" one-link-mark="yes">7、源程序</a></li><li><ul><li><a href="#71__157" target="_self" one-link-mark="yes">7.1 百度网盘链接</a></li></ul>
 </li></ul>
</div>
<p></p> 
<h1><a name="t1" one-link-mark="yes"></a><a id="1_4" one-link-mark="yes"></a>1、摘要</h1> 
<p>单片机具有串口发送和接收功能，我们可以通过串口发送AT指令从而获取到知心天气的数据。并在另一个串口输出。</p> 
<h1><a name="t2" one-link-mark="yes"></a><a id="2_6" one-link-mark="yes"></a>2、硬件准备</h1> 
<p>除了上一章使用的wifi模块还有USB转TTL模板外，我们还需要准备一块stm32单片机的最小系统板。</p> 
<h2><a name="t3" one-link-mark="yes"></a><a id="21_WIFI_8" one-link-mark="yes"></a>2.1 、WIFI模块</h2> 
<p>同上章节。</p> 
<h2><a name="t4" one-link-mark="yes"></a><a id="22USBTTL_10" one-link-mark="yes"></a>2.2、USB转TTL模块</h2> 
<p>同上章节。</p> 
<h2><a name="t5" one-link-mark="yes"></a><a id="23STM32_12" one-link-mark="yes"></a>2.3、STM32最小系统板</h2> 
<p>因为项目比较简单，所以使用哪一款单片机随意~<br> 我使用的是在淘宝上买的stm32f103rct6的最小系统板。<br> <img src="https://img-blog.csdnimg.cn/20210530145546481.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2V0aGFuXzMz,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"></p> 
<h2><a name="t6" one-link-mark="yes"></a><a id="24_16" one-link-mark="yes"></a>2.4、商品链接</h2> 
<p>最小系统板：<a href="https://s.click.taobao.com/9Reevmu" one-link-mark="yes">购买链接</a><br> USB转TTL(种类有点多，随便选一个就行，我用的是CH340这个芯片的)：<a href="https://s.click.taobao.com/IH4t2nu" one-link-mark="yes">购买链接</a><br> <a href="https://so.csdn.net/so/search?q=ESP8266&amp;spm=1001.2101.3001.7020" target="_blank" class="hl hl-1" data-report-view="{&quot;spm&quot;:&quot;1001.2101.3001.7020&quot;,&quot;dest&quot;:&quot;https://so.csdn.net/so/search?q=ESP8266&amp;spm=1001.2101.3001.7020&quot;}" data-report-click="{&quot;spm&quot;:&quot;1001.2101.3001.7020&quot;,&quot;dest&quot;:&quot;https://so.csdn.net/so/search?q=ESP8266&amp;spm=1001.2101.3001.7020&quot;}" one-link-mark="yes">ESP8266</a>：<a href="https://s.click.taobao.com/78Qs2nu" one-link-mark="yes">购买链接</a><br> OLED（我用的是0.96寸4针，I2C接口）：<a href="https://s.click.taobao.com/Jn4t2nu" one-link-mark="yes">购买链接</a><br> ST-Link V2下载线：<a href="https://s.click.taobao.com/JNY3vmu" one-link-mark="yes">购买链接</a></p> 
<h1><a name="t7" one-link-mark="yes"></a><a id="3_23" one-link-mark="yes"></a>3、软件准备</h1> 
<p>上一节收到的数据有部分是乱码，经查阅是因为编码方式不一致导致的，不过“QCOM”没有更改编码方式的功能，于是我就换成“XCOM”。使用方法和之前的大体一致。<br> <a href="https://pan.baidu.com/s/127VbtgGw4VLNj5DcYO1u1Q" one-link-mark="yes"><span class="one-pan-tip one-pan-tip-error" one-id="27VbtgGw4VLNj5DcYO1u1Q" one-source="baidu" one-tip-mark="yes">下载链接</span></a><br> 提取码：3mzd</p> 
<p>更改编码方式：<br> <img src="https://img-blog.csdnimg.cn/20210530150449625.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2V0aGFuXzMz,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"></p> 
<h1><a name="t8" one-link-mark="yes"></a><a id="4_30" one-link-mark="yes"></a>4、硬件连线</h1> 
<div class="table-box"><table><thead><tr><th>MCU</th><th>ESP8266</th></tr></thead><tbody><tr><td>3.3V</td><td>VCC</td></tr><tr><td>GND</td><td>GND</td></tr><tr><td>PB10</td><td>RXD</td></tr><tr><td>PB11</td><td>TXD</td></tr><tr><td>3.3V</td><td>IO</td></tr><tr><td>3.3V</td><td>RST</td></tr></tbody></table></div> 
<div class="table-box"><table><thead><tr><th>MCU</th><th>USB转TTL</th></tr></thead><tbody><tr><td>5V</td><td>VCC</td></tr><tr><td>GND</td><td>GND</td></tr><tr><td>PA9</td><td>RXD</td></tr><tr><td>PA10</td><td>TXD</td></tr></tbody></table></div>
<h1><a name="t9" one-link-mark="yes"></a><a id="5_48" one-link-mark="yes"></a>5、代码解析</h1> 
<p>基础功能的代码这里就不详细介绍了，主要讲解关键代码。<br> 源代码在文末下载，大部分代码已经加上注释。</p> 
<h2><a name="t10" one-link-mark="yes"></a><a id="51ESP8266_51" one-link-mark="yes">

#### ESP8266初始化程序
![](https://gitee.com/lemonhubchat/blog-image/raw/master/img/AT1.png)
```c
void esp8266_start_trans(void)
{
	u8 *p;
	p=mymalloc(SRAMIN,50);							//申请32字节内存，用于存wifista_ssid，wifista_password
	printf("send:AT\r\n");	
	while(esp8266_send_cmd("AT","OK",20))//检查WIFI模块是否在线
	{
	} 
	//设置工作模式 1：station模式   2：AP模式  3：兼容 AP+station模式
	printf("send:AT+CWMODE=1\r\n");	
	esp8266_send_cmd("AT+CWMODE=1","OK",50);
	//Wifi模块重启
	printf("send:AT+RST\r\n");	
	esp8266_send_cmd("AT+RST","OK",20);
	delay_ms(1000);         //延时3S等待重启成功
	delay_ms(1000);
	delay_ms(1000);	
	
	//设置连接到的WIFI网络名称/加密方式/密码,这几个参数需要根据您自己的路由器设置进行修改!! 
	printf("send:AT+CIPMUX=0\r\n");	
	esp8266_send_cmd("AT+CIPMUX=0","OK",20);   //0：单连接，1：多连接		

	sprintf((char*)p,"AT+CWJAP=\"%s\",\"%s\"",wifista_ssid,wifista_password);//设置无线参数:ssid,密码
	printf("send:AT+CWJAP=\"%s\",\"%s\"\r\n",wifista_ssid,wifista_password);
	
	while(esp8266_send_cmd(p,"WIFI GOT IP",300));					//连接目标路由器,并且获得IP
	myfree(SRAMIN,p);
}


```
![](https://gitee.com/lemonhubchat/blog-image/raw/master/img/AT2.png)

#### 获取一次实时天气

```c
//获取一次实时天气
//返回：0---获取成功，1---获取失败
u8 get_current_weather(void)
{
	u8 res;
	p=mymalloc(SRAMIN,40);							//申请40字节内存
	
	
	sprintf((char*)p,"AT+CIPSTART=\"TCP\",\"%s\",%s",WEATHER_SERVERIP,WEATHER_PORTNUM);    //配置目标TCP服务器
	printf("send:AT+CIPSTART=\"TCP\",\"%s\",%s\r\n",WEATHER_SERVERIP,WEATHER_PORTNUM);
	res = esp8266_send_cmd(p,"OK",200);//连接到目标TCP服务器
	if(res==1)
	{
		myfree(SRAMIN,p);
		
		return 1;
	}
	delay_ms(300);
	
	printf("send:AT+CIPMODE=1\r\n");	
	esp8266_send_cmd("AT+CIPMODE=1","OK",100);      //传输模式为：透传	

	USART3_RX_STA=0;
	printf("send:AT+CIPSEND\r\n");	
	esp8266_send_cmd("AT+CIPSEND","OK",100);         //开始透传
	printf("start trans...\r\n");
	
	u3_printf("GET https://api.seniverse.com/v3/weather/now.json?key=私钥&location=城市&language=zh-Hans&unit=c\n\n");	
	delay_ms(20);//延时20ms返回的是指令发送成功的状态
	USART3_RX_STA=0;	//清零串口3数据
	delay_ms(1000);
	if(USART3_RX_STA&0X8000)		//此时再次接到一次数据，为天气的数据
	{ 
		USART3_RX_BUF[USART3_RX_STA&0X7FFF]=0;//添加结束符
	} 
	printf("USART3_RX_BUF=%s\r\n",USART3_RX_BUF);
	
	atk_8266_quit_trans();//退出透传
	
	printf("send:AT+CIPCLOSE\r\n");	
	esp8266_send_cmd("AT+CIPCLOSE","OK",50);         //关闭连接
	myfree(SRAMIN,p);
	return 0;
}

```


</a>6、运行结果</h1> 
<p>将代码烧入后，可在串口调试器中查看到接收到的状态信息以及天气数据。<br> 当按下按键(PA0),可再次获取天气数据。<br> <img src="https://img-blog.csdnimg.cn/20210530160010680.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2V0aGFuXzMz,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"></p> 
<h1><a name="t13" one-link-mark="yes"></a><a id="7_156" one-link-mark="yes">
</a>7、源程序</h1> 
<h2><a name="t14" one-link-mark="yes"></a><a id="71__157" one-link-mark="yes"></a>7.1 百度网盘链接</h2> 
<p>链接：<br> <a href="https://pan.baidu.com/s/1sd00hF-RVmsDbEoMfnqdBQ" one-link-mark="yes"><span class="one-pan-tip one-pan-tip-success" one-id="sd00hF-RVmsDbEoMfnqdBQ" one-source="baidu" one-tip-mark="yes">https://pan.baidu.com/s/1sd00hF-RVmsDbEoMfnqdBQ</span> </a><br> 提取码：sgek</p> 
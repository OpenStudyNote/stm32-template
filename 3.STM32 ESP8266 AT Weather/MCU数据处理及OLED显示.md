<p>前言：本章我们要实现的功能为：将获取到的天气数据进行OLED显示。<br> 参考资料：<br> OLED显示屏：<br> <a href="https://blog.csdn.net/m0_49648532/article/details/107958716?ops_request_misc=&amp;request_id=&amp;biz_id=102&amp;utm_term=oled0.96&amp;utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-9-.nonecase&amp;spm=1018.2226.3001.4187" one-link-mark="yes">关于基于stm32的0.96寸oled显示屏的学习理解心得。</a><br> cJSON数据转换：<br> <a href="https://blog.csdn.net/rsd102/article/details/109266442" one-link-mark="yes">用cJSON解析心知天气返回的数据包</a><br> <a href="https://www.cnblogs.com/piaoyang/p/9274925.html" one-link-mark="yes">C语言cJSON库的使用，解析json数据格式</a></p> 
<p></p>
<div class="toc">
 <h3><a name="t0" one-link-mark="yes"></a>文章目录</h3>
 <ul><li><a href="#1_10" target="_self" one-link-mark="yes">1、摘要</a></li><li><a href="#2_15" target="_self" one-link-mark="yes">2、硬件准备</a></li><li><ul><li><a href="#21_18" target="_self" one-link-mark="yes">2.1、商品链接</a></li></ul>
  </li><li><a href="#3_24" target="_self" one-link-mark="yes">3、软件准备</a></li><li><a href="#4_31" target="_self" one-link-mark="yes">4、硬件连线</a></li><li><a href="#5_54" target="_self" one-link-mark="yes">5、代码解析</a></li><li><ul><li><a href="#51OLED_55" target="_self" one-link-mark="yes">5.1、OLED代码分析</a></li><li><a href="#52cJSON_138" target="_self" one-link-mark="yes">5.2、cJSON解析数据包代码</a></li><li><a href="#53_275" target="_self" one-link-mark="yes">5.3、项目代码逻辑</a></li></ul>
  </li><li><a href="#6_279" target="_self" one-link-mark="yes">6、运行结果</a></li><li><a href="#7_282" target="_self" one-link-mark="yes">7、源程序</a></li><li><ul><li><a href="#71_283" target="_self" one-link-mark="yes">7.1、百度网盘</a></li><li><a href="#72Github_286" target="_self" one-link-mark="yes">7.2、Github地址</a></li></ul>
 </li></ul>
</div>
<p></p> 
<h1><a name="t1" one-link-mark="yes"></a><a id="1_10" one-link-mark="yes"></a>1、摘要</h1> 
<p>本章节主要有两个部分组成：</p> 
<p>*一个是OLED屏幕的显示，关于OLED的资料有挺多的，CSDN中也有许多大佬做了比较详细的介绍，所以本章节并不会很深入地去讲解代码，只是会稍微提一下，<strong>如果大家有需要我写一个比较详细地介绍的话，也可以在评论区提出，我有时间就会写一下的。</strong><br> 另一个是用cJSON去解读心知天气返回的数据包。</p> 
<h1><a name="t2" one-link-mark="yes"></a><a id="2_15" one-link-mark="yes"></a>2、硬件准备</h1> 
<p>硬件和上章节差不多，只是多了一个OLED屏幕，这里我使用的是0.96寸I2C驱动的OLED屏幕。<br> <img src="https://img-blog.csdnimg.cn/20210601204139846.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2V0aGFuXzMz,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"></p> 
<h2><a name="t3" one-link-mark="yes"></a><a id="21_18" one-link-mark="yes"></a>2.1、商品链接</h2> 
<p>最小系统板：<a href="https://s.click.taobao.com/9Reevmu" one-link-mark="yes">购买链接</a><br> USB转TTL(种类有点多，随便选一个就行，我用的是CH340这个芯片的)：<a href="https://s.click.taobao.com/IH4t2nu" one-link-mark="yes">购买链接</a><br> <a href="https://so.csdn.net/so/search?q=ESP8266&amp;spm=1001.2101.3001.7020" target="_blank" class="hl hl-1" data-report-view="{&quot;spm&quot;:&quot;1001.2101.3001.7020&quot;,&quot;dest&quot;:&quot;https://so.csdn.net/so/search?q=ESP8266&amp;spm=1001.2101.3001.7020&quot;}" data-report-click="{&quot;spm&quot;:&quot;1001.2101.3001.7020&quot;,&quot;dest&quot;:&quot;https://so.csdn.net/so/search?q=ESP8266&amp;spm=1001.2101.3001.7020&quot;}" one-link-mark="yes">ESP8266</a>：<a href="https://s.click.taobao.com/78Qs2nu" one-link-mark="yes">购买链接</a><br> OLED（我用的是0.96寸4针，I2C接口）：<a href="https://s.click.taobao.com/Jn4t2nu" one-link-mark="yes">购买链接</a><br> ST-Link V2下载线：<a href="https://s.click.taobao.com/JNY3vmu" one-link-mark="yes">购买链接</a></p> 
<h1><a name="t4" one-link-mark="yes"></a><a id="3_24" one-link-mark="yes"></a>3、软件准备</h1> 
<p>Keil编译器<br> VSCode编译器<br> XCOM串口调试助手<br> 这边附上另一篇文章，大家可以参考学习一下<br> <a href="https://blog.csdn.net/ethan_33/article/details/117441149" one-link-mark="yes">STM32----使用VSCode编写Keil<br> </a></p> 
<h1><a name="t5" one-link-mark="yes"></a><a id="4_31" one-link-mark="yes"></a>4、硬件连线</h1> 
<div class="table-box"><table><thead><tr><th>MCU</th><th>ESP8266</th></tr></thead><tbody><tr><td>3.3V</td><td>VCC</td></tr><tr><td>GND</td><td>GND</td></tr><tr><td>PB10</td><td>RXD</td></tr><tr><td>PB11</td><td>TXD</td></tr><tr><td>3.3V</td><td>IO</td></tr><tr><td>3.3V</td><td>RST</td></tr></tbody></table></div> 
<div class="table-box"><table><thead><tr><th>MCU</th><th>USB转TTL</th></tr></thead><tbody><tr><td>5V</td><td>VCC</td></tr><tr><td>GND</td><td>GND</td></tr><tr><td>PA9</td><td>RXD</td></tr><tr><td>PA10</td><td>TXD</td></tr></tbody></table></div> 
<div class="table-box"><table><thead><tr><th>MCU</th><th>OLED</th></tr></thead><tbody><tr><td>5V</td><td>VCC</td></tr><tr><td>GND</td><td>GND</td></tr><tr><td>PB15</td><td>SDA</td></tr><tr><td>PB13</td><td>SCL</td></tr></tbody></table></div>
<h1><a name="t6" one-link-mark="yes"></a><a id="5_54" one-link-mark="yes"></a>5、代码解析</h1> 
<h2><a name="t7" one-link-mark="yes"></a><a id="51OLED_55" one-link-mark="yes"></a>5.1、OLED代码分析</h2> 
<p>参考其他博主写的技术论文<br> OLED显示屏：<a href="https://blog.csdn.net/m0_49648532/article/details/107958716?ops_request_misc=&amp;request_id=&amp;biz_id=102&amp;utm_term=oled0.96&amp;utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-9-.nonecase&amp;spm=1018.2226.3001.4187" one-link-mark="yes">关于基于stm32的0.96寸oled显示屏的学习理解心得。</a></p> 
<p>本实验使用的OLED是基于I2C通信的。所以最主要的内容有：<br> 发送从机地址（0x78），再发送命令字节，接着发送数据字节。

### OLED显示代码
```c
/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
   IIC_Start();
   Write_IIC_Byte(0x78);            //Slave address,SA0=0
	IIC_Wait_Ack();	
   Write_IIC_Byte(0x00);			//write command
	IIC_Wait_Ack();	
   Write_IIC_Byte(IIC_Command); 
	IIC_Wait_Ack();	
   IIC_Stop();
}
/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
   IIC_Start();
   Write_IIC_Byte(0x78);			//D/C#=0; R/W#=0
	IIC_Wait_Ack();	
   Write_IIC_Byte(0x40);			//write data
	IIC_Wait_Ack();	
   Write_IIC_Byte(IIC_Data);
	IIC_Wait_Ack();	
   IIC_Stop();
}

/**********************************
显示一个字符串
输入数据： 
x----x轴
y----y轴
*chr----字符串
Char_Size----大小（16/12）
**********************************/
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		
		OLED_ShowChar(x,y,chr[j],Char_Size);
		x+=8;
		if(x>120){x=0;y+=2;}
		j++;
	}
}

/**********************************
显示一个文字
输入数据： 
x----x轴
y----y轴
no----字库数组文字对应的位置
**********************************/
void OLED_ShowCHinese(u8 x,u8 y,u8 no)
{      			    
	u8 t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
				adder+=1;
      }					
}
```
### cJSON解析数据包代码
因为C语言没有字典这样的结构，所以我们解析json格式的数据就需要调用cJSON这个函数库。
主要函数接口：


```c
/* The cJSON structure: */
typedef struct cJSON {
	struct cJSON *next,*prev;	/* next/prev allow you to walk array/object chains. Alternatively, use GetArraySize/GetArrayItem/GetObjectItem */
	struct cJSON *child;		/* An array or object item will have a child pointer pointing to a chain of the items in the array/object. */
	int type;					/* The type of the item, as above. */
	char *valuestring;			/* The item's string, if type==cJSON_String */
	int valueint;				/* The item's number, if type==cJSON_Number */
	double valuedouble;			/* The item's number, if type==cJSON_Number */
	char *string;				/* The item's name string, if this item is the child of, or is in the list of subitems of an object. */
} cJSON;

```
说明：

cJSON是使用链表来存储数据的，其访问方式很像一颗树。每一个节点可以有兄弟节点，通过next/prev指针来查找，它类似双向链表；每个节点也可以有孩子节点，通过child指针来访问，进入下一层。只有节点是对象或数组时才可以有孩子节点。
type是键（key）的类型，一共有7种取值，分别是：False，Ture，NULL，Number，String，Array，Object。
若是Number类型，则valueint或valuedouble中存储着值。 若期望的是int，则访问valueint。
若期望的是double，则访问valuedouble，可以得到值。
若是String类型的，则valuestring中存储着值，可以访问valuestring得到值。
string中存放的是这个节点的名字，可理解为key的名称。
重要的接口函数：

cJSON *cJSON_Parse(const char *value)；
功能：解析JSON数据包，并按照cJSON结构体的结构序列化整个数据包。可以看做是获取一个句柄。
cJSON *cJSON_GetObjectItem(cJSON *object,const char *string)；
功能：获取json指定的对象成员 ；
参数：*objec：第一个函数中获取的句柄。string：需要获取的对象 ；
返回值：这个对象成员的句柄；
如果json格式的对象成员直接就是字符串那么就可以直接通过结构体中的valuestring元素来获取这个成员的值。
cJSON *cJSON_GetArrayItem(cJSON *array,int item);
功能：有可能第二个函数中获取到的是成员对象值是一个数组，那么就需要用到这个函数。用来获取这个数组指定的下标对象；
参数：*array：传入第二步中返回的值， item：想要获取这个数组的下标元素 ；
返回值：这个数组中指定下标的对象。然后在对这个返回值重复使用第二步函数就可以获取到各个成员的值了。也就是说对象是数组的比是字符串的要多用一个cJSON_GetArrayItem函数，其他的没区别。
cJSON_Delete() 用来释放你第一步获取的句柄，来释放整个内存。用在解析完后调用。
### 解析数据包
```c
/*********************************************************************************
* Function Name    ： cJSON_WeatherParse,解析天气数据
* Parameter		   ： JSON：天气数据包  results：保存解析后得到的有用的数据
* Return Value     ： 0：成功 其他:错误
* Function Explain ： 
* Create Date      ： 2017.12.6 by lzn
**********************************************************************************/
int cJSON_WeatherParse(char *JSON, Results *results)
{
	cJSON *json,*arrayItem,*object,*subobject,*item;
	
	json = cJSON_Parse(JSON); //解析JSON数据包
	if(json == NULL)		  //检测JSON数据包是否存在语法上的错误，返回NULL表示数据包无效
	{
		printf("Error before: [%s] \r\n",cJSON_GetErrorPtr()); //打印数据包语法错误的位置
		return 1;
	}
	else
	{
		if((arrayItem = cJSON_GetObjectItem(json,"results")) != NULL); //匹配字符串"results",获取数组内容
		{
			int size = cJSON_GetArraySize(arrayItem);     //获取数组中对象个数
			printf("cJSON_GetArraySize: size=%d \r\n",size); 
			
			if((object = cJSON_GetArrayItem(arrayItem,0)) != NULL)//获取父对象内容
			{
				/* 匹配子对象1 */
				if((subobject = cJSON_GetObjectItem(object,"location")) != NULL)
				{
					printf("---------------------------------subobject1-------------------------------\r\n");
					if((item = cJSON_GetObjectItem(subobject,"id")) != NULL)   //匹配子对象1成员"id"
					{
						printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",item->type,item->string,item->valuestring);
						memcpy(results[0].location.id,item->valuestring,strlen(item->valuestring));
					}
					if((item = cJSON_GetObjectItem(subobject,"name")) != NULL) //匹配子对象1成员"name"
					{
						printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",item->type,item->string,item->valuestring);
						memcpy(results[0].location.name,item->valuestring,strlen(item->valuestring));
					}
					if((item = cJSON_GetObjectItem(subobject,"country")) != NULL)//匹配子对象1成员"country"
					{
						printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",item->type,item->string,item->valuestring);
						memcpy(results[0].location.country,item->valuestring,strlen(item->valuestring));
					}
					if((item = cJSON_GetObjectItem(subobject,"path")) != NULL)  //匹配子对象1成员"path"
					{
						printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",item->type,item->string,item->valuestring);
						memcpy(results[0].location.path,item->valuestring,strlen(item->valuestring));
					}
					if((item = cJSON_GetObjectItem(subobject,"timezone")) != NULL)//匹配子对象1成员"timezone"
					{
						printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",item->type,item->string,item->valuestring);
						memcpy(results[0].location.timezone,item->valuestring,strlen(item->valuestring));
					}
					if((item = cJSON_GetObjectItem(subobject,"timezone_offset")) != NULL)//匹配子对象1成员"timezone_offset"
					{
						printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",item->type,item->string,item->valuestring);
						memcpy(results[0].location.timezone_offset,item->valuestring,strlen(item->valuestring));
					}
				}
				/* 匹配子对象2 */
				if((subobject = cJSON_GetObjectItem(object,"now")) != NULL)
				{
					printf("---------------------------------subobject2-------------------------------\r\n");
					if((item = cJSON_GetObjectItem(subobject,"text")) != NULL)//匹配子对象2成员"text"
					{
						printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",item->type,item->string,item->valuestring);
						memcpy(results[0].now.text,item->valuestring,strlen(item->valuestring));
					}
					if((item = cJSON_GetObjectItem(subobject,"code")) != NULL)//匹配子对象2成员"code"
					{
						printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",item->type,item->string,item->valuestring);
						memcpy(results[0].now.code,item->valuestring,strlen(item->valuestring));
					}
					if((item = cJSON_GetObjectItem(subobject,"temperature")) != NULL) //匹配子对象2成员"temperature"
					{
						printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",item->type,item->string,item->valuestring);
						memcpy(results[0].now.temperature,item->valuestring,strlen(item->valuestring));
					}
				}
				/* 匹配子对象3 */
				if((subobject = cJSON_GetObjectItem(object,"last_update")) != NULL)
				{
					printf("---------------------------------subobject3-------------------------------\r\n");
					printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",subobject->type,subobject->string,subobject->valuestring);
					memcpy(results[0].last_update,item->valuestring,strlen(subobject->valuestring));
				}
			} 
		}
	}
	
	cJSON_Delete(json); //释放cJSON_Parse()分配出来的内存空间
	
	return 0;
}

```




</a>5.3、项目代码逻辑</h2> 
<p>基本的代码已经介绍完了，其他的操作就是调用这些函数实现功能而已，这边就不全部列出来了，感觉没什么意义。<br> 我把我的代码的逻辑分享一下吧，具体代码我会附在文末，大家可以详细看看。<br> 初始化函数-&gt;OLED显示状态-&gt;按下按键触发中断-&gt;获取天气数据-&gt;OLED状态更新。</p> 
<h1><a name="t10" one-link-mark="yes"></a><a id="6_279" one-link-mark="yes"></a>6、运行结果</h1> 
<p>设备上电后，等待ESP8266初始化，获取天气数据后通过cJSON解析，将状态显示到OLED屏幕上。当按下按键后，会重新获取，更新天气数据。<br> <img src="https://img-blog.csdnimg.cn/20210601221029521.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2V0aGFuXzMz,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"></p> 
<h1><a name="t11" one-link-mark="yes"></a><a id="7_282" one-link-mark="yes"></a>7、源程序</h1> 
<h2><a name="t12" one-link-mark="yes"></a><a id="71_283" one-link-mark="yes"></a>7.1、百度网盘</h2> 
<p>链接：<a href="https://pan.baidu.com/s/1fDIIgYYc9yALo2gTNgoJRw" one-link-mark="yes"><span class="one-pan-tip one-pan-tip-lock" one-id="fDIIgYYc9yALo2gTNgoJRw" one-source="baidu" one-tip-mark="yes">https://pan.baidu.com/s/1fDIIgYYc9yALo2gTNgoJRw</span></a><br> 提取码：gd2d</p> 
<h2><a name="t13" one-link-mark="yes"></a><a id="72Github_286" one-link-mark="yes">
                
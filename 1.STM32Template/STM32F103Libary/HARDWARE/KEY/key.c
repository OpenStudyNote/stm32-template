//--------------------------------------------------------------------------------------------------
//  ������ͷ�ļ�    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
#include "key.h"
#include "delay.h"

//==================================================================================================
//  ʵ�ֹ���: KEY_Init ����gpio�˿����ó�ʼ������
//  ����˵��: KEY0 PE4 KEY1 PE3 KEY_WK_UP PA0
//  ������ע: KEY0_PRES 1  KEY1_PRES 1  WKUP_PRES 3 
//----------------------------------------- ---------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================  
//������ʼ������
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3|GPIO_Pin_4;//KEY0-KEY1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��PE3,4
	//��ʼ�� WK_UP-->GPIOA.0	  ��������
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0���ó����룬Ĭ������	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.0

}


//==================================================================================================
//  ʵ�ֹ���: KEY_Scan ���������� ���ذ���ֵ
//  ����˵��: KEY0 PE4 KEY1 PE3 KEY_WK_UP PA0
//  ������ע: KEY0_PRES 1  KEY1_PRES 1  WKUP_PRES 3 
//  mode:0,��֧��������;1,֧��������;
//  0��û���κΰ�������
//  1��KEY0����
//  2��KEY1����
//  3��KEY3���� WK_UP
//  ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY3!!
//----------------------------------------- ---------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================  
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)
    key_up=1;  //֧������		  
	if(key_up&&(KEY0==0||KEY1==0||WK_UP==1))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY0==0)
      return KEY0_PRES;
		else if(KEY1==0)
      return KEY1_PRES;
		else if(WK_UP==1)
      return WKUP_PRES;
	}
  else if(KEY0==1&&KEY1==1&&WK_UP==0)
    key_up=1; 	    
 	return 0;// �ް�������
}

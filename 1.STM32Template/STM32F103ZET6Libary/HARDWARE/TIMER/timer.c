//--------------------------------------------------------------------------------------------------
//  ������ͷ�ļ�    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
#include "timer.h"

//==================================================================================================
//  ʵ�ֹ���: ��ʱ��1 ��ʼ������
//  ����˵��: �߼���ʱ�� TIM1 TIM8
//  ������ע: ��ʱ������Ƚϣ����벶׽������������������źţ�ÿ����ʱ����8���ⲿIO��
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================  
void TIM1_Int_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    TIM_TimeBaseStructure.TIM_Period = arr;
    TIM_TimeBaseStructure.TIM_Prescaler = psc;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE );

    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    TIM_Cmd(TIM1, ENABLE);
}

void TIM2_Int_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��

    TIM_TimeBaseStructure.TIM_Period = arr;      //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ     ������5000Ϊ500ms
    TIM_TimeBaseStructure.TIM_Prescaler =psc;    //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

    TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx
}


//=================================================================================================
//  ʵ�ֹ���: ��ʱ��3 ��ʼ������
//  ����˵��: 
//  ������ע: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================  
void TIM3_Int_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��


    //��ʱ��TIM3��ʼ��
    TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE ); 
  
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;            //TIM3�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;         //�����ȼ�3��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure);      //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

    TIM_Cmd(TIM3, ENABLE);  

}


//=================================================================================================
//  ʵ�ֹ���: TIM3_PWM_Init ��ʱ��3 PWM
//  ����˵��: 
//  TIM3 PWM���ֳ�ʼ�� 
//  arr���Զ���װֵ
//  psc��ʱ��Ԥ��Ƶ��
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================  
void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3������ӳ��  TIM3_CH2->PB5    
 
//==================================================================================================
//  ʵ�ֹ���: ���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOB.5  
//  ����˵��:  LED0 ʵ�ֲ�ͬ���ȵĺ�����  
//==================================================================================================
  //
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
 
   //��ʼ��TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//��ʼ��TIM3 Channel2 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC2

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
 
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3
	

}
//==================================================================================================
//  ʵ�ֹ���: ��ʱ��4 ��ʼ������
//  ����˵��: 
//  ������ע: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================  

void TIM4_Int_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʱ��ʹ��


    //��ʱ��TIM4��ʼ��
    TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE ); //ʹ��ָ����TIM4�ж�,��������ж�

    //�ж����ȼ�NVIC����
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //�����ȼ�3��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

    TIM_Cmd(TIM4, ENABLE); //ʹ�ܶ�ʱ��4
}
//==================================================================================================
//  ʵ�ֹ���: ��ʱ��5 ��ʼ������
//  ����˵��: 
//  ������ע: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================  
void TIM5_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //ʱ��ʹ��

    TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ     ������5000Ϊ500ms
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM3�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

    TIM_Cmd(TIM5, ENABLE);  //ʹ��TIMx
}
//==================================================================================================
//  ��������: TIME6,7 ������ʱ��
//  �������: ������������
//  ����˵��: 
//--------------------------------------------------------------------------------------------------
//  �������: ��
//  �������: ��
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
// �ж����ȼ�����
static void BASIC_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // �����ж���Ϊ0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = BASIC_TIM_IRQ ;	
		// ���������ȼ�Ϊ 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // ������ռ���ȼ�Ϊ3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*
 * ע�⣺TIM_TimeBaseInitTypeDef�ṹ��������5����Ա��TIM6��TIM7�ļĴ�������ֻ��
 * TIM_Prescaler��TIM_Period������ʹ��TIM6��TIM7��ʱ��ֻ���ʼ����������Ա���ɣ�
 * ����������Ա��ͨ�ö�ʱ���͸߼���ʱ������.
 *-----------------------------------------------------------------------------
 *typedef struct
 *{ TIM_Prescaler            ����
 *	TIM_CounterMode			     TIMx,x[6,7]û�У���������
 *  TIM_Period               ����
 *  TIM_ClockDivision        TIMx,x[6,7]û�У���������
 *  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]����
 *}TIM_TimeBaseInitTypeDef; 
 *-----------------------------------------------------------------------------
 */


static void BASIC_TIM_Mode_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		
		// ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
    BASIC_TIM_APBxClock_FUN(BASIC_TIM_CLK, ENABLE);
	
		// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
    TIM_TimeBaseStructure.TIM_Period = BASIC_TIM_Period;	

	  // ʱ��Ԥ��Ƶ��Ϊ
    TIM_TimeBaseStructure.TIM_Prescaler= BASIC_TIM_Prescaler;
	
		// ʱ�ӷ�Ƶ���� ��������ʱ��û�У����ù�
    //TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
		
		// ����������ģʽ��������ʱ��ֻ�����ϼ�����û�м���ģʽ������
    //TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
		
		// �ظ���������ֵ��������ʱ��û�У����ù�
		//TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	
	  // ��ʼ����ʱ��
    TIM_TimeBaseInit(BASIC_TIM, &TIM_TimeBaseStructure);
		
		// ����������жϱ�־λ
    TIM_ClearFlag(BASIC_TIM, TIM_FLAG_Update);
	  
		// �����������ж�
    TIM_ITConfig(BASIC_TIM,TIM_IT_Update,ENABLE);
		
		// ʹ�ܼ�����
    TIM_Cmd(BASIC_TIM, ENABLE);	
}

void BASIC_TIM_Init(void)
{
	BASIC_TIM_NVIC_Config();
	BASIC_TIM_Mode_Config();
}

//==================================================================================================
//  ʵ�ֹ���: ��ʱ��1 �жϷ���������
//  ����˵��: 
//  ������ע: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================  

void TIM1_UP_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
    {

    }
    TIM_ClearFlag(TIM1, TIM_IT_Update );
}

//==================================================================================================
//  ʵ�ֹ���: ��ʱ��1 �жϷ���������
//  ����˵��: 
//  ������ע: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================  
extern unsigned int time3;
extern unsigned int timeflag3;

void TIM2_IRQHandler(void)
{

    if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
       TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);       
       time3++;
       timeflag3=1;
      
    }
     
}
//==================================================================================================
//  ʵ�ֹ���: ��ʱ��3 �жϷ���������
//  ����˵��: 
//  ������ע: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================  
extern unsigned int time2;
extern unsigned int timeflag2;

void TIM3_IRQHandler(void)   //TIM3�ж�
 {
     if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
     {
         
       TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
       
//       time2++;
//       timeflag2=1;

         
     }
 }
//==================================================================================================
//  ʵ�ֹ���: ��ʱ��4 �жϷ���������
//  ����˵��: 
//  ������ע: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 
extern unsigned int time4;
extern unsigned int timeflag4; 
 
void TIM4_IRQHandler(void)   //TIM4�ж�
{
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //���TIM4�����жϷ������
    {
      TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //���TIM4�����жϱ�־
       
       time4++;
       timeflag4=1;
    }
}    

//==================================================================================================
//  ʵ�ֹ���: ��ʱ��5 �жϷ���������
//  ����˵��: 
//  ������ע: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 

extern unsigned int time1;
extern unsigned int timeflag1;

void TIM5_IRQHandler(void)   //TIM3�ж�
{
    if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ
    {

      TIM_ClearITPendingBit(TIM5, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ
      
       time1++;
       timeflag1=1;
    }
      
}

//==================================================================================================
//  ʵ�ֹ���: ��ʱ��6,7 �жϷ���������
//  ����˵��:  ������ʱ��6��7 
//  ������ע: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 
extern unsigned int Basictime;
void  BASIC_TIM_IRQHandler (void)
{
	if ( TIM_GetITStatus( BASIC_TIM, TIM_IT_Update) != RESET ) 
	{	
		
		TIM_ClearITPendingBit(BASIC_TIM , TIM_FLAG_Update);
    
    Basictime++;

	}		 	
}

#ifndef  __ADC_H
#define  __ADC_H

//--------------------------------------------------------------------------------------------------
//  包含的头文件    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
#include "sys.h"


//==================================================================================================
// ADC采集配置函数声明
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 
void  Adc_Init(void);
u16 Get_Adc(unsigned char ch);//通道采集
u16 Get_Adc_Average(unsigned char ch,unsigned char times);//平均滤波
#endif



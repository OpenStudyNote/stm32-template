#ifndef __DHT11_H
#define __DHT11_H

//--------------------------------------------------------------------------------------------------
//  ���Զ�������    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
#define DHT11_IO    GPIOC
#define DHT11_PIN   GPIO_Pin_14
//IO��������
#define DHT11_IO_IN()  {DHT11_IO->CRH&=0XF0FFFFFF;DHT11_IO->CRH|=8<<24;}
#define DHT11_IO_OUT() {DHT11_IO->CRH&=0XF0FFFFFF;DHT11_IO->CRH|=3<<24;}
////IO��������											   
#define	DHT11_DQ_OUT PCout(14) //���ݶ˿�	PC14 
#define	DHT11_DQ_IN  PCin(14)  //���ݶ˿�	PC14 

//--------------------------------------------------------------------------------------------------
//  ���ú�������    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
unsigned char DHT11_Init(void);//��ʼ��DHT11
unsigned char DHT11_Read_Data(unsigned char *temp,unsigned char *humi);//��ȡ��ʪ��
unsigned char DHT11_Read_Byte(void);//����һ���ֽ�
unsigned char DHT11_Read_Bit(void);//����һ��λ
unsigned char DHT11_Check(void);//����Ƿ����DHT11
void DHT11_Rst(void);//��λDHT11


#endif

















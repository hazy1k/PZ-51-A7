#ifndef __ds18b20_H_
#define __ds18b20_H_

#include "public.h"


//--����ʹ�õ�IO��--//
sbit DS18B20_DQ_OUT=P3^7;

//--����ȫ�ֺ���--//
u8 DS18B20_Init(void);			//��ʼ��DS18B20
float DS18B20_GetTemperture(void);	//��ȡ�¶�
void DS18B20_Start(void);		//��ʼ�¶�ת��
void DS18B20_Write_Byte(u8 dat);//д��һ���ֽ�
u8 DS18B20_Read_Byte(void);		//����һ���ֽ�
u8 DS18B20_Read_Bit(void);		//����һ��λ
u8 DS18B20_Check(void);			//����Ƿ����DS18B20
void DS18B20_Reset(void);			//��λDS18B20 

#endif

#ifndef	  __XPT2046_H_
#define   __XPT2046_H_

//---����ͷ�ļ�---//
#include "public.h"


//---�ض���ؼ���---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint  unsigned int
#endif

#ifndef ulong
#define ulong  unsigned long
#endif

//---����ʹ�õ�IO��---//
sbit DOUT = P3^4;	  //���
sbit CLK  = P3^7;	  //ʱ��
sbit DIN  = P3^5;	  //����
sbit CS   = P3^6;	  //Ƭѡ

uint Read_AD_Data(uchar cmd);
uint SPI_Read(void);
void SPI_Write(uchar dat);

#endif






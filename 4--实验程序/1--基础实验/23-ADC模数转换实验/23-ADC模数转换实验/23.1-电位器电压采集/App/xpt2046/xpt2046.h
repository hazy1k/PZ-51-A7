#ifndef _xpt2046_H
#define _xpt2046_H

#include "public.h"

//�ܽŶ���
sbit DOUT = P3^7;	  //���
sbit CLK  = P3^6;	  //ʱ��
sbit DIN  = P3^4;	  //����
sbit CS   = P3^5;	  //Ƭѡ


//��������
u16 xpt2046_read_adc_value(u8 cmd);

#endif
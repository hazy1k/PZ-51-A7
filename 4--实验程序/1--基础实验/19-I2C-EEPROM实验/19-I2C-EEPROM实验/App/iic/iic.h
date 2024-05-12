#ifndef _iic_H
#define _iic_H

#include "public.h"

//����EEPROM���ƽ�
sbit IIC_SCL=P2^1;//SCLʱ����
sbit IIC_SDA=P2^0;//SDA������


//IIC���в�������				 
void iic_start(void);			//����IIC��ʼ�ź�
void iic_stop(void);	  		//����IICֹͣ�ź�
void iic_write_byte(u8 txd);	//IIC����һ���ֽ�
u8 iic_read_byte(u8 ack);		//IIC��ȡһ���ֽ�
u8 iic_wait_ack(void); 			//IIC�ȴ�ACK�ź�
void iic_ack(void);				//IIC����ACK�ź�
void iic_nack(void);			//IIC������ACK�ź�

#endif

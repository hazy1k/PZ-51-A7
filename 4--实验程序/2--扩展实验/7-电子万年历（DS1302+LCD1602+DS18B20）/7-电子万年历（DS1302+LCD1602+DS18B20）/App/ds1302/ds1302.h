#ifndef _ds1302_H
#define _ds1302_H

#include "public.h"

//�ܽŶ���
sbit DS1302_RST=P3^5;//��λ�ܽ�
sbit DS1302_CLK=P3^6;//ʱ�ӹܽ�
sbit DS1302_IO=P3^4;//���ݹܽ�

//��������
extern u8 gDS1302_TIME[7];//�洢ʱ��

//��������
void ds1302_init(void);
void ds1302_read_time(void);


#endif
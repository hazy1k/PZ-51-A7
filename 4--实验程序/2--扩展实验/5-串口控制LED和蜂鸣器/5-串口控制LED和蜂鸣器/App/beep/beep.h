#ifndef _beep_H
#define _beep_H

#include "public.h"

//�ܽŶ���
sbit BEEP=P2^5;

//��������
void beep_alarm(u16 time,u16 fre);
#endif

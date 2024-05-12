#ifndef _pwm_H
#define _pwm_H

#include "public.h"


//�ܽŶ���
sbit PWM=P2^1;

//��������
extern u8 gtim_scale;

//��������
void pwm_init(u8 tim_h,u8 tim_l,u16 tim_scale,u8 duty);
void pwm_set_duty_cycle(u8 duty);

#endif

#ifndef _pwm_H
#define _pwm_H

#include "public.h"


//管脚定义
sbit PWM=P2^1;

//变量声明
extern u8 gtim_scale;

//函数声明
void pwm_init(u8 tim_h,u8 tim_l,u16 tim_scale,u8 duty);
void pwm_set_duty_cycle(u8 duty);

#endif

#include "pwm.h"

//全局变量定义
u8 gtim_h=0;//保存定时器初值高8位
u8 gtim_l=0;//保存定时器初值低8位
u8 gduty=0;//保存PWM占空比
u8 gtim_scale=0;//保存PWM周期=定时器初值*tim_scale


/*******************************************************************************
* 函 数 名       : pwm_init
* 函数功能		 : PWM初始化函数
* 输    入       : tim_h：定时器高8位
				   tim_l：定时器低8位
				   tim_scale：PWM周期倍数：定时器初值*tim_scale
				   duty：PWM占空比（要小于等于tim_scale）
* 输    出    	 : 无
*******************************************************************************/
void pwm_init(u8 tim_h,u8 tim_l,u16 tim_scale,u8 duty)
{
	gtim_h=tim_h;//将传入的初值保存在全局变量中，方便中断函数继续调用
	gtim_l=tim_l;
	gduty=duty;
	gtim_scale=tim_scale;

	TMOD|=0X01;	//选择为定时器0模式，工作方式1
	TH0 = gtim_h;	//定时初值设置 
	TL0 = gtim_l;		
	ET0=1;//打开定时器0中断允许
	EA=1;//打开总中断
	TR0=1;//打开定时器
}

/*******************************************************************************
* 函 数 名       : pwm_set_duty_cycle
* 函数功能		 : PWM设置占空比
* 输    入       : duty：PWM占空比（要小于等于tim_scale）
* 输    出    	 : 无
*******************************************************************************/
void pwm_set_duty_cycle(u8 duty)
{
	gduty=duty;	
}

void pwm(void) interrupt 1	//定时器0中断函数
{
	static u16 time=0;

	TH0 = gtim_h;	//定时初值设置 
	TL0 = gtim_l;
	
	time++;
	if(time>=gtim_scale)//PWM周期=定时器初值*gtim_scale，重新开始计数
		time=0;
	if(time<=gduty)//占空比	
		PWM=1;
	else
		PWM=0;		
}
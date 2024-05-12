/**************************************************************************************
深圳市普中科技有限公司（PRECHIN 普中）
技术支持：www.prechin.net
PRECHIN
 普中
 
实验名称：红外遥控LED和蜂鸣器
接线说明：	
实验现象：下载程序后，操作红外遥控器最上面第1个键和第2个键可控制D1和蜂鸣器开关，并且数码管
			上显示遥控器键值码
注意事项：红外接收头凸起处要与PCB板接口凸起丝印处对应																				  
***************************************************************************************/
#include "public.h"
#include "smg.h"
#include "ired.h"
#include "beep.h"

//定义端口
sbit LED1=P2^0;

//定义宏值
#define LED_KEY_VALUE		0X45
#define BEEP_KEY_VALUE		0X46

/*******************************************************************************
* 函 数 名       : main
* 函数功能		 : 主函数
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/
void main()
{	
	u8 ired_buf[3];
	u8 key_cnt_led=0;
	u8 key_cnt_beep=0;
	u8 ired_tempx=0;
	u8 ired_tempy=0;

	ired_init();//红外初始化
	
	while(1)
	{
		ired_tempx=gired_data[2];//保存键值
		if(ired_tempx!=0)ired_tempy=ired_tempx;//当不为0时则更新数码管显示键值
		ired_buf[0]=gsmg_code[ired_tempy/16];//将控制码高4位转换为数码管段码
		ired_buf[1]=gsmg_code[ired_tempy%16];//将控制码低4位转换为数码管段码
		ired_buf[2]=0X76;//显示H的段码
		smg_display(ired_buf,6);

		if(ired_tempx==LED_KEY_VALUE)//如果是第一键按下
		{
			gired_data[2]=0;//清零,等待下次按键按下
			key_cnt_led++;
			if(key_cnt_led==3)key_cnt_led=1;
		}
		else if(ired_tempx==BEEP_KEY_VALUE)//如果是第一键按下
		{
			gired_data[2]=0;//清零,等待下次按键按下
			key_cnt_beep++;
			if(key_cnt_beep==3)key_cnt_beep=1;
		}

		if(key_cnt_led==1)LED1=0;
		else LED1=1;
		if(key_cnt_beep==1)beep_alarm(100,10);
	}
}

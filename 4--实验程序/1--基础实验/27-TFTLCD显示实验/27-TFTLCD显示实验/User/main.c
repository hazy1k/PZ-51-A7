/**************************************************************************************
深圳市普中科技有限公司（PRECHIN 普中）
技术支持：www.prechin.net

实验名称：TFTLCD显示实验
接线说明：	
实验现象：下载程序后，插上TFTLCD彩屏（要购买含TFTLCD彩屏套餐）显示汉字字符信息
注意事项：																				  
***************************************************************************************/

#include "public.h"  
#include "uart.h"
#include "tftlcd.h"
#include "gui.h"
#include "picture.h"



void main()
{
	UART_Init();//串口初始化，方便使用printf调试
	TFTLCD_Init();//TFTLCD初始化
		
	FRONT_COLOR=WHITE;
	LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,12,"Hello World");
	LCD_ShowString(10,30,tftlcd_data.width,tftlcd_data.height,16,"Hello World");
	LCD_ShowString(10,50,tftlcd_data.width,tftlcd_data.height,24,"Hello World");
	LCD_ShowString(10,80,tftlcd_data.width,tftlcd_data.height,16,"0123456789");
	LCD_ShowFontHZ(10,100,"普中科技");
//	LCD_ShowPicture(10,60,56,56,gImage_picture_snow);
	
	while(1)
	{
		
	}					
}

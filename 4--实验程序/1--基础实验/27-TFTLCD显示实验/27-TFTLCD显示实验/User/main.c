/**************************************************************************************
���������пƼ����޹�˾��PRECHIN ���У�
����֧�֣�www.prechin.net

ʵ�����ƣ�TFTLCD��ʾʵ��
����˵����	
ʵ���������س���󣬲���TFTLCD������Ҫ����TFTLCD�����ײͣ���ʾ�����ַ���Ϣ
ע�����																				  
***************************************************************************************/

#include "public.h"  
#include "uart.h"
#include "tftlcd.h"
#include "gui.h"
#include "picture.h"



void main()
{
	UART_Init();//���ڳ�ʼ��������ʹ��printf����
	TFTLCD_Init();//TFTLCD��ʼ��
		
	FRONT_COLOR=WHITE;
	LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,12,"Hello World");
	LCD_ShowString(10,30,tftlcd_data.width,tftlcd_data.height,16,"Hello World");
	LCD_ShowString(10,50,tftlcd_data.width,tftlcd_data.height,24,"Hello World");
	LCD_ShowString(10,80,tftlcd_data.width,tftlcd_data.height,16,"0123456789");
	LCD_ShowFontHZ(10,100,"���пƼ�");
//	LCD_ShowPicture(10,60,56,56,gImage_picture_snow);
	
	while(1)
	{
		
	}					
}

/**************************************************************************************
���������пƼ����޹�˾��PRECHIN ���У�
����֧�֣�www.prechin.net
PRECHIN
 ����																				  
***************************************************************************************/
#include "public.h"  
#include "uart.h"
#include "tftlcd.h"
#include "touch.h"
#include "gui.h"



//������ʾ����
void HZFontShow_Test(void)
{
	FRONT_COLOR=RED;
	LCD_ShowFontHZ(10,10,"���пƼ�");
	FRONT_COLOR=WHITE;
	LCD_ShowFontHZ(10,50,"���пƼ�");
	FRONT_COLOR=GREEN;
	LCD_ShowFontHZ(10,90,"���пƼ�");	
}

void main()
{

	UART_Init();
	TFTLCD_Init();

	HZFontShow_Test();
	
	while(1)
	{
				
	}					
}

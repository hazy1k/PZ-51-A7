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



#define LED_START_X		20	  			//LED��ʼX����
#define LED_START_Y		80				//LED��ʼY����
#define LED_SPACE_X		10				//LED���X����
#define LED_RADIUS		15				//LEDͼ��Բ�뾶
#define LED_DIAMETER	LED_RADIUS*2	//LEDͼ��Բֱ��

#define LED_BACKCOLOR	WHITE  			//����ɫ
#define LED_FRONTCOLOR	BLUE   			//ǰ��ɫ
#define LED_SPEED		1000	 			//��λms


//��ˮ�ƹ�������
void LEDFlow_Test(void)
{
	u8 i=0;

	FRONT_COLOR=RED;
	LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,16,"LED Flow Test");
	for(i=0;i<4;i++)
	{
		gui_fill_circle(LED_START_X+(LED_DIAMETER+LED_SPACE_X)*i,LED_START_Y,LED_RADIUS,LED_BACKCOLOR);	
	}
	
	while(1)
	{
		gui_fill_circle(LED_START_X+(LED_DIAMETER+LED_SPACE_X)*(3),LED_START_Y,LED_RADIUS,LED_BACKCOLOR);
		gui_fill_circle(LED_START_X+(LED_DIAMETER+LED_SPACE_X)*0,LED_START_Y,LED_RADIUS,LED_FRONTCOLOR);	
		delay_ms(LED_SPEED);
		for(i=1;i<4;i++)
		{
			gui_fill_circle(LED_START_X+(LED_DIAMETER+LED_SPACE_X)*(i-1),LED_START_Y,LED_RADIUS,LED_BACKCOLOR);
			gui_fill_circle(LED_START_X+(LED_DIAMETER+LED_SPACE_X)*i,LED_START_Y,LED_RADIUS,LED_FRONTCOLOR);	
			delay_ms(LED_SPEED);
		}	
	}	
}

void main()
{

	UART_Init();
	TFTLCD_Init();

	LEDFlow_Test();
	
	while(1)
	{
				
	}					
}

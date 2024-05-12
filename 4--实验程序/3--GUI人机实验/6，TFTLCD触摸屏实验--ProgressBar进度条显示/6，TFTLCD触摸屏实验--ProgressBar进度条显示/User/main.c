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



#define PROGRESSBAR_START_X		10	  	//��������ʼX����
#define PROGRESSBAR_START_Y		50		//��������ʼY����
#define PROGRESSBAR_WIDTH		100		//��������
#define PROGRESSBAR_HEIGHT		15		//��������

#define PROGRESSBAR_BACKCOLOR	GREEN  	//����ɫ
#define PROGRESSBAR_FRONTCOLOR	RED   	//ǰ��ɫ
#define PROGRESSBAR_FONTCOLOR	BLUE   //������ֵ��ɫ


//��������ʾ
//percent�����ȣ��ٷ���
void ProgressBar_Show(u8 percent)
{
	static u8 int_flag=0;
	u8 temp[4];
	u8 color_temp=0;
	u8 font_size=12;

	color_temp=BACK_COLOR;
	if(percent<10)
	{
		temp[0]=' ';
		temp[1]=' ';
		temp[2]=percent%100%10+0x30;	
	}	
	else if(percent<100)
	{
		temp[0]=' ';
		temp[1]=percent%100/10+0x30;
		temp[2]=percent%100%10+0x30;
	}
	else
	{
		temp[0]=percent/100+0x30;
		temp[1]=percent%100/10+0x30;
		temp[2]=percent%100%10+0x30;	
	}		
	temp[3]='%';
	if(int_flag==0) //ֻ����һ�γ�ʼ��
	{
		int_flag=1;
		gui_fill_rectangle(PROGRESSBAR_START_X,PROGRESSBAR_START_Y,PROGRESSBAR_WIDTH,PROGRESSBAR_HEIGHT,PROGRESSBAR_BACKCOLOR);		
	}
	gui_fill_rectangle(PROGRESSBAR_START_X,PROGRESSBAR_START_Y,percent,PROGRESSBAR_HEIGHT,PROGRESSBAR_FRONTCOLOR);
	if(percent>(PROGRESSBAR_WIDTH/2))
	{
		gui_show_strmidex(PROGRESSBAR_START_X,PROGRESSBAR_START_Y,PROGRESSBAR_WIDTH,PROGRESSBAR_HEIGHT,PROGRESSBAR_FONTCOLOR,font_size,temp,1);	
	}
	else
	{
		BACK_COLOR=PROGRESSBAR_BACKCOLOR;
		gui_show_strmidex(PROGRESSBAR_START_X,PROGRESSBAR_START_Y,PROGRESSBAR_WIDTH,PROGRESSBAR_HEIGHT,PROGRESSBAR_FONTCOLOR,font_size,temp,0);	
	}	
	BACK_COLOR=color_temp;
}

//����������
void ProgressBar_Test(void)
{
	u8 i=0;

	FRONT_COLOR=RED;
	LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,16,"ProgressBar Test");
	
	
	while(1)
	{
		gui_fill_rectangle(PROGRESSBAR_START_X,PROGRESSBAR_START_Y,PROGRESSBAR_WIDTH,PROGRESSBAR_HEIGHT,PROGRESSBAR_BACKCOLOR);
		for(i=1;i<=100;i++)
		{
			ProgressBar_Show(i);
			delay_ms(50);	
		}	
	}	
}

void main()
{

	UART_Init();
	TFTLCD_Init();

	ProgressBar_Test();
	
	while(1)
	{
				
	}					
}

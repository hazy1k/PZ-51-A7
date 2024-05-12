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



#define MULTIEDIT_START_X		10	  		//��ʼX����
#define MULTIEDIT_START_Y		70			//��ʼY����
#define MULTIEDIT_WIDTH			150			//��
#define MULTIEDIT_HEIGHT		100			//��

#define MULTIEDIT_RIM_LTOC 		0XA535	    //����������ɫ
#define MULTIEDIT_RIM_LTIC 		0X8431		//����������ɫ
#define MULTIEDIT_RIM_RBOC 		0XFFFF		//����������ɫ
#define MULTIEDIT_RIM_RBIC 		0XDEFC		//����������ɫ

#define MULTIEDIT_BACKCOLOR		WHITE  		//����ɫ
#define MULTIEDIT_FRONTCOLOR	BLUE   		//ǰ��ɫ
#define MULTIEDIT_FONTSIZE		16   		//�ı����������С

//�����ı��򴴽�
//x0,y0:���ε����Ͻ�����
//width,height:�ı���ĳߴ�
//backcolor:������ɫ
void MultiEdit_Create(u16 x0,u16 y0,u16 width,u16 height,u16 backcolor)
{
	gui_draw_vline(x0,y0,height,MULTIEDIT_RIM_LTOC);			//������
	gui_draw_hline(x0,y0,width,MULTIEDIT_RIM_LTOC);			//������
	gui_draw_vline(x0+1,y0+1,height-2,MULTIEDIT_RIM_LTIC);	//������
	gui_draw_hline(x0+1,y0+1,width-2,MULTIEDIT_RIM_LTIC);	//������
	gui_draw_vline(x0+width-1,y0,height,MULTIEDIT_RIM_RBOC);		//������
	gui_draw_hline(x0,y0+height-1,width,MULTIEDIT_RIM_RBOC);		//������
	gui_draw_vline(x0+width-2,y0+1,height-2,MULTIEDIT_RIM_RBIC);	//������
	gui_draw_hline(x0+1,y0+height-2,width-2,MULTIEDIT_RIM_RBIC);	//������
	gui_fill_rectangle(x0+2,y0+2,width-3,height-3,backcolor);//����ڲ�	
}

//�����ı�����ʾ�ַ���
//x0,y0:���ε����Ͻ�����
//width,height:�ı���ĳߴ�
//offset:��ʼ��ʾ��ƫ��
//backcolor:������ɫ
//frontcolor:ǰ����ɫ
//size:���ִ�С
//str:�ַ���
void MultiEdit_ShowString(u16 x0,u16 y0,u16 width,u16 height,u16 xoffset,u16 yoffset,u16 backcolor,u16 frontcolor,u8 size,u8 *str)
{
	static u16 color_temp=0;

	color_temp=BACK_COLOR;
	BACK_COLOR=backcolor;
	gui_show_stringex(x0+xoffset,y0+yoffset,width,height,frontcolor,size,str,0);
	BACK_COLOR=color_temp;	
}

const u8 multiedit_testbuf[]={"Hello everyone,I am MuYi,I'm very happy to learn with you."};

//�����ı������
void MultiEdit_Test(void)
{
	u16 t=0;

	FRONT_COLOR=RED;
	LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,16,"MultiEdit Test");
	FRONT_COLOR=GREEN;
	LCD_ShowString(10,50,tftlcd_data.width,tftlcd_data.height,16,"Send Message:"); 

	MultiEdit_Create(MULTIEDIT_START_X,MULTIEDIT_START_Y,MULTIEDIT_WIDTH,MULTIEDIT_HEIGHT,MULTIEDIT_BACKCOLOR); 
	MultiEdit_ShowString(MULTIEDIT_START_X,MULTIEDIT_START_Y,MULTIEDIT_WIDTH,MULTIEDIT_HEIGHT,5,4,MULTIEDIT_BACKCOLOR,MULTIEDIT_FRONTCOLOR,MULTIEDIT_FONTSIZE,multiedit_testbuf);
	while(1)
	{
			
	}	
}

void main()
{

	UART_Init();
	TFTLCD_Init();

	MultiEdit_Test();
	
	while(1)
	{
				
	}					
}

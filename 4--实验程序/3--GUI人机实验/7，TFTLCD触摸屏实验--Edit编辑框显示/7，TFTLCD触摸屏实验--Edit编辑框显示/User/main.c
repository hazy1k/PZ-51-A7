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



#define EDIT_START_X		65	  	//�༭����ʼX����
#define EDIT_START_Y		50		//�༭����ʼY����
#define EDIT_WIDTH			60		//�༭��
#define EDIT_HEIGHT			20		//�༭���

#define EDIT_RIM_LTOC 		0XA535	    //����������ɫ
#define EDIT_RIM_LTIC 		0X8431		//����������ɫ
#define EDIT_RIM_RBOC 		0XFFFF		//����������ɫ
#define EDIT_RIM_RBIC 		0XDEFC		//����������ɫ

#define EDIT_BACKCOLOR		WHITE  	//����ɫ
#define EDIT_FRONTCOLOR		BLUE   //ǰ��ɫ
#define EDIT_FONTSIZE		16   	//�ı����������С

//�༭�򴴽�
//x0,y0:���ε����Ͻ�����
//width,height:�ı���ĳߴ�
//backcolor:������ɫ
void Edit_Create(u16 x0,u16 y0,u16 width,u16 height,u16 backcolor)
{
	gui_draw_vline(x0,y0,height,EDIT_RIM_LTOC);			//������
	gui_draw_hline(x0,y0,width,EDIT_RIM_LTOC);			//������
	gui_draw_vline(x0+1,y0+1,height-2,EDIT_RIM_LTIC);	//������
	gui_draw_hline(x0+1,y0+1,width-2,EDIT_RIM_LTIC);	//������
	gui_draw_vline(x0+width-1,y0,height,EDIT_RIM_RBOC);		//������
	gui_draw_hline(x0,y0+height-1,width,EDIT_RIM_RBOC);		//������
	gui_draw_vline(x0+width-2,y0+1,height-2,EDIT_RIM_RBIC);	//������
	gui_draw_hline(x0+1,y0+height-2,width-2,EDIT_RIM_RBIC);	//������
	gui_fill_rectangle(x0+2,y0+2,width-3,height-3,backcolor);//����ڲ�	
}

//�༭����ʾ�ַ���
//x0,y0:���ε����Ͻ�����
//width,height:�ı���ĳߴ�
//backcolor:������ɫ
//frontcolor:ǰ����ɫ
//size:���ִ�С
//str:�ַ���
void Edit_ShowString(u16 x0,u16 y0,u16 width,u16 height,u16 backcolor,u16 frontcolor,u8 size,u8 *str)
{
	static u16 color_temp=0;

	color_temp=BACK_COLOR;
	BACK_COLOR=backcolor;
	gui_show_strmidex(x0,y0,width,height,frontcolor,size,str,0);
	BACK_COLOR=color_temp;	
}

//�༭����ʾ����
//x0,y0:���ε����Ͻ�����
//len :���ֵ�λ��
//backcolor:������ɫ
//frontcolor:ǰ����ɫ
//size:�����С
//num:��ֵ(0~2^64);
void Edit_ShowNum(u16 x0,u16 y0,u8 len,u16 backcolor,u16 frontcolor,u8 size,long num)
{
	static u16 color_temp=0;

	color_temp=BACK_COLOR;
	BACK_COLOR=backcolor;
	gui_show_num(x0+4,y0+3,len,frontcolor,size,num,0);
	BACK_COLOR=color_temp;	
}

//�༭�����
void Edit_Test(void)
{
	u16 t=0;

	FRONT_COLOR=RED;
	LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,16,"Edit Test");
	FRONT_COLOR=GREEN;
	LCD_ShowString(0,50,tftlcd_data.width,tftlcd_data.height,16,"Counter:"); 
	LCD_ShowString(0,80,tftlcd_data.width,tftlcd_data.height,16,"String :");
	Edit_Create(EDIT_START_X,EDIT_START_Y,EDIT_WIDTH,EDIT_HEIGHT,EDIT_BACKCOLOR); 
	Edit_Create(EDIT_START_X,EDIT_START_Y+30,EDIT_WIDTH,EDIT_HEIGHT,EDIT_BACKCOLOR);
	while(1)
	{
		t++;
		Edit_ShowNum(EDIT_START_X,EDIT_START_Y,6,EDIT_BACKCOLOR,EDIT_FRONTCOLOR,EDIT_FONTSIZE,t);			
	 	delay_ms(100);
		Edit_ShowString(EDIT_START_X,EDIT_START_Y+30,EDIT_WIDTH,EDIT_HEIGHT,EDIT_BACKCOLOR,EDIT_FRONTCOLOR,EDIT_FONTSIZE,"Hello");
	}	
}

void main()
{

	UART_Init();
	TFTLCD_Init();

	Edit_Test();
	
	while(1)
	{
				
	}					
}

/**************************************************************************************
���������пƼ����޹�˾��PRECHIN ���У�
����֧�֣�www.prechin.net
PRECHIN
 ����																				  
***************************************************************************************/
/**  
ע�⣺�漰������ͨ�ŵ��뽫��������12M���񻻳�11.0592MHZ��
	�����ڴ��ڳ�ʼ�������ڽ�TI=1ע�͵������Ա�ʵ�鲻��ʹ��printf����������tftlcd.c��
	TFTLCD��ʼ�������ڽ�ID��ӡ��printfע�͵��ˡ�
	���Ҫʹ��printf�����TI=1�����ǵ�������ť���º�TFTLCD��һ��ˢ�»������
	�������Ǹ����⡣
*/

#include "public.h"  
#include "uart.h"
#include "tftlcd.h"
#include "touch.h"
#include "gui.h"


sbit LED1=P3^6;

#define MULTIEDIT_START_X		10	  		//��ʼX����
#define MULTIEDIT_START_Y		40			//��ʼY����
#define MULTIEDIT_WIDTH			150			//��
#define MULTIEDIT_HEIGHT		40			//��

#define MULTIEDIT1_START_X		10	  		//��ʼX����
#define MULTIEDIT1_START_Y		HEIGHT-MULTIEDIT1_HEIGHT-10			//��ʼY����
#define MULTIEDIT1_WIDTH		150			//��
#define MULTIEDIT1_HEIGHT		60			//��

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






#define BUTTON_START_X		(MULTIEDIT_START_X+MULTIEDIT_WIDTH)/2-BUTTON_WIDTH	  		//��ʼX����
#define BUTTON_START_Y		MULTIEDIT_START_Y+MULTIEDIT_HEIGHT+5			//��ʼY����
#define BUTTON_WIDTH		50			//��
#define BUTTON_HEIGHT		40			//��
#define BUTTON_ARCSIZE		4  			//Ĭ��Բ�ǵİ뾶

#define BUTTON_SPACE_X		10  			//X���
#define BUTTON_SPACE_Y		10  			//Y���

//��ť��ɫ����
#define BTN_DFU_BCFUC		0X0000		//Ĭ���ɿ�����ɫ
#define BTN_DFU_BCFDC		0X0000		//Ĭ�ϰ��µ���ɫ

#define ARC_BTN_RIMC		0X0000		//Բ�ǰ�ť�߿���ɫ
#define ARC_BTN_TP1C		0XD6BB		//��һ�е���ɫ
#define ARC_BTN_UPHC		0X8452		//�ϰ벿����ɫ
#define ARC_BTN_DNHC		0X52CD		//�°벿����ɫ

#define BUTTON_BACKCOLOR	0XEF5D  	//����ɫ
#define BUTTON_FRONTCOLOR	BLACK   	//ǰ��ɫ
#define BUTTON_FONTSIZE		16   		//�����С


//���������Ƚ�ֵ
#define CONTROL_START_X		BUTTON_START_X
#define CONTROL_START_Y		BUTTON_START_Y
#define CONTROL_END_X		BUTTON_START_X+BUTTON_WIDTH
#define CONTROL_END_Y		BUTTON_START_Y+BUTTON_HEIGHT


//��ť����
//x0,y0:���ε����Ͻ�����
//width,height:�ı���ĳߴ�
//backcolor:������ɫ
void Button_Create(u16 x0,u16 y0,u16 width,u16 height,u8 r,u16 backcolor,u16 frontcolor,u8 size,u8*str)
{
	gui_draw_arcrectangle(x0,y0,width,height,r,1,ARC_BTN_UPHC,ARC_BTN_DNHC);//���Բ�ǰ�ť
	gui_draw_arcrectangle(x0,y0,width,height,r,0,ARC_BTN_RIMC,ARC_BTN_RIMC);//��Բ�Ǳ߿�
	gui_draw_hline (x0+r,y0+1,width-2*r,ARC_BTN_TP1C);//��һ��
	gui_show_strmid(x0+1,y0+1,width,height,frontcolor,size,str);
}

//��ť������ʾ
//x0,y0:���ε����Ͻ�����
//width,height:�ı���ĳߴ�
//backcolor:������ɫ
void Button_PressCreate(u16 x0,u16 y0,u16 width,u16 height,u8 r,u16 backcolor,u16 frontcolor,u8 size,u8*str)
{	
	gui_draw_arcrectangle(x0,y0,width,height,r,1,WHITE,WHITE);//���Բ�ǰ�ť
	gui_draw_arcrectangle(x0,y0,width,height,r,0,GREEN,GREEN);//��Բ�Ǳ߿�
	gui_draw_hline (x0+r,y0+1,width-2*r,ARC_BTN_TP1C);//��һ��
	gui_show_strmid(x0+1,y0+1,width,height,frontcolor,size,str);
}




const u8 Button_text[]={"Send"}; //��ť��ʾ�ı�
const u8 Send_testbuf[]={"Hello everyone,I am MuYi"};//��������
const u8 rec_clearbuf[]={"                                 "};//����������

//����ͨ��Ӧ�ò���
void UART_Test(void)
{
	u8 i=0;
	u8 Button_PressFlag=0;
	u8 rec_len=0;
	
	FRONT_COLOR=RED;
	LCD_ShowString(10,0,tftlcd_data.width,tftlcd_data.height,16,"UART Test");
	FRONT_COLOR=GREEN;
	LCD_ShowString(10,20,tftlcd_data.width,tftlcd_data.height,16,"Send Message:");
   	MultiEdit_Create(MULTIEDIT_START_X,MULTIEDIT_START_Y,MULTIEDIT_WIDTH,MULTIEDIT_HEIGHT,MULTIEDIT_BACKCOLOR); 
	MultiEdit_ShowString(MULTIEDIT_START_X,MULTIEDIT_START_Y,MULTIEDIT_WIDTH,MULTIEDIT_HEIGHT,5,4,MULTIEDIT_BACKCOLOR,MULTIEDIT_FRONTCOLOR,MULTIEDIT_FONTSIZE,Send_testbuf);
	Button_Create(BUTTON_START_X,BUTTON_START_Y,BUTTON_WIDTH,BUTTON_HEIGHT,BUTTON_ARCSIZE,BUTTON_BACKCOLOR,BUTTON_FRONTCOLOR,16,Button_text);  
	LCD_ShowString(10,BUTTON_START_Y+BUTTON_HEIGHT+5,tftlcd_data.width,tftlcd_data.height,16,"Receive Message:");
   	MultiEdit_Create(MULTIEDIT1_START_X,MULTIEDIT1_START_Y,MULTIEDIT1_WIDTH,MULTIEDIT1_HEIGHT,MULTIEDIT_BACKCOLOR); 
	
	UART_Cmd(ENABLE);
	while(1)
	{
		TOUCH_Scan();
		if(xpt_xy.sta)
		{
			if((xpt_xy.lcdx>=CONTROL_START_X) && (xpt_xy.lcdx<=CONTROL_END_X) && 
				(xpt_xy.lcdy>=CONTROL_START_Y) && (xpt_xy.lcdy<=CONTROL_END_Y))
			{
				xpt_xy.lcdx=0;
				xpt_xy.lcdy=0;
				Button_PressFlag=1;
			}
		}
		else
		{
			if(Button_PressFlag)
			{
				Button_PressFlag=0;
				Button_Create(BUTTON_START_X,BUTTON_START_Y,BUTTON_WIDTH,BUTTON_HEIGHT,BUTTON_ARCSIZE,BUTTON_BACKCOLOR,BUTTON_FRONTCOLOR,16,Button_text); 		  					
			}
		}
		if(Button_PressFlag)//��������
		{
			Button_PressCreate(BUTTON_START_X,BUTTON_START_Y,BUTTON_WIDTH,BUTTON_HEIGHT,BUTTON_ARCSIZE,BUTTON_BACKCOLOR,BUTTON_FRONTCOLOR,16,Button_text);			
			UART_SendString(Send_testbuf);
			UART_SendString("\r\n");
		}

		if((UART_RX_STA&0x8000))//���յ�����  ��λ����������ʱҪ�Ի��н�β����
		{
			MultiEdit_ShowString(MULTIEDIT1_START_X,MULTIEDIT1_START_Y,MULTIEDIT1_WIDTH,MULTIEDIT1_HEIGHT,5,4,MULTIEDIT_BACKCOLOR,MULTIEDIT_FRONTCOLOR,MULTIEDIT_FONTSIZE,rec_clearbuf);//���֮ǰ����ʾ����
			rec_len=UART_RX_STA&0X3FFF;
			UART_RX_BUF[rec_len]='\0';
			MultiEdit_ShowString(MULTIEDIT1_START_X,MULTIEDIT1_START_Y,MULTIEDIT1_WIDTH,MULTIEDIT1_HEIGHT,5,4,MULTIEDIT_BACKCOLOR,MULTIEDIT_FRONTCOLOR,MULTIEDIT_FONTSIZE,UART_RX_BUF);//��ʾ�½��յ�����			
			UART_RX_STA=0;
		}
		
		i++;
		if(i%20==0)
			LED1=!LED1;
		delay_ms(10);	
	}	
}

void main()
{	

	UART_Init();
	TFTLCD_Init();

	UART_Test();
	while(1)
	{
		
				
	}		
}

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


sbit LED1=P3^5;
sbit LED2=P3^6;
sbit LED3=P3^7;	


#define BUTTON_START_X		2	  		//��ʼX����
#define BUTTON_START_Y		70			//��ʼY����
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


//LED1���������Ƚ�ֵ
#define LED1_START_X		BUTTON_START_X
#define LED1_START_Y		BUTTON_START_Y
#define LED1_END_X			BUTTON_START_X+BUTTON_WIDTH
#define LED1_END_Y			BUTTON_START_Y+BUTTON_HEIGHT

//LED2���������Ƚ�ֵ
#define LED2_START_X		BUTTON_START_X+BUTTON_WIDTH+BUTTON_SPACE_X
#define LED2_START_Y		BUTTON_START_Y
#define LED2_END_X			BUTTON_START_X+BUTTON_WIDTH*2+BUTTON_SPACE_X
#define LED2_END_Y			BUTTON_START_Y+BUTTON_HEIGHT

//LED3���������Ƚ�ֵ
#define LED3_START_X		BUTTON_START_X+BUTTON_WIDTH*2+BUTTON_SPACE_X*2
#define LED3_START_Y		BUTTON_START_Y
#define LED3_END_X			BUTTON_START_X+BUTTON_WIDTH*3+BUTTON_SPACE_X*2
#define LED3_END_Y			BUTTON_START_Y+BUTTON_HEIGHT


//LEDͼ�β���
#define LED_START_X		30	  			//LED��ʼX����
#define LED_START_Y		150				//LED��ʼY����
#define LED_SPACE_X		30				//LED���X����
#define LED_RADIUS		15				//LEDͼ��Բ�뾶
#define LED_DIAMETER	LED_RADIUS*2	//LEDͼ��Բֱ��

#define LED_BACKCOLOR	WHITE  			//����ɫ
#define LED_FRONTCOLOR	GREEN   		//ǰ��ɫ

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


const u8 Button_text[][5]={"LED1","LED2","LED3"};

//��ť����
void Button_Test(void)
{
	u8 i=0;
	u8 LED1_PressFlag=0;
	u8 LED2_PressFlag=0;
	u8 LED3_PressFlag=0;

	FRONT_COLOR=RED;
	LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,16,"Button Test");

	for(i=0;i<3;i++)
	{
		Button_Create(BUTTON_START_X+(BUTTON_SPACE_X+BUTTON_WIDTH)*i,BUTTON_START_Y,BUTTON_WIDTH,BUTTON_HEIGHT,BUTTON_ARCSIZE,BUTTON_BACKCOLOR,BUTTON_FRONTCOLOR,16,Button_text[i]); 		
	  	gui_fill_circle(LED_START_X+(LED_DIAMETER+LED_SPACE_X)*i,LED_START_Y,LED_RADIUS,LED_BACKCOLOR);
	}
	
	while(1)
	{
		TOUCH_Scan();

		if(xpt_xy.sta)
		{	
			//LED1
			if((xpt_xy.lcdx>=LED1_START_X) && (xpt_xy.lcdx<=LED1_END_X) && 
				(xpt_xy.lcdy>=LED1_START_Y) && (xpt_xy.lcdy<=LED1_END_Y))
			{
				xpt_xy.lcdx=0;
				xpt_xy.lcdy=0;
				LED1_PressFlag=1;
			}
		
			//LED2
			else if((xpt_xy.lcdx>=LED2_START_X) && (xpt_xy.lcdx<=LED2_END_X) && 
				(xpt_xy.lcdy>=LED2_START_Y) && (xpt_xy.lcdy<=LED2_END_Y))
			{
				xpt_xy.lcdx=0;
				xpt_xy.lcdy=0;
				LED2_PressFlag=1;
			}
			
			//LED3
			else if((xpt_xy.lcdx>=LED3_START_X) && (xpt_xy.lcdx<=LED3_END_X) && 
				(xpt_xy.lcdy>=LED3_START_Y) && (xpt_xy.lcdy<=LED3_END_Y))
			{
				xpt_xy.lcdx=0;
				xpt_xy.lcdy=0;
				LED3_PressFlag=1;
			}
		}
		else
		{
			if(LED1_PressFlag)
			{
				LED1_PressFlag=0;
				Button_Create(BUTTON_START_X+(BUTTON_SPACE_X+BUTTON_WIDTH)*0,BUTTON_START_Y,BUTTON_WIDTH,BUTTON_HEIGHT,BUTTON_ARCSIZE,BUTTON_BACKCOLOR,BUTTON_FRONTCOLOR,16,Button_text[0]); 		
			  	LED1=1;
				gui_fill_circle(LED_START_X+(LED_DIAMETER+LED_SPACE_X)*0,LED_START_Y,LED_RADIUS,LED_BACKCOLOR);  					
			}
			else if(LED2_PressFlag)
			{
				LED2_PressFlag=0;
				Button_Create(BUTTON_START_X+(BUTTON_SPACE_X+BUTTON_WIDTH)*1,BUTTON_START_Y,BUTTON_WIDTH,BUTTON_HEIGHT,BUTTON_ARCSIZE,BUTTON_BACKCOLOR,BUTTON_FRONTCOLOR,16,Button_text[1]); 		
			  	LED2=1;
				gui_fill_circle(LED_START_X+(LED_DIAMETER+LED_SPACE_X)*1,LED_START_Y,LED_RADIUS,LED_BACKCOLOR);  					
			}
			else if(LED3_PressFlag)
			{
				LED3_PressFlag=0;
				Button_Create(BUTTON_START_X+(BUTTON_SPACE_X+BUTTON_WIDTH)*2,BUTTON_START_Y,BUTTON_WIDTH,BUTTON_HEIGHT,BUTTON_ARCSIZE,BUTTON_BACKCOLOR,BUTTON_FRONTCOLOR,16,Button_text[2]); 		
			  	LED3=1;
				gui_fill_circle(LED_START_X+(LED_DIAMETER+LED_SPACE_X)*2,LED_START_Y,LED_RADIUS,LED_BACKCOLOR);  					
			}		
		}
		
		if(LED1_PressFlag)
		{
			Button_PressCreate(BUTTON_START_X+(BUTTON_SPACE_X+BUTTON_WIDTH)*0,BUTTON_START_Y,BUTTON_WIDTH,BUTTON_HEIGHT,BUTTON_ARCSIZE,BUTTON_BACKCOLOR,BUTTON_FRONTCOLOR,16,Button_text[0]);
			LED1=0;
			gui_fill_circle(LED_START_X+(LED_DIAMETER+LED_SPACE_X)*0,LED_START_Y,LED_RADIUS,LED_FRONTCOLOR);			
		}
		else if(LED2_PressFlag)
		{
			Button_PressCreate(BUTTON_START_X+(BUTTON_SPACE_X+BUTTON_WIDTH)*1,BUTTON_START_Y,BUTTON_WIDTH,BUTTON_HEIGHT,BUTTON_ARCSIZE,BUTTON_BACKCOLOR,BUTTON_FRONTCOLOR,16,Button_text[1]);
			LED2=0;
			gui_fill_circle(LED_START_X+(LED_DIAMETER+LED_SPACE_X)*1,LED_START_Y,LED_RADIUS,LED_FRONTCOLOR);			
		}
		else if(LED3_PressFlag)
		{
			Button_PressCreate(BUTTON_START_X+(BUTTON_SPACE_X+BUTTON_WIDTH)*2,BUTTON_START_Y,BUTTON_WIDTH,BUTTON_HEIGHT,BUTTON_ARCSIZE,BUTTON_BACKCOLOR,BUTTON_FRONTCOLOR,16,Button_text[2]);
			LED3=0;
			gui_fill_circle(LED_START_X+(LED_DIAMETER+LED_SPACE_X)*2,LED_START_Y,LED_RADIUS,LED_FRONTCOLOR);			
		}			
	}	
}

void main()
{

	UART_Init();
	TFTLCD_Init();

	Button_Test();
	
	while(1)
	{
				
	}					
}

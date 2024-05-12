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
#include "XPT2046.h"


sbit LED1=P3^1;



#define EDIT_START_X		85	  	//�༭����ʼX����
#define EDIT_START_Y		40		//�༭����ʼY����
#define EDIT_WIDTH			60		//�༭��
#define EDIT_HEIGHT			20		//�༭���
#define EDIT_SPACE_X   		20
#define EDIT_SPACE_Y   		20

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


//ADC��ͨ���ɼ�ϵͳ����
void Multichannel_ADC_SampleSystem_Test(void)
{
	u8 i=0;
	u16 r_advalue;
	u16 g_advalue;
	u16 t_advalue;
	u16 e_advalue;
	float r_vol;
	u8 strbuf[5];

	FRONT_COLOR=RED;
	LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,16,"Multichannel ADC Test");
	FRONT_COLOR=GREEN;
	LCD_ShowString(10,40,tftlcd_data.width,tftlcd_data.height,16,"R_Voltage:");
	LCD_ShowString(10,80,tftlcd_data.width,tftlcd_data.height,16,"G_ADValue:");
	LCD_ShowString(10,120,tftlcd_data.width,tftlcd_data.height,16,"T_ADValue:");
	LCD_ShowString(10,160,tftlcd_data.width,tftlcd_data.height,16,"E_Voltage:");
	LCD_ShowString(EDIT_START_X+EDIT_WIDTH+2,40,tftlcd_data.width,tftlcd_data.height,16,"V");
	LCD_ShowString(EDIT_START_X+EDIT_WIDTH+2,160,tftlcd_data.width,tftlcd_data.height,16,"V");
	for(i=0;i<4;i++)
	{
		Edit_Create(EDIT_START_X,EDIT_START_Y+(EDIT_HEIGHT+EDIT_SPACE_Y)*i,EDIT_WIDTH,EDIT_HEIGHT,EDIT_BACKCOLOR);	
	}
	 
	while(1)
	{
		i++;
		if(i%10==0)
		{
			LED1=!LED1;
			
			//��ȡXPT2046��4��ͨ��ADֵ
			r_advalue=Read_AD_Data(0x94);//AIN0
			t_advalue=Read_AD_Data(0xD4);//AIN1
			g_advalue=Read_AD_Data(0xA4);//AIN2
			e_advalue=Read_AD_Data(0xE4);//AIN3
			
			//AIN0--��λ����ѹת��
			r_vol=((float)r_advalue*5/4096)*10;
			r_advalue=r_vol;
			strbuf[0]=r_advalue/10+0x30;
			strbuf[1]='.';
			strbuf[2]=r_advalue%10+0x30;
			strbuf[3]='\0';
			Edit_ShowString(EDIT_START_X,EDIT_START_Y+(EDIT_HEIGHT+EDIT_SPACE_Y)*0,EDIT_WIDTH,EDIT_HEIGHT,EDIT_BACKCOLOR,EDIT_FRONTCOLOR,EDIT_FONTSIZE,strbuf);	
			//AIN1--����������ADֵת��
			strbuf[0]=t_advalue/1000+0x30;
			strbuf[1]=t_advalue%1000/100+0x30;
			strbuf[2]=t_advalue%1000%100/10+0x30;
			strbuf[3]=t_advalue%1000%100%10+0x30;
			strbuf[4]='\0';
			Edit_ShowString(EDIT_START_X,EDIT_START_Y+(EDIT_HEIGHT+EDIT_SPACE_Y)*1,EDIT_WIDTH,EDIT_HEIGHT,EDIT_BACKCOLOR,EDIT_FRONTCOLOR,EDIT_FONTSIZE,strbuf);	
		
			//AIN2--����������ADֵת��
			strbuf[0]=g_advalue/1000+0x30;
			strbuf[1]=g_advalue%1000/100+0x30;
			strbuf[2]=g_advalue%1000%100/10+0x30;
			strbuf[3]=g_advalue%1000%100%10+0x30;
			strbuf[4]='\0';
			Edit_ShowString(EDIT_START_X,EDIT_START_Y+(EDIT_HEIGHT+EDIT_SPACE_Y)*2,EDIT_WIDTH,EDIT_HEIGHT,EDIT_BACKCOLOR,EDIT_FRONTCOLOR,EDIT_FONTSIZE,strbuf);	
			
			//AIN3--�ⲿ��ѹת��
			r_vol=((float)e_advalue*5/4096)*10;
			e_advalue=r_vol;
			strbuf[0]=e_advalue/10+0x30;
			strbuf[1]='.';
			strbuf[2]=e_advalue%10+0x30;
			strbuf[3]='\0';
			Edit_ShowString(EDIT_START_X,EDIT_START_Y+(EDIT_HEIGHT+EDIT_SPACE_Y)*3,EDIT_WIDTH,EDIT_HEIGHT,EDIT_BACKCOLOR,EDIT_FRONTCOLOR,EDIT_FONTSIZE,strbuf);	
	
		}
		delay_ms(10);
	}	
}

void main()
{	

	UART_Init();
	TFTLCD_Init();

	Multichannel_ADC_SampleSystem_Test();
	while(1)
	{
		
				
	}		
}

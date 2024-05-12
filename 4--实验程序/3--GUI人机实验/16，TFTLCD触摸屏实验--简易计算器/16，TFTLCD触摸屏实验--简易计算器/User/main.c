/**************************************************************************************
���������пƼ����޹�˾��PRECHIN ���У�
����֧�֣�www.prechin.net
PRECHIN
 ����																				  
***************************************************************************************/
/**  
ע�⣺�漰������ͨ�ŵ��뽫��������12M���񻻳�11.0592MHZ��
*/

#include "public.h"  
#include "uart.h"
#include "tftlcd.h"
#include "touch.h"
#include "gui.h"
#include "stdlib.h"

sbit LED1=P3^6;

#define MULTIEDIT_START_X		10	  		//��ʼX����
#define MULTIEDIT_START_Y		20			//��ʼY����
#define MULTIEDIT_WIDTH			150			//��
#define MULTIEDIT_HEIGHT		20			//��

#define MULTIEDIT1_START_X		MULTIEDIT_START_X	  		//��ʼX����
#define MULTIEDIT1_START_Y		MULTIEDIT_START_Y+MULTIEDIT_HEIGHT+1			//��ʼY����

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






#define BUTTON_START_X		MULTIEDIT_START_X	  		//��ʼX����
#define BUTTON_START_Y		MULTIEDIT1_START_Y+MULTIEDIT_HEIGHT+5			//��ʼY����
#define BUTTON_WIDTH		30			//��
#define BUTTON_HEIGHT		30			//��
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




const u8 Button_text[][2]={"1","2","3","+",
						   "4","5","6","-",
						   "7","8","9","*",
						   "0","=","C","/"}; //��ť��ʾ�ı�

#define ADD		1  //��
#define MINUS	2  //��
#define RIDE	3  //��
#define EXCEPT	4  //��
#define EQUAL	5  //����
#define CLEAR	6  //���

//���׼���������
void Calculator_Test(void)
{
	u8 i=0;
	u8 j=0;
	u8 Button_PressFlag=0;
	u8 cx,cy;
	u8 total_cnt=0;
	u8 dat1_numstr[6];
	u8 dat1_cnt=0;
	u8 dat2_numstr[6];
	u8 dat2_cnt=0;
	u8 fuhao_value=0;
	u8 fuhao_flag=0;
	int dat1_num=0;
	int dat2_num=0;
	int result=0;
	char result_buf[15];
	
	FRONT_COLOR=RED;
	LCD_ShowString(10,0,tftlcd_data.width,tftlcd_data.height,16,"Calculator Test");
   	MultiEdit_Create(MULTIEDIT_START_X,MULTIEDIT_START_Y,MULTIEDIT_WIDTH,MULTIEDIT_HEIGHT,MULTIEDIT_BACKCOLOR); 
	MultiEdit_ShowString(MULTIEDIT_START_X,MULTIEDIT_START_Y,MULTIEDIT_WIDTH,MULTIEDIT_HEIGHT,5,2,MULTIEDIT_BACKCOLOR,MULTIEDIT_FRONTCOLOR,MULTIEDIT_FONTSIZE," ");
	MultiEdit_Create(MULTIEDIT1_START_X,MULTIEDIT1_START_Y,MULTIEDIT_WIDTH,MULTIEDIT_HEIGHT,MULTIEDIT_BACKCOLOR); 
	MultiEdit_ShowString(MULTIEDIT1_START_X,MULTIEDIT1_START_Y,MULTIEDIT_WIDTH,MULTIEDIT_HEIGHT,5,2,MULTIEDIT_BACKCOLOR,MULTIEDIT_FRONTCOLOR,MULTIEDIT_FONTSIZE,"0");
	
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			Button_Create(BUTTON_START_X+(BUTTON_SPACE_X+BUTTON_WIDTH)*j,BUTTON_START_Y+(BUTTON_SPACE_Y+BUTTON_HEIGHT)*i,BUTTON_WIDTH,BUTTON_HEIGHT,BUTTON_ARCSIZE,BUTTON_BACKCOLOR,BUTTON_FRONTCOLOR,16,Button_text[4*i+j]);	
		}	
	}
	
	while(1)
	{
		TOUCH_Scan();
		if(xpt_xy.sta)
		{
			for(i=0;i<4;i++)   //ɨ�谴ť����ȡ��Ӧ��λ����Ϣ
			{
				for(j=0;j<4;j++)
				{
					if((xpt_xy.lcdx>=BUTTON_START_X+(BUTTON_SPACE_X+BUTTON_WIDTH)*j) && 
						(xpt_xy.lcdx<=BUTTON_START_X+BUTTON_WIDTH+(BUTTON_SPACE_X+BUTTON_WIDTH)*j)
						 && (xpt_xy.lcdy>=BUTTON_START_Y+(BUTTON_SPACE_Y+BUTTON_HEIGHT)*i) && 
						(xpt_xy.lcdy<=BUTTON_START_Y+BUTTON_HEIGHT+(BUTTON_SPACE_Y+BUTTON_HEIGHT)*i))
					{
						cx=j;
						cy=i;
						Button_PressFlag=1;			
					}
				}	
			}
			//ȷ���Ƿ������ּ����£������ǵ�1������������������ֵ��ϵ��ַ�����dat1_numstr��
			if((dat1_cnt<6) && (!fuhao_flag))
			{
				if(!strcmp(Button_text[4*cy+cx],"1") || !strcmp(Button_text[4*cy+cx],"2") || 
					!strcmp(Button_text[4*cy+cx],"3") || !strcmp(Button_text[4*cy+cx],"4") || 
					!strcmp(Button_text[4*cy+cx],"5") || !strcmp(Button_text[4*cy+cx],"6") || 
					!strcmp(Button_text[4*cy+cx],"7") || !strcmp(Button_text[4*cy+cx],"8") ||
					!strcmp(Button_text[4*cy+cx],"9") || !strcmp(Button_text[4*cy+cx],"0") )
				{									
					dat1_numstr[dat1_cnt++]=atoi(Button_text[4*cy+cx])+0x30;
					printf("dat1_numstr[dat1_cnt-1]=%c\r\n",dat1_numstr[dat1_cnt-1]);
				}	
			}
			//ȷ���Ƿ������ּ����£������ǵ�2������������������ֵ��ϵ��ַ�����dat2_numstr��
			else if((dat2_cnt<6) && (fuhao_flag))
			{
				if(!strcmp(Button_text[4*cy+cx],"1") || !strcmp(Button_text[4*cy+cx],"2") || 
					!strcmp(Button_text[4*cy+cx],"3") || !strcmp(Button_text[4*cy+cx],"4") || 
					!strcmp(Button_text[4*cy+cx],"5") || !strcmp(Button_text[4*cy+cx],"6") || 
					!strcmp(Button_text[4*cy+cx],"7") || !strcmp(Button_text[4*cy+cx],"8") ||
					!strcmp(Button_text[4*cy+cx],"9") || !strcmp(Button_text[4*cy+cx],"0") )
				{									
					dat2_numstr[dat2_cnt++]=atoi(Button_text[4*cy+cx])+0x30;
					printf("dat2_numstr[dat2_cnt-1]=%c\r\n",dat2_numstr[dat2_cnt-1]);
				}	
			}
			//�ж��Ƿ���������ţ�����¼�����
			if(!strcmp(Button_text[4*cy+cx],"+") || !strcmp(Button_text[4*cy+cx],"-") ||
				!strcmp(Button_text[4*cy+cx],"*") || !strcmp(Button_text[4*cy+cx],"/"))
			{
				fuhao_flag=1;//��������������
				dat1_num=atoi(dat1_numstr);//����ȡ�ĵ�1���������ַ���ת��Ϊ��ֵ���ȴ���������
				printf("dat1_num=%d\r\n",dat1_num);
				if(!strcmp(Button_text[4*cy+cx],"+"))
					fuhao_value=ADD;
				else if(!strcmp(Button_text[4*cy+cx],"-"))
					fuhao_value=MINUS;
				else if(!strcmp(Button_text[4*cy+cx],"*"))
					fuhao_value=RIDE;
				else if(!strcmp(Button_text[4*cy+cx],"/"))
					fuhao_value=EXCEPT;
			}
			
			//���������洢����ת��Ϊ�ַ���������ʾ
			if(!strcmp(Button_text[4*cy+cx],"="))
			{
				dat2_num=atoi(dat2_numstr);//����ȡ�ĵ�2���������ַ���ת��Ϊ��ֵ���ȴ���������	
				printf("dat2_num=%d\r\n",dat2_num);
				if(fuhao_value==ADD)//�ӷ�
				{
					result=dat1_num+dat2_num;		
				}
				else if(fuhao_value==MINUS)//����
				{
					result=dat1_num-dat2_num;		
				}
				else if(fuhao_value==RIDE)//�˷�
				{
					result=dat1_num*dat2_num;		
				}
				else if(fuhao_value==EXCEPT)//����
				{
					result=dat1_num/dat2_num;		
				}
				printf("result=%d\r\n",result);
				gui_num2strex(result,result_buf);//��ʮ����������ת��Ϊ�ַ���������ʾ
			  	printf("result_buf=%s\r\n",result_buf);
				MultiEdit_ShowString(MULTIEDIT1_START_X,MULTIEDIT1_START_Y,MULTIEDIT_WIDTH,MULTIEDIT_HEIGHT,5,2,MULTIEDIT_BACKCOLOR,MULTIEDIT_FRONTCOLOR,MULTIEDIT_FONTSIZE,result_buf);
				fuhao_value=EQUAL;
			}

			//�����������ʾ�ڵ�1���ı�����
			if(strcmp(Button_text[4*cy+cx],"C")!=0)
			{
				MultiEdit_ShowString(MULTIEDIT_START_X+(total_cnt*MULTIEDIT_FONTSIZE/2),MULTIEDIT_START_Y,MULTIEDIT_WIDTH,MULTIEDIT_HEIGHT,5,2,MULTIEDIT_BACKCOLOR,MULTIEDIT_FRONTCOLOR,MULTIEDIT_FONTSIZE,Button_text[4*cy+cx]);
				total_cnt++;	
			}
				
			if(!strcmp(Button_text[4*cy+cx],"C"))
			{
				cx=0;
				cy=0;
				fuhao_value=0;
				fuhao_flag=0;
				total_cnt=0;
				dat1_cnt=0;
				dat2_cnt=0;
				dat1_num=0;
				dat2_num=0;
				result=0;
				strcpy(dat1_numstr,"      ");
				strcpy(dat2_numstr,"      ");
				strcpy(result_buf,"      ");

				MultiEdit_ShowString(MULTIEDIT_START_X,MULTIEDIT_START_Y,MULTIEDIT_WIDTH,MULTIEDIT_HEIGHT,5,2,MULTIEDIT_BACKCOLOR,MULTIEDIT_FRONTCOLOR,MULTIEDIT_FONTSIZE,"                 ");
				MultiEdit_ShowString(MULTIEDIT1_START_X,MULTIEDIT1_START_Y,MULTIEDIT_WIDTH,MULTIEDIT_HEIGHT,5,2,MULTIEDIT_BACKCOLOR,MULTIEDIT_FRONTCOLOR,MULTIEDIT_FONTSIZE,result_buf);	
			}
	
		}
		else
		{
			if(Button_PressFlag)
			{
				Button_PressFlag=0;
				Button_Create(BUTTON_START_X+(BUTTON_SPACE_X+BUTTON_WIDTH)*cx,BUTTON_START_Y+(BUTTON_SPACE_Y+BUTTON_HEIGHT)*cy,BUTTON_WIDTH,BUTTON_HEIGHT,BUTTON_ARCSIZE,BUTTON_BACKCOLOR,BUTTON_FRONTCOLOR,16,Button_text[4*cy+cx]);
			}
		}
		if(Button_PressFlag)//��������
		{
			Button_PressCreate(BUTTON_START_X+(BUTTON_SPACE_X+BUTTON_WIDTH)*cx,BUTTON_START_Y+(BUTTON_SPACE_Y+BUTTON_HEIGHT)*cy,BUTTON_WIDTH,BUTTON_HEIGHT,BUTTON_ARCSIZE,BUTTON_BACKCOLOR,BUTTON_FRONTCOLOR,16,Button_text[4*cy+cx]);			
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

	Calculator_Test();
	while(1)
	{
		
				
	}		
}

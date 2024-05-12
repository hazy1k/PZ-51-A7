/**************************************************************************************
深圳市普中科技有限公司（PRECHIN 普中）
技术支持：www.prechin.net
PRECHIN
 普中																				  
***************************************************************************************/
#include "public.h"  
#include "uart.h"
#include "tftlcd.h"
#include "touch.h"
#include "gui.h"
#include "ds18b20.h"


sbit LED1=P3^6;


#define GRAPH_XSTART				5
#define GRAPH_YSTART				40
#define GRAPH_WIDTH					160
#define GRAPH_HEIGHT				130
#define GRAPH_BACKCOLOR				BLACK
#define GRAPH_FRONTCOLOR			GRAY
#define GRAPH_RIM_LTOC 				0XA535	    //左上外线颜色
#define GRAPH_RIM_LTIC 				0X8431		//左上内线颜色
#define GRAPH_RIM_RBOC 				0XFFFF		//右下外线颜色
#define GRAPH_RIM_RBIC 				0XDEFC		//右下内线颜色


#define VALID_AREA_SPACE_LEFT		30
#define VALID_AREA_SPACE_RIGHT		5
#define VALID_AREA_SPACE_TOP		5
#define VALID_AREA_SPACE_BOTTOM		5
#define VALID_AREA_GRID_XSTART		0
#define VALID_AREA_GRID_YSTART		0	
#define VALID_AREA_GRID_SPACE_X		20
#define VALID_AREA_GRID_SPACE_Y		20
#define VALID_AREA_GRID_LINE_COLOR	GRAY
#define VAILD_AREA_GRID_WIDTH		(GRAPH_WIDTH-VALID_AREA_SPACE_LEFT-VALID_AREA_SPACE_RIGHT)
#define VAILD_AREA_GRID_HEIGHT		(GRAPH_HEIGHT-VALID_AREA_SPACE_TOP-VALID_AREA_SPACE_BOTTOM)
#define VAILD_AREA_GRID_XNUM		(VAILD_AREA_GRID_WIDTH/VALID_AREA_GRID_SPACE_X)
#define VAILD_AREA_GRID_YNUM		(VAILD_AREA_GRID_HEIGHT/VALID_AREA_GRID_SPACE_Y)


#define TEXT_XSTART					GRAPH_XSTART
#define TEXT_YSTART					GRAPH_YSTART+VALID_AREA_SPACE_TOP
#define TEXT_XSPACE					VALID_AREA_GRID_SPACE_X
#define TEXT_YSPACE					VALID_AREA_GRID_SPACE_Y
#define TEXT_WIDTH					GRAPH_WIDTH-VAILD_AREA_GRID_WIDTH
#define TEXT_HEIGHT					GRAPH_HEIGHT-VAILD_AREA_GRID_HEIGHT
#define TEXT_COLOR					BLUE
#define TEXT_FONT					12

#define GRAPH_OBJECT_XSTART			GRAPH_XSTART+VALID_AREA_SPACE_LEFT+VALID_AREA_GRID_XSTART
#define GRAPH_OBJECT_YSTART			VAILD_AREA_GRID_HEIGHT+(GRAPH_YSTART+VALID_AREA_SPACE_TOP+VALID_AREA_GRID_YSTART)
#define GRAPH_OBJECT_COLOR			GREEN		

const u16 text_value[]={120,100,80,60,40,20};

//图形绘制
//x0,y0:图形的左上角坐标
//width,height:图形的尺寸
//backcolor:背景颜色
//frontcolor:前景颜色
void Graph_Create(u16 x0,u16 y0,u16 width,u16 height,u16 backcolor,u16 frontcolor)
{
	u8 i=0;

	gui_draw_vline(x0,y0,height,GRAPH_RIM_LTOC);				//左外线
	gui_draw_hline(x0,y0,width,GRAPH_RIM_LTOC);					//上外线
	gui_draw_vline(x0+1,y0+1,height-2,GRAPH_RIM_LTIC);			//左内线
	gui_draw_hline(x0+1,y0+1,width-2,GRAPH_RIM_LTIC);			//上内线
	gui_draw_vline(x0+width-1,y0,height,GRAPH_RIM_RBOC);		//右外线
	gui_draw_hline(x0,y0+height-1,width,GRAPH_RIM_RBOC);		//下外线
	gui_draw_vline(x0+width-2,y0+1,height-2,GRAPH_RIM_RBIC);	//右内线
	gui_draw_hline(x0+1,y0+height-2,width-2,GRAPH_RIM_RBIC);	//下内线
	gui_fill_rectangle(x0+2,y0+2,width-3,height-3,frontcolor);	//填充内部
	gui_fill_rectangle(x0+VALID_AREA_SPACE_LEFT,y0+VALID_AREA_SPACE_TOP,width-VALID_AREA_SPACE_LEFT-VALID_AREA_SPACE_RIGHT,height-VALID_AREA_SPACE_TOP-VALID_AREA_SPACE_BOTTOM,backcolor);
	
	for(i=0;i<VAILD_AREA_GRID_XNUM;i++)
	{
		gui_draw_vline(x0+VALID_AREA_SPACE_LEFT+VALID_AREA_GRID_XSTART+(VALID_AREA_GRID_SPACE_X*i),y0+VALID_AREA_SPACE_TOP,height-VALID_AREA_SPACE_TOP-VALID_AREA_SPACE_BOTTOM,VALID_AREA_GRID_LINE_COLOR);	
	}
	for(i=0;i<VAILD_AREA_GRID_YNUM;i++)
	{
		gui_draw_hline(x0+VALID_AREA_SPACE_LEFT+VALID_AREA_GRID_XSTART,y0+VALID_AREA_SPACE_TOP+(VALID_AREA_GRID_SPACE_Y*i),width-VALID_AREA_SPACE_LEFT-VALID_AREA_SPACE_RIGHT,VALID_AREA_GRID_LINE_COLOR);	
	}			
}

void ReDraw_ValidAreaGird(u16 x0,u16 y0,u16 width,u16 height,u16 backcolor,u16 frontcolor)
{
	u8 i=0;

	gui_fill_rectangle(x0+VALID_AREA_SPACE_LEFT,y0+VALID_AREA_SPACE_TOP,width-VALID_AREA_SPACE_LEFT-VALID_AREA_SPACE_RIGHT,height-VALID_AREA_SPACE_TOP-VALID_AREA_SPACE_BOTTOM,backcolor);
	
	for(i=0;i<VAILD_AREA_GRID_XNUM;i++)
	{
		gui_draw_vline(x0+VALID_AREA_SPACE_LEFT+VALID_AREA_GRID_XSTART+(VALID_AREA_GRID_SPACE_X*i),y0+VALID_AREA_SPACE_TOP,height-VALID_AREA_SPACE_TOP-VALID_AREA_SPACE_BOTTOM,VALID_AREA_GRID_LINE_COLOR);	
	}
	for(i=0;i<VAILD_AREA_GRID_YNUM;i++)
	{
		gui_draw_hline(x0+VALID_AREA_SPACE_LEFT+VALID_AREA_GRID_XSTART,y0+VALID_AREA_SPACE_TOP+(VALID_AREA_GRID_SPACE_Y*i),width-VALID_AREA_SPACE_LEFT-VALID_AREA_SPACE_RIGHT,VALID_AREA_GRID_LINE_COLOR);	
	}		
}



void Graph_AddText(u16 *value)
{
	u8 i=0;
	char text_str[VAILD_AREA_GRID_YNUM+1];

	for(i=0;i<VAILD_AREA_GRID_YNUM;i++)
	{	
		gui_num2strex(value[i], &text_str[i]);
		gui_show_strmid(TEXT_XSTART,TEXT_YSTART+(TEXT_YSPACE*i),TEXT_WIDTH,TEXT_HEIGHT,TEXT_COLOR,TEXT_FONT,&text_str[i]);	
	}
}

void Graph_AddValue(u16 x0,u16 y0,u16 value,u16 color,u16 sampletime)
{
	static u16 xtemp=GRAPH_OBJECT_XSTART;
	static u16 ytemp=GRAPH_OBJECT_YSTART;

	gui_draw_bline1(xtemp,ytemp,x0+sampletime,y0-value,1,color);
	xtemp=x0+sampletime;
	ytemp=y0-value;

	if((sampletime>VAILD_AREA_GRID_WIDTH) || (value>VAILD_AREA_GRID_HEIGHT))
	{
		xtemp=GRAPH_OBJECT_XSTART;
		ytemp=GRAPH_OBJECT_YSTART-value;
		ReDraw_ValidAreaGird(GRAPH_XSTART,GRAPH_YSTART,GRAPH_WIDTH,GRAPH_HEIGHT,GRAPH_BACKCOLOR,GRAPH_FRONTCOLOR);						
	}
}






#define EDIT_START_X		55	  	//编辑框起始X坐标
#define EDIT_START_Y		180		//编辑框起始Y坐标
#define EDIT_WIDTH			60		//编辑框长
#define EDIT_HEIGHT			20		//编辑框高

#define EDIT_RIM_LTOC 		0XA535	    //左上外线颜色
#define EDIT_RIM_LTIC 		0X8431		//左上内线颜色
#define EDIT_RIM_RBOC 		0XFFFF		//右下外线颜色
#define EDIT_RIM_RBIC 		0XDEFC		//右下内线颜色

#define EDIT_BACKCOLOR		WHITE  	//背景色
#define EDIT_FRONTCOLOR		BLUE   //前景色
#define EDIT_FONTSIZE		16   	//文本框内字体大小

//编辑框创建
//x0,y0:矩形的左上角坐标
//width,height:文本框的尺寸
//backcolor:背景颜色
void Edit_Create(u16 x0,u16 y0,u16 width,u16 height,u16 backcolor)
{
	gui_draw_vline(x0,y0,height,EDIT_RIM_LTOC);			//左外线
	gui_draw_hline(x0,y0,width,EDIT_RIM_LTOC);			//上外线
	gui_draw_vline(x0+1,y0+1,height-2,EDIT_RIM_LTIC);	//左内线
	gui_draw_hline(x0+1,y0+1,width-2,EDIT_RIM_LTIC);	//上内线
	gui_draw_vline(x0+width-1,y0,height,EDIT_RIM_RBOC);		//右外线
	gui_draw_hline(x0,y0+height-1,width,EDIT_RIM_RBOC);		//下外线
	gui_draw_vline(x0+width-2,y0+1,height-2,EDIT_RIM_RBIC);	//右内线
	gui_draw_hline(x0+1,y0+height-2,width-2,EDIT_RIM_RBIC);	//下内线
	gui_fill_rectangle(x0+2,y0+2,width-3,height-3,backcolor);//填充内部	
}

//编辑框显示字符串
//x0,y0:矩形的左上角坐标
//width,height:文本框的尺寸
//backcolor:背景颜色
//frontcolor:前景颜色
//size:文字大小
//str:字符串
void Edit_ShowString(u16 x0,u16 y0,u16 width,u16 height,u16 backcolor,u16 frontcolor,u8 size,u8 *str)
{
	static u16 color_temp=0;

	color_temp=BACK_COLOR;
	BACK_COLOR=backcolor;
	gui_show_strmidex(x0,y0,width,height,frontcolor,size,str,0);
	BACK_COLOR=color_temp;	
}

//编辑框显示数字
//x0,y0:矩形的左上角坐标
//len :数字的位数
//backcolor:背景颜色
//frontcolor:前景颜色
//size:字体大小
//num:数值(0~2^64);
void Edit_ShowNum(u16 x0,u16 y0,u8 len,u16 backcolor,u16 frontcolor,u8 size,long num)
{
	static u16 color_temp=0;

	color_temp=BACK_COLOR;
	BACK_COLOR=backcolor;
	gui_show_num(x0+4,y0+3,len,frontcolor,size,num,0);
	BACK_COLOR=color_temp;	
}


//温度监控系统测试
void TempertureControlSystem_Test(void)
{
	u8 i=0;
	float temper;
	int value=0;
	u8 buf[6];
	u16 samptime=0;
	u16 textvalue;

	DS18B20_GetTemperture();

	FRONT_COLOR=YELLOW;
	LCD_ShowString(10,180,tftlcd_data.width,tftlcd_data.height,16,"Temp:");
	LCD_ShowString(EDIT_START_X+EDIT_WIDTH+2,180,tftlcd_data.width,tftlcd_data.height,16,"^C"); 
	Edit_Create(EDIT_START_X,EDIT_START_Y,EDIT_WIDTH,EDIT_HEIGHT,EDIT_BACKCOLOR); 
	
	Graph_Create(GRAPH_XSTART,GRAPH_YSTART,GRAPH_WIDTH,GRAPH_HEIGHT,GRAPH_BACKCOLOR,GRAPH_FRONTCOLOR);
	Graph_AddText(text_value);

	while(1)
	{
		i++;
		if(i%10==0)
		{
			LED1=!LED1;
			samptime++;
			temper=DS18B20_GetTemperture();
			if(temper<0)
			{
				printf("检测的温度为：-");
			}
			else
			{
				printf("检测的温度为： ");
			}
			printf("%.2f°C\r\n",temper);

			value=temper;

			Graph_AddValue(GRAPH_OBJECT_XSTART,GRAPH_OBJECT_YSTART,value,GRAPH_OBJECT_COLOR,samptime);
			if((samptime>VAILD_AREA_GRID_WIDTH))samptime=0;
//			Edit_ShowNum(EDIT_START_X,EDIT_START_Y,6,EDIT_BACKCOLOR,EDIT_FRONTCOLOR,EDIT_FONTSIZE,value);
			textvalue=temper*10;
			buf[0]=textvalue/1000+0x30;
			buf[1]=textvalue%1000/100+0x30;
			buf[2]=textvalue%1000%100/10+0x30;
			buf[3]='.';
			buf[4]=textvalue%1000%100%10+0x30;
			buf[5]='\0';
			Edit_ShowString(EDIT_START_X,EDIT_START_Y,EDIT_WIDTH,EDIT_HEIGHT,EDIT_BACKCOLOR,EDIT_FRONTCOLOR,EDIT_FONTSIZE,buf);
		}
		delay_ms(10);
	}	
}

void main()
{	
	

	UART_Init();
	TFTLCD_Init();

	FRONT_COLOR=RED;
	LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,16,"Temperature Test");

	while(DS18B20_Init())
	{
		LCD_ShowString(10,30,tftlcd_data.width,tftlcd_data.height,16,"DS18B20 Error!");	
	}
	LCD_ShowString(10,30,tftlcd_data.width,tftlcd_data.height,16,"                 ");
	TempertureControlSystem_Test();
	while(1)
	{
		
				
	}		
}

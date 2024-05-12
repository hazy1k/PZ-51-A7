#include "calendar.h"
#include "ds1302.h"
#include "ds18b20.h"
#include "lcd1602.h"
#include "key.h"
#include "beep.h"
#include "time.h"


code u8 alarm_switch_str[]="Alarm: OFF";
code u8 alarm_on_str[]="ON ";
code u8 alarm_off_str[]="OFF";

_calendar g_calendar;

u8 g_keyvalue=0;

void time0() interrupt 1
{
	static u8 cnt=0;
	static u8 oneflag=1;
	TH0=0xDC;
	TL0=0x00; 
	cnt++;
	
	if(cnt==50)
	{
		cnt=0;
		if(g_calendar.mode==0)
			ds1302_read_time();			
		if(oneflag==1)
		{
			oneflag=0;
			g_calendar.alarm_time[0]=g_calendar.min;
			g_calendar.alarm_time[1]=g_calendar.hour;//记录初始闹钟时间		
		}
		g_calendar.temperture=ds18b20_read_temperture();		
	}
}

void calendar_datapros(u8 *datebuf,u8 *timebuf)
{
	datebuf[0]='2';
	datebuf[1]='0';
	datebuf[2]=g_calendar.year/16+0x30;
	datebuf[3]=g_calendar.year%16+0x30;
	datebuf[4]='-';
	datebuf[5]=g_calendar.month/16+0x30;
	datebuf[6]=g_calendar.month%16+0x30;
	datebuf[7]='-';
	datebuf[8]=g_calendar.day/16+0x30;
	datebuf[9]=g_calendar.day%16+0x30;
	datebuf[10]=' ';
	datebuf[11]='D';
	datebuf[12]='a';
	datebuf[13]='y';
	datebuf[14]=g_calendar.week%16+0x30;
	datebuf[15]='\0';

	timebuf[0]=g_calendar.hour/16+0x30;
	timebuf[1]=g_calendar.hour%16+0x30;
	timebuf[2]=':';
	timebuf[3]=g_calendar.min/16+0x30;
	timebuf[4]=g_calendar.min%16+0x30;
	timebuf[5]=':';
	timebuf[6]=g_calendar.sec/16+0x30;
	timebuf[7]=g_calendar.sec%16+0x30;
	timebuf[8]='\0';				
}

void temperture_datapros(u8 *tempbuf)
{
	int temp_value;

	temp_value=g_calendar.temperture*10;
	if(temp_value<0)
	{
		temp_value=-temp_value;
		tempbuf[0]='-';	
	}
	else
		tempbuf[0]=' ';
	if(temp_value>=1000)
		tempbuf[1]=temp_value/1000+0x30;
	else
		tempbuf[1]=' ';
	tempbuf[2]=temp_value%1000/100+0x30;
	tempbuf[3]=temp_value%1000%100/10+0x30;
	tempbuf[4]='.';
	tempbuf[5]=temp_value%1000%100%10+0x30;
	tempbuf[6]='C';
	tempbuf[7]='\0';		
}

void alarm_datapros(u8 *alarmbuf)
{
	alarmbuf[0]=g_calendar.alarm_time[1]/16+0x30;
	alarmbuf[1]=g_calendar.alarm_time[1]%16+0x30;
	alarmbuf[2]='-';
	alarmbuf[3]=g_calendar.alarm_time[0]/16+0x30;
	alarmbuf[4]=g_calendar.alarm_time[0]%16+0x30;
	alarmbuf[5]='\0';		
}

void calendar_save_set_time(void)
{
	gDS1302_TIME[0]=g_calendar.sec;
	gDS1302_TIME[1]=g_calendar.min;
	gDS1302_TIME[2]=g_calendar.hour;
	gDS1302_TIME[3]=g_calendar.day;
	gDS1302_TIME[4]=g_calendar.month;
	gDS1302_TIME[5]=g_calendar.week;
	gDS1302_TIME[6]=g_calendar.year;

	ds1302_init();		
}	  

void calendar_set_time(void)//时钟设置模式
{
	if(g_calendar.mode==1)//时钟设置
	{
		if(g_calendar.add==1)
		{
			g_calendar.add=0;	
			switch(g_calendar.time_choice)
			{
				case 0: g_calendar.sec++;
						if((g_calendar.sec&0x0f)>9)g_calendar.sec+=6;
						if(g_calendar.sec>=0x60)g_calendar.sec=0;
						break;
				case 1: g_calendar.min++;
						if((g_calendar.min&0x0f)>9)g_calendar.min+=6;
						if(g_calendar.min>=0x60)g_calendar.min=0;
						break;
				case 2: g_calendar.hour++;
						if((g_calendar.hour&0x0f)>9)g_calendar.hour+=6;
						if(g_calendar.hour>=0x24)g_calendar.hour=0;
						break;
				case 3: g_calendar.week++;
						if((g_calendar.week&0x0f)>9)g_calendar.week+=6;
						if(g_calendar.week>=0x08)g_calendar.week=1;
						break;
				case 4: g_calendar.day++;
						if((g_calendar.day&0x0f)>9)g_calendar.day+=6;
						if(g_calendar.day>=0x32)g_calendar.day=1;
						break;
				case 5: g_calendar.month++;
						if((g_calendar.month&0x0f)>9)g_calendar.month+=6;
						if(g_calendar.month>=0x13)g_calendar.month=1;
						break;
				case 6: g_calendar.year++;
						if((g_calendar.year&0x0f)>9)g_calendar.year+=6;
						if(g_calendar.year>=0x99)g_calendar.year=0;
						break;		
			}	
		}																
	}				
}

void calendar_set_alarm(void)//闹钟设置模式
{
	if(g_calendar.mode==2)//闹钟设置
	{
		if(g_calendar.add==1)
		{
			g_calendar.add=0;	
			switch(g_calendar.time_choice)
			{
				case 0: g_calendar.alarm_time[0]++;
						if((g_calendar.alarm_time[0]&0x0f)>9)g_calendar.alarm_time[0]+=6;
						if(g_calendar.alarm_time[0]>=0x60)g_calendar.alarm_time[0]=0;
						break;
				case 1: g_calendar.alarm_time[1]++;
						if((g_calendar.alarm_time[1]&0x0f)>9)g_calendar.alarm_time[1]+=6;
						if(g_calendar.alarm_time[1]>=0x24)g_calendar.alarm_time[1]=0;
						break; 
				case 2: g_calendar.alarm=!g_calendar.alarm;
						break;
				case 3: g_calendar.time_choice=0;
						break;
			}	
		}																	
	}		
}

void calendar_show(void)//时钟显示
{
	u8 date_buf[16];
	u8 time_buf[9];
	u8 temp_buf[8];

	if(g_calendar.mode==0)//正常模式显示
	{
		g_calendar.sec=gDS1302_TIME[0];	
		g_calendar.min=gDS1302_TIME[1];
		g_calendar.hour=gDS1302_TIME[2];
		g_calendar.day=gDS1302_TIME[3];
		g_calendar.month=gDS1302_TIME[4];
		g_calendar.week=gDS1302_TIME[5];
		g_calendar.year=gDS1302_TIME[6];

		calendar_datapros(date_buf,time_buf);			
		temperture_datapros(temp_buf);
		lcd1602_show_string(0,0,date_buf);
		lcd1602_show_string(0,1,time_buf);
		lcd1602_show_string(9,1,temp_buf);						
	}
	else if(g_calendar.mode==1)//时钟设置模式显示
	{
		calendar_datapros(date_buf,time_buf);			
		temperture_datapros(temp_buf);
		lcd1602_show_string(0,0,date_buf);
		lcd1602_show_string(0,1,time_buf);
		lcd1602_show_string(9,1,temp_buf);			
	}
	else if(g_calendar.mode==2)//闹钟设置模式显示
	{	
		alarm_datapros(time_buf);	
		lcd1602_show_string(0,1,time_buf);
		if(g_calendar.alarm)
			lcd1602_show_string(7,0,alarm_on_str);	
		else
			lcd1602_show_string(7,0,alarm_off_str);		
	}			
}

void alarm_compareproc(void)
{
	if(g_calendar.alarm&&g_calendar.setok)
	{
		if(g_calendar.alarm_time[1]==g_calendar.hour)
		{
			if(g_calendar.alarm_time[0]==g_calendar.min)//对比闹钟设置时间和当前时间，相同则闹铃
				beep_alarm(100,10);		
		}	
	}	
}

void calendar_test(void)
{
	u8 key_temp=0;

	lcd1602_init();
	ds1302_init();
	ds18b20_init();
	time0_init();//定时器10ms	
	while(1)
	{
		key_temp=key_scan(0);
		if(key_temp==KEY1_PRESS)//模式设置
		{
			g_calendar.mode++;
			if(g_calendar.mode==3)
				g_calendar.mode=1;
			g_calendar.setok=0;
			g_calendar.time_choice=0;
			if(g_calendar.mode==2)
			{
				lcd1602_clear();
				lcd1602_show_string(0,0,alarm_switch_str);	
			}
			beep_alarm(100,10);	
		}				
		else if(key_temp==KEY2_PRESS)//进入设置模式时，对应位选择设置
		{
			g_calendar.time_choice++;
			if(g_calendar.time_choice==7)
				g_calendar.time_choice=0;
			beep_alarm(100,10);
			
		}
		else if(key_temp==KEY3_PRESS)//进入设置模式时，进行数据加操作
		{
			g_calendar.add=1;
			beep_alarm(100,10);
		}	
		else if(key_temp==KEY4_PRESS)//设置完成，恢复正常显示模式
		{
			g_calendar.setok=1;
			g_calendar.time_choice=0;
			g_calendar.mode=0;
			calendar_save_set_time();
			beep_alarm(100,10);			
		}
		if(g_calendar.mode==1)//模拟光标闪烁
		{
			if(g_calendar.time_choice<3)
				lcd1602_show_string(7-g_calendar.time_choice*3,1," ");
			else if(g_calendar.time_choice>=3&&g_calendar.time_choice<4)
				lcd1602_show_string(14,0," ");
			else if(g_calendar.time_choice>=4&&g_calendar.time_choice<7)
				lcd1602_show_string(21-g_calendar.time_choice*3,0," ");		
		}
		else if(g_calendar.mode==2)//模拟光标闪烁
		{
			if(g_calendar.time_choice<2)
				lcd1602_show_string(4-g_calendar.time_choice*3,1," ");
			else if(g_calendar.time_choice==2)
				lcd1602_show_string(9,0," ");
			else if(g_calendar.time_choice==3)
				lcd1602_show_string(4,1," ");		
		}
				
		calendar_set_time();
		calendar_set_alarm();	
		calendar_show();
		alarm_compareproc();			
	}		
}


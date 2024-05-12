#ifndef __CALENDAR_H
#define __CALENDAR_H

#include "public.h"

typedef struct
{
	u8 sec;
	u8 min;
	u8 hour;
	u8 day;
	u8 month;
	u8 year;
	u8 week;
	u8 mode;//1：时钟设置模式；2：闹钟设置模式；
	u8 time_choice;//进入模式设置时，用于切换年月日时分秒哪个需要设置
	u8 add;//进入模式设置时，用于加
	u8 setok;//设置完成标志
	u8 alarm;//闹钟开关
	u8 alarm_time[2];//闹钟时间
	float temperture;		
}_calendar;
extern _calendar g_calendar;

void calendar_test(void);

#endif
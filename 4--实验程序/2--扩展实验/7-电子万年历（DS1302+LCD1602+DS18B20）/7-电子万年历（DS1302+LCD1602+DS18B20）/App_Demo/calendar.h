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
	u8 mode;//1��ʱ������ģʽ��2����������ģʽ��
	u8 time_choice;//����ģʽ����ʱ�������л�������ʱ�����ĸ���Ҫ����
	u8 add;//����ģʽ����ʱ�����ڼ�
	u8 setok;//������ɱ�־
	u8 alarm;//���ӿ���
	u8 alarm_time[2];//����ʱ��
	float temperture;		
}_calendar;
extern _calendar g_calendar;

void calendar_test(void);

#endif
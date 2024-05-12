/**************************************************************************************
���������пƼ����޹�˾��PRECHIN ���У�
����֧�֣�www.prechin.net
PRECHIN
 ����
 
ʵ�����ƣ���ʱ����LCD1602��ʾ��
����˵����	
ʵ���������س���󣬰���K1����ʼ��ʱ���ٴΰ���K1��ֹͣ��ʱ������K2������
ע���������LCD1602ʵ���½ڲ��LCD1602��������																				  
***************************************************************************************/
#include "public.h"
#include "key.h"
#include "beep.h"
#include "lcd1602.h"
#include "time.h"

/*******************************************************************************
* �� �� ��       : main
* ��������		 : ������
* ��    ��       : ��
* ��    ��    	 : ��
*******************************************************************************/
void main()
{	
	u8 key=0;
	u8 time_buf[9];
	u8 time_flag=0;

	lcd1602_init();
	time0_init();
	while(1)
	{
		key=key_scan(0);
		if(key==KEY1_PRESS)//��ʼ��ֹͣ��ʱ
		{
			time_flag=!time_flag;
			beep_alarm(1000,10);//������ʾ��
		}	
		else if(key==KEY2_PRESS)//�����ʱ
		{
			time0_stop();
			time_flag=0;
			gmin=0;
			gsec=0;
			gmsec=0;
			beep_alarm(1000,10);//������ʾ��		
		}
		if(time_flag)
			time0_start();//��ʼ��ʱ
		else
			time0_stop();//ֹͣ��ʱ
	
		time_buf[0]=gmin/10+0x30;
		time_buf[1]=gmin%10+0x30;//��
		time_buf[2]='-';//-
		time_buf[3]=gsec/10+0x30;
		time_buf[4]=gsec%10+0x30;//��
		time_buf[5]='-';//-
		time_buf[6]=gmsec/10+0x30;
		time_buf[7]=gmsec%10+0x30;//����
		time_buf[8]='\0';
		lcd1602_show_string(0,0,time_buf);//��ʾ	
	}
}

/**************************************************************************************
���������пƼ����޹�˾��PRECHIN ���У�
����֧�֣�www.prechin.net
PRECHIN
 ����
 
ʵ�����ƣ�����ң��LED�ͷ�����
����˵����	
ʵ���������س���󣬲�������ң�����������1�����͵�2�����ɿ���D1�ͷ��������أ����������
			����ʾң������ֵ��
ע������������ͷ͹��Ҫ��PCB��ӿ�͹��˿ӡ����Ӧ																				  
***************************************************************************************/
#include "public.h"
#include "smg.h"
#include "ired.h"
#include "beep.h"

//����˿�
sbit LED1=P2^0;

//�����ֵ
#define LED_KEY_VALUE		0X45
#define BEEP_KEY_VALUE		0X46

/*******************************************************************************
* �� �� ��       : main
* ��������		 : ������
* ��    ��       : ��
* ��    ��    	 : ��
*******************************************************************************/
void main()
{	
	u8 ired_buf[3];
	u8 key_cnt_led=0;
	u8 key_cnt_beep=0;
	u8 ired_tempx=0;
	u8 ired_tempy=0;

	ired_init();//�����ʼ��
	
	while(1)
	{
		ired_tempx=gired_data[2];//�����ֵ
		if(ired_tempx!=0)ired_tempy=ired_tempx;//����Ϊ0ʱ������������ʾ��ֵ
		ired_buf[0]=gsmg_code[ired_tempy/16];//���������4λת��Ϊ����ܶ���
		ired_buf[1]=gsmg_code[ired_tempy%16];//���������4λת��Ϊ����ܶ���
		ired_buf[2]=0X76;//��ʾH�Ķ���
		smg_display(ired_buf,6);

		if(ired_tempx==LED_KEY_VALUE)//����ǵ�һ������
		{
			gired_data[2]=0;//����,�ȴ��´ΰ�������
			key_cnt_led++;
			if(key_cnt_led==3)key_cnt_led=1;
		}
		else if(ired_tempx==BEEP_KEY_VALUE)//����ǵ�һ������
		{
			gired_data[2]=0;//����,�ȴ��´ΰ�������
			key_cnt_beep++;
			if(key_cnt_beep==3)key_cnt_beep=1;
		}

		if(key_cnt_led==1)LED1=0;
		else LED1=1;
		if(key_cnt_beep==1)beep_alarm(100,10);
	}
}

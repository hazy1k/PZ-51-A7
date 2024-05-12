#include "pwm.h"

//ȫ�ֱ�������
u8 gtim_h=0;//���涨ʱ����ֵ��8λ
u8 gtim_l=0;//���涨ʱ����ֵ��8λ
u8 gduty=0;//����PWMռ�ձ�
u8 gtim_scale=0;//����PWM����=��ʱ����ֵ*tim_scale


/*******************************************************************************
* �� �� ��       : pwm_init
* ��������		 : PWM��ʼ������
* ��    ��       : tim_h����ʱ����8λ
				   tim_l����ʱ����8λ
				   tim_scale��PWM���ڱ�������ʱ����ֵ*tim_scale
				   duty��PWMռ�ձȣ�ҪС�ڵ���tim_scale��
* ��    ��    	 : ��
*******************************************************************************/
void pwm_init(u8 tim_h,u8 tim_l,u16 tim_scale,u8 duty)
{
	gtim_h=tim_h;//������ĳ�ֵ������ȫ�ֱ����У������жϺ�����������
	gtim_l=tim_l;
	gduty=duty;
	gtim_scale=tim_scale;

	TMOD|=0X01;	//ѡ��Ϊ��ʱ��0ģʽ��������ʽ1
	TH0 = gtim_h;	//��ʱ��ֵ���� 
	TL0 = gtim_l;		
	ET0=1;//�򿪶�ʱ��0�ж�����
	EA=1;//�����ж�
	TR0=1;//�򿪶�ʱ��
}

/*******************************************************************************
* �� �� ��       : pwm_set_duty_cycle
* ��������		 : PWM����ռ�ձ�
* ��    ��       : duty��PWMռ�ձȣ�ҪС�ڵ���tim_scale��
* ��    ��    	 : ��
*******************************************************************************/
void pwm_set_duty_cycle(u8 duty)
{
	gduty=duty;	
}

void pwm(void) interrupt 1	//��ʱ��0�жϺ���
{
	static u16 time=0;

	TH0 = gtim_h;	//��ʱ��ֵ���� 
	TL0 = gtim_l;
	
	time++;
	if(time>=gtim_scale)//PWM����=��ʱ����ֵ*gtim_scale�����¿�ʼ����
		time=0;
	if(time<=gduty)//ռ�ձ�	
		PWM=1;
	else
		PWM=0;		
}
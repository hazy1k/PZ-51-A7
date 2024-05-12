/**************************************************************************************
���������пƼ����޹�˾��PRECHIN ���У�
����֧�֣�www.prechin.net
PRECHIN
 ����
 
ʵ�����ƣ����󰴼�ʵ��
����˵����	
ʵ���������س���󣬰��¡����󰴼���ģ����S1-S16������Ӧ��̬�������ʾ0-F
ע�����																				  
***************************************************************************************/
#include "reg52.h"

typedef unsigned int u16;	//��ϵͳĬ���������ͽ����ض���
typedef unsigned char u8;

#define KEY_MATRIX_PORT	P1	//ʹ�ú궨����󰴼����ƿ�		

#define SMG_A_DP_PORT	P0	//ʹ�ú궨������ܶ����

//�������������ʾ0~F�Ķ�������
u8 gsmg_code[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
				0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};	

/*******************************************************************************
* �� �� ��       : delay_10us
* ��������		 : ��ʱ������ten_us=1ʱ����Լ��ʱ10us
* ��    ��       : ten_us
* ��    ��    	 : ��
*******************************************************************************/
void delay_10us(u16 ten_us)
{
	while(ten_us--);	
}

/*******************************************************************************
* �� �� ��       : key_matrix_ranks_scan
* ��������		 : ʹ������ʽɨ�跽���������󰴼��Ƿ��£������򷵻ض�Ӧ��ֵ
* ��    ��       : ��
* ��    ��    	 : key_value��1-16����ӦS1-S16����
				   0������δ����
*******************************************************************************/
u8 key_matrix_ranks_scan(void)
{
	u8 key_value=0;

	KEY_MATRIX_PORT=0xf7;//����һ�и�ֵ0������ȫΪ1
	if(KEY_MATRIX_PORT!=0xf7)//�жϵ�һ�а����Ƿ���
	{
		delay_10us(1000);//����
		switch(KEY_MATRIX_PORT)//�����һ�а������º�ļ�ֵ	
		{
			case 0x77: key_value=1;break;
			case 0xb7: key_value=5;break;
			case 0xd7: key_value=9;break;
			case 0xe7: key_value=13;break;
		}
	}
	while(KEY_MATRIX_PORT!=0xf7);//�ȴ������ɿ�	
	
	KEY_MATRIX_PORT=0xfb;//���ڶ��и�ֵ0������ȫΪ1
	if(KEY_MATRIX_PORT!=0xfb)//�жϵڶ��а����Ƿ���
	{
		delay_10us(1000);//����
		switch(KEY_MATRIX_PORT)//����ڶ��а������º�ļ�ֵ	
		{
			case 0x7b: key_value=2;break;
			case 0xbb: key_value=6;break;
			case 0xdb: key_value=10;break;
			case 0xeb: key_value=14;break;
		}
	}
	while(KEY_MATRIX_PORT!=0xfb);//�ȴ������ɿ�	
	
	KEY_MATRIX_PORT=0xfd;//�������и�ֵ0������ȫΪ1
	if(KEY_MATRIX_PORT!=0xfd)//�жϵ����а����Ƿ���
	{
		delay_10us(1000);//����
		switch(KEY_MATRIX_PORT)//��������а������º�ļ�ֵ	
		{
			case 0x7d: key_value=3;break;
			case 0xbd: key_value=7;break;
			case 0xdd: key_value=11;break;
			case 0xed: key_value=15;break;
		}
	}
	while(KEY_MATRIX_PORT!=0xfd);//�ȴ������ɿ�	
	
	KEY_MATRIX_PORT=0xfe;//�������и�ֵ0������ȫΪ1
	if(KEY_MATRIX_PORT!=0xfe)//�жϵ����а����Ƿ���
	{
		delay_10us(1000);//����
		switch(KEY_MATRIX_PORT)//��������а������º�ļ�ֵ	
		{
			case 0x7e: key_value=4;break;
			case 0xbe: key_value=8;break;
			case 0xde: key_value=12;break;
			case 0xee: key_value=16;break;
		}
	}
	while(KEY_MATRIX_PORT!=0xfe);//�ȴ������ɿ�
	
	return key_value;		
}

/*******************************************************************************
* �� �� ��       : key_matrix_flip_scan
* ��������		 : ʹ���߷�תɨ�跽���������󰴼��Ƿ��£������򷵻ض�Ӧ��ֵ
* ��    ��       : ��
* ��    ��    	 : key_value��1-16����ӦS1-S16����
				   0������δ����
*******************************************************************************/
u8 key_matrix_flip_scan(void)
{
	static u8 key_value=0;

	KEY_MATRIX_PORT=0x0f;//�������и�ֵ0����ȫΪ1
	if(KEY_MATRIX_PORT!=0x0f)//�жϰ����Ƿ���
	{
		delay_10us(1000);//����
		if(KEY_MATRIX_PORT!=0x0f)
		{
			//������
			KEY_MATRIX_PORT=0x0f;
			switch(KEY_MATRIX_PORT)//������Ϊ0���������º����ֵ	
			{
				case 0x07: key_value=1;break;
				case 0x0b: key_value=2;break;
				case 0x0d: key_value=3;break;
				case 0x0e: key_value=4;break;
			}
			//������
			KEY_MATRIX_PORT=0xf0;
			switch(KEY_MATRIX_PORT)//������Ϊ0���������º�ļ�ֵ	
			{
				case 0x70: key_value=key_value;break;
				case 0xb0: key_value=key_value+4;break;
				case 0xd0: key_value=key_value+8;break;
				case 0xe0: key_value=key_value+12;break;
			}
			while(KEY_MATRIX_PORT!=0xf0);//�ȴ������ɿ�	
		}
	}
	else
		key_value=0;		
	
	return key_value;		
}

/*******************************************************************************
* �� �� ��       : main
* ��������		 : ������
* ��    ��       : ��
* ��    ��    	 : ��
*******************************************************************************/
void main()
{	
	u8 key=0;

	while(1)
	{
	   	key=key_matrix_ranks_scan();
		if(key!=0)
			SMG_A_DP_PORT=~gsmg_code[key-1];//�õ��İ���ֵ��1����������±��Ӧ0-F����		
	}		
}
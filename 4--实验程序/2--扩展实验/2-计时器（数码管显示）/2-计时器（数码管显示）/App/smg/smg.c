#include "smg.h"

//�������������ʾ0~F�Ķ�������
u8 gsmg_code[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
				0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

/*******************************************************************************
* �� �� ��       : smg_display
* ��������		 : ��̬�������ʾ
* ��    ��       : dat��Ҫ��ʾ������
				   pos������ʼ�ڼ���λ�ÿ�ʼ��ʾ����Χ1-8
* ��    ��    	 : ��
*******************************************************************************/
void smg_display(u8 dat[],u8 pos)
{
	u8 i=0;
	u8 pos_temp=pos-1;

	for(i=pos_temp;i<8;i++)
	{
	   	switch(i)//λѡ
		{
			case 0: LSC=1;LSB=1;LSA=1;break;
			case 1: LSC=1;LSB=1;LSA=0;break;
			case 2: LSC=1;LSB=0;LSA=1;break;
			case 3: LSC=1;LSB=0;LSA=0;break;
			case 4: LSC=0;LSB=1;LSA=1;break;
			case 5: LSC=0;LSB=1;LSA=0;break;
			case 6: LSC=0;LSB=0;LSA=1;break;
			case 7: LSC=0;LSB=0;LSA=0;break;
		}
		SMG_A_DP_PORT=dat[i-pos_temp];//���Ͷ�ѡ����
		delay_10us(100);//��ʱһ��ʱ�䣬�ȴ���ʾ�ȶ�
		SMG_A_DP_PORT=0x00;//����
	}
}

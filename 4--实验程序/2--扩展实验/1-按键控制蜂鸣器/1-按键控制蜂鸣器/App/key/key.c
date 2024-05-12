#include "key.h"

/*******************************************************************************
* �� �� ��       : key_scan
* ��������		 : �����������Ƿ��£������򷵻ض�Ӧ��ֵ
* ��    ��       : mode=0������ɨ�谴��
				   mode=1������ɨ�谴��
* ��    ��    	 : KEY1_PRESS��K1����
				   KEY2_PRESS��K2����
				   KEY3_PRESS��K3����
				   KEY4_PRESS��K4����
				   KEY_UNPRESS��δ�а�������
*******************************************************************************/
u8 key_scan(u8 mode)
{
	static u8 key=1;

	if(mode)key=1;//����ɨ�谴��
	if(key==1&&(KEY1==0||KEY2==0||KEY3==0||KEY4==0))//���ⰴ������
	{
		delay_10us(1000);//����
		key=0;
		if(KEY1==0)
			return KEY1_PRESS;
		else if(KEY2==0)
			return KEY2_PRESS;
		else if(KEY3==0)
			return KEY3_PRESS;
		else if(KEY4==0)
			return KEY4_PRESS;	
	}
	else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1)	//�ް�������
	{
		key=1;			
	}
	return KEY_UNPRESS;		
}
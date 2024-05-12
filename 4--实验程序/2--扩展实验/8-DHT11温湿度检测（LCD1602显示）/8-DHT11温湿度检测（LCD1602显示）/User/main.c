/**************************************************************************************
���������пƼ����޹�˾��PRECHIN ���У�
����֧�֣�www.prechin.net
PRECHIN
 ����
 
ʵ�����ƣ�DHT11��ʪ�ȼ�⣨LCD1602��ʾ��
����˵����DHT11��ʪ��ģ��-->��Ƭ��IO
		  VCC-->5V
		  DATA-->P2.3
		  GND-->GND	
ʵ���������س����LCD1602����ʾDHT11��ʪ�ȴ������ɼ����¶Ⱥ�ʪ��ֵ
ע���������LCD1602ʵ���½ڲ��LCD1602��������																				  
***************************************************************************************/
#include "public.h"
#include "lcd1602.h"
#include "dht11.h"

/*******************************************************************************
* �� �� ��       : main
* ��������		 : ������
* ��    ��       : ��
* ��    ��    	 : ��
*******************************************************************************/
void main()
{	
	u8 temp=0,humi=0;
	u8 i=0;
	u8 temp_buf[3],humi_buf[3];

	lcd1602_init();
	while(DHT11_Init())	//���DHT11�Ƿ����
	{
		lcd1602_show_string(0,0,"Error");		
	}
	lcd1602_show_string(0,0,"Temp:   C");
	lcd1602_show_string(0,1,"Humi:   %RH");
	while(1)
	{
		i++;
		if(i%200==0)
		{
			DHT11_Read_Data(&temp,&humi);
			temp_buf[0]=temp/10+0x30;	
			temp_buf[1]=temp%10+0x30;
			temp_buf[2]='\0';
			lcd1602_show_string(6,0,temp_buf);

			humi_buf[0]=humi/10+0x30;	
			humi_buf[1]=humi%10+0x30;
			humi_buf[2]='\0';
			lcd1602_show_string(6,1,humi_buf);	
		}
			
		delay_ms(1);		
	}
}

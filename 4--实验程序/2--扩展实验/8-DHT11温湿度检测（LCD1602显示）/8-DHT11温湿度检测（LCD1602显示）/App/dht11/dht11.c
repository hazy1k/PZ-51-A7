#include "dht11.h"
#include "intrins.h"


//DHT11��ʼ�� 
//����0����ʼ���ɹ���1��ʧ��
u8 DHT11_Init(void)
{
	DHT11_DQ=1;
	DHT11_Rst();	  
	return DHT11_Check();	
}

//��λDHT11
void DHT11_Rst(void)	   
{                 
	DHT11_DQ=1;
	delay_10us(1);
	DHT11_DQ=0; 	//����DQ
    delay_ms(25);   //��������18ms
    DHT11_DQ=1; 	//DQ=1 
	delay_10us(3);  //��������20~40us
}

//�ȴ�DHT11�Ļ�Ӧ
//����1:δ��⵽DHT11�Ĵ���
//����0:����
u8 DHT11_Check(void) 	   
{   
	u8 retry=0;
	
	while (!DHT11_DQ&&retry<100)//�жϴӻ����� 80us �ĵ͵�ƽ��Ӧ�ź��Ƿ����
	{
		retry++;
		_nop_();
	};
	if(retry>=100)return 1;
	else retry=0;
    while (DHT11_DQ&&retry<100)//�жϴӻ����� 80us �ĸߵ�ƽ�Ƿ������������������������ݽ���״̬
	{
		retry++;
		_nop_();
	};	 
	if(retry>=100)return 1;	    
	return 0;
}

//��DHT11��ȡһ���ֽ�
//����ֵ������������
u8 DHT11_Read_Byte(void)    
{        
    u8 i,temp;
	u8 data_byte=0; 
	u8 retry=0;

  	for(i=0;i<8;i++)//����8bit������ 
  	{ 
//		while(!DHT11_DQ);//�ȴ�50us�ĵ͵�ƽ��ʼ�źŽ���
		while (!DHT11_DQ&&retry<50)//�ȴ�50us�ĵ͵�ƽ��ʼ�źŽ���
		{
			retry++;
			_nop_();
		};
		retry=0; 
		delay_10us(3);//�ȴ�40us 
		temp=0;//ʱ��Ϊ26us-28us����ʾ���յ�Ϊ����'0' 
		if(DHT11_DQ==1) 
			temp=1; //���26us-28us֮�󪣻�Ϊ�ߵ�ƽ�����ʾ���յ�����Ϊ'1' 
//		while(DHT11_DQ);//�ȴ������źŸߵ�ƽ��'0'Ϊ26us-28us��'1'Ϊ70us
		while (DHT11_DQ&&retry<100)//�ȴ������źŸߵ�ƽ��'0'Ϊ26us-28us��'1'Ϊ70us
		{
			retry++;
			_nop_();
		};
		data_byte<<=1;//���յ�����Ϊ��λ��ǰ�����ƪ� 
		data_byte|=temp; 
  	} 

  	return data_byte;
}

//��DHT11��ȡһ������
//temp:�¶�ֵ(��Χ:0~50��)
//humi:ʪ��ֵ(��Χ:20%~90%)
//����ֵ��0,����;1,��ȡʧ��
u8 DHT11_Read_Data(u8 *temp,u8 *humi)    
{        
 	u8 buf[5];
	u8 i;
	DHT11_Rst();
	if(DHT11_Check()==0)
	{
		for(i=0;i<5;i++)//��ȡ40λ����
		{
			buf[i]=DHT11_Read_Byte();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{
			*humi=buf[0];
			*temp=buf[2];
		}
		
	}else return 1;
	return 0;	    
}


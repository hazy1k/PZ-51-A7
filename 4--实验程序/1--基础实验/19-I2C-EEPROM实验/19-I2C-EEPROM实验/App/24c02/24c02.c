#include "24c02.h"
#include "iic.h"


/*******************************************************************************
* �� �� ��         : at24c02_write_one_byte
* ��������		   : ��AT24CXXָ����ַд��һ������
* ��    ��         : addr:д�����ݵ�Ŀ�ĵ�ַ 
					 dat:Ҫд�������
* ��    ��         : ��
*******************************************************************************/
void at24c02_write_one_byte(u8 addr,u8 dat)
{				   	  	    																 
    iic_start();  
	iic_write_byte(0XA0);	//����д����	    	  
	iic_wait_ack();	   
    iic_write_byte(addr);	//����д��ַ   
	iic_wait_ack(); 	 										  		   
	iic_write_byte(dat);	//�����ֽ�    							   
	iic_wait_ack();  		    	   
    iic_stop();				//����һ��ֹͣ����
	delay_ms(10);	 
}

/*******************************************************************************
* �� �� ��         : at24c02_read_one_byte
* ��������		   : ��AT24CXXָ����ַ����һ������
* ��    ��         : addr:��ʼ�����ĵ�ַ 
* ��    ��         : ����������
*******************************************************************************/
u8 at24c02_read_one_byte(u8 addr)
{				  
	u8 temp=0;		  	    																 
    iic_start();  
	iic_write_byte(0XA0);	//����д����	   
	iic_wait_ack(); 
    iic_write_byte(addr); 	//����д��ַ  
	iic_wait_ack();	    
	iic_start();  	 	   
	iic_write_byte(0XA1); 	//�������ģʽ         			   
	iic_wait_ack();	 
    temp=iic_read_byte(0);	//��ȡ�ֽ�		   
    iic_stop();				//����һ��ֹͣ����    
	return temp;			//���ض�ȡ������
}


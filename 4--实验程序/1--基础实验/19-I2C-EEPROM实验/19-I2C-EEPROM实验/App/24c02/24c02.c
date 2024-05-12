#include "24c02.h"
#include "iic.h"


/*******************************************************************************
* 函 数 名         : at24c02_write_one_byte
* 函数功能		   : 在AT24CXX指定地址写入一个数据
* 输    入         : addr:写入数据的目的地址 
					 dat:要写入的数据
* 输    出         : 无
*******************************************************************************/
void at24c02_write_one_byte(u8 addr,u8 dat)
{				   	  	    																 
    iic_start();  
	iic_write_byte(0XA0);	//发送写命令	    	  
	iic_wait_ack();	   
    iic_write_byte(addr);	//发送写地址   
	iic_wait_ack(); 	 										  		   
	iic_write_byte(dat);	//发送字节    							   
	iic_wait_ack();  		    	   
    iic_stop();				//产生一个停止条件
	delay_ms(10);	 
}

/*******************************************************************************
* 函 数 名         : at24c02_read_one_byte
* 函数功能		   : 在AT24CXX指定地址读出一个数据
* 输    入         : addr:开始读数的地址 
* 输    出         : 读到的数据
*******************************************************************************/
u8 at24c02_read_one_byte(u8 addr)
{				  
	u8 temp=0;		  	    																 
    iic_start();  
	iic_write_byte(0XA0);	//发送写命令	   
	iic_wait_ack(); 
    iic_write_byte(addr); 	//发送写地址  
	iic_wait_ack();	    
	iic_start();  	 	   
	iic_write_byte(0XA1); 	//进入接收模式         			   
	iic_wait_ack();	 
    temp=iic_read_byte(0);	//读取字节		   
    iic_stop();				//产生一个停止条件    
	return temp;			//返回读取的数据
}


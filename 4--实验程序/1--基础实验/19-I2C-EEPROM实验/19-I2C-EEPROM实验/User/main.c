/**************************************************************************************
深圳市普中科技有限公司（PRECHIN 普中）
技术支持：www.prechin.net
PRECHIN
 普中
 
实验名称：I2C-EEPROM实验
接线说明：	
实验现象：下载程序后，数码管右3位显示0，按K1键将数据写入到EEPROM内保存，
		  按K2键读取EEPROM内保存的数据，按K3键显示数据加1，按K4键显示数据清零，
		  最大能写入的数据是255。
注意事项：																				  
***************************************************************************************/
#include "public.h"
#include "24c02.h"
#include "key.h"
#include "smg.h"


#define EEPROM_ADDRESS	0	//定义数据存入EEPROM的起始地址

/*******************************************************************************
* 函 数 名       : main
* 函数功能		 : 主函数
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/
void main()
{	
	u8 key_temp=0;
   	u8 save_value=0;
	u8 save_buf[3];

	while(1)
	{			
		key_temp=key_scan(0);
		if(key_temp==KEY1_PRESS)
		{
			at24c02_write_one_byte(EEPROM_ADDRESS,save_value);
		}
		else if(key_temp==KEY2_PRESS)
		{
			save_value=at24c02_read_one_byte(EEPROM_ADDRESS);
		}
		else if(key_temp==KEY3_PRESS)
		{
			save_value++;
			if(save_value==255)save_value=255;
		}
		else if(key_temp==KEY4_PRESS)
		{
			save_value=0;	
		}
		save_buf[0]=save_value/100;
		save_buf[1]=save_value%100/10;
		save_buf[2]=save_value%100%10;
		smg_display(save_buf,6);
	}		
}

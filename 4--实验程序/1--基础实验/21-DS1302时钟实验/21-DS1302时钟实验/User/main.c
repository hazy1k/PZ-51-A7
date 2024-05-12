/**************************************************************************************
深圳市普中科技有限公司（PRECHIN 普中）
技术支持：www.prechin.net
PRECHIN
 普中
 
实验名称：DS1302时钟实验
接线说明：	
实验现象：下载程序后，数码管上显示电子时钟时分秒，格式为“XX-XX-XX”
注意事项：																				  
***************************************************************************************/
#include "public.h"
#include "smg.h"
#include "ds1302.h"


/*******************************************************************************
* 函 数 名       : main
* 函数功能		 : 主函数
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/
void main()
{	
	u8 time_buf[8];
	
	ds1302_init();//初始化DS1302

	while(1)
	{				
		ds1302_read_time();
		time_buf[0]=gsmg_code[gDS1302_TIME[2]/16];
		time_buf[1]=gsmg_code[gDS1302_TIME[2]&0x0f];
		time_buf[2]=0x40;
		time_buf[3]=gsmg_code[gDS1302_TIME[1]/16];
		time_buf[4]=gsmg_code[gDS1302_TIME[1]&0x0f];
		time_buf[5]=0x40;
		time_buf[6]=gsmg_code[gDS1302_TIME[0]/16];
		time_buf[7]=gsmg_code[gDS1302_TIME[0]&0x0f];
		smg_display(time_buf,1);
	}		
}

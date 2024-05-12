/**************************************************************************************
深圳市普中科技有限公司（PRECHIN 普中）
技术支持：www.prechin.net
PRECHIN
 普中
 
实验名称：DS18B20温度传感器实验
接线说明：	
实验现象：下载程序后，插上DS18B20温度传感器，数码管显示检测的温度值
注意事项：注意温度传感器的方向，在接口处我们已经用丝印画了一个凸起，
		  所以只需要将温度传感器对应插入即可																				  
***************************************************************************************/
#include "public.h"
#include "smg.h"
#include "ds18b20.h"


/*******************************************************************************
* 函 数 名       : main
* 函数功能		 : 主函数
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/
void main()
{	
	u8 i=0;
   	int temp_value;
	u8 temp_buf[5];

	ds18b20_init();//初始化DS18B20

	while(1)
	{				
		i++;
		if(i%50==0)//间隔一段时间读取温度值，间隔时间要大于温度传感器转换温度时间
			temp_value=ds18b20_read_temperture()*10;//保留温度值小数后一位
		if(temp_value<0)//负温度
		{
			temp_value=-temp_value;
			temp_buf[0]=0x40;//显示负号	
		}
		else
			temp_buf[0]=0x00;//不显示
		temp_buf[1]=gsmg_code[temp_value/1000];//百位
		temp_buf[2]=gsmg_code[temp_value%1000/100];//十位
		temp_buf[3]=gsmg_code[temp_value%1000%100/10]|0x80;//个位+小数点
		temp_buf[4]=gsmg_code[temp_value%1000%100%10];//小数点后一位
		smg_display(temp_buf,4);
	}		
}

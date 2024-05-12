/**************************************************************************************
深圳市普中科技有限公司（PRECHIN 普中）
技术支持：www.prechin.net
PRECHIN
 普中
 
实验名称：ADC模数转换实验--电位器电压采集
接线说明：	
实验现象：下载程序后，数码管上显示AD模块采集电位器的电压值
注意事项：																				  
***************************************************************************************/
#include "public.h"
#include "smg.h"
#include "xpt2046.h"


/*******************************************************************************
* 函 数 名       : main
* 函数功能		 : 主函数
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/
void main()
{	
	u16 adc_value=0;
	float adc_vol;//ADC电压值
	u8 adc_buf[3];

	while(1)
	{				
		adc_value=xpt2046_read_adc_value(0x94);//测量电位器
		adc_vol=5.0*adc_value/4096;//将读取的AD值转换为电压
		adc_value=adc_vol*10;//放大10倍，即保留小数点后一位
		adc_buf[0]=gsmg_code[adc_value/10]|0x80;
		adc_buf[1]=gsmg_code[adc_value%10];
	   	adc_buf[2]=0x3e;//显示单位V
		smg_display(adc_buf,6);		
	}		
}

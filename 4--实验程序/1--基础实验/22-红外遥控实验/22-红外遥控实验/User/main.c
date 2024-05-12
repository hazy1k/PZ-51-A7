/**************************************************************************************
深圳市普中科技有限公司（PRECHIN 普中）
技术支持：www.prechin.net
PRECHIN
 普中
 
实验名称：红外遥控实验
接线说明：	
实验现象：下载程序后，数码管上显示数码管上显示红外解码遥控器键值
注意事项：红外接收头凸起处要与PCB板接口凸起丝印处对应																				  
***************************************************************************************/
#include "public.h"
#include "smg.h"
#include "ired.h"


/*******************************************************************************
* 函 数 名       : main
* 函数功能		 : 主函数
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/
void main()
{	
	u8 ired_buf[3];

	ired_init();//红外初始化

	while(1)
	{				
		ired_buf[0]=gsmg_code[gired_data[2]/16];//将控制码高4位转换为数码管段码
		ired_buf[1]=gsmg_code[gired_data[2]%16];//将控制码低4位转换为数码管段码
		ired_buf[2]=0X76;//显示H的段码
		smg_display(ired_buf,6);	
	}		
}

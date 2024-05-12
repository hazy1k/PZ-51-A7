#include "lcd9648.h"
#include "font.h"


//ȫ�ֱ�������
xdata u8 gdata_buf[96][6];

/*******************************************************************************
* �� �� ��       : lcd9648_spi_write_byte
* ��������		 : LCD9648 SPI��������
* ��    ��       : dat������
* ��    ��    	 : ��
*******************************************************************************/
void lcd9648_spi_write_byte(u8 dat)
{
	u8 i=0;

   	for(i=0;i<8;i++)//ѭ��8�ν�һ���ֽڴ���			
   	{  
      	if((dat&0x80)!=0) 
			SDA = 1;
        else 
			SDA = 0;
      	dat<<= 1;//��д��λ��д��λ
	  	SCL = 0;
      	SCL = 1;//ʱ��������д������			
   	}
}

/*******************************************************************************
* �� �� ��       : lcd9648_write_cmd
* ��������		 : LCD9648д����
* ��    ��       : cmd������
* ��    ��    	 : ��
*******************************************************************************/
void lcd9648_write_cmd(u8 cmd)
{
	CS0 = 0;//ʹ��
	RS  = 0;//ѡ������
	lcd9648_spi_write_byte(cmd);//��������
	CS0 = 1;//ʧ��	
}

/*******************************************************************************
* �� �� ��       : lcd9648_write_dat
* ��������		 : LCD9648д����
* ��    ��       : dat������
* ��    ��    	 : ��
*******************************************************************************/
void lcd9648_write_dat(u8 dat)
{
	CS0 = 0;//ʹ��
	RS  = 1;//ѡ������
	lcd9648_spi_write_byte(dat);//��������
	CS0 = 1;//ʧ��	
}

/*******************************************************************************
* �� �� ��       : lcd9648_init
* ��������		 : LCD9648��ʼ��
* ��    ��       : ��
* ��    ��    	 : ��
*******************************************************************************/
void lcd9648_init(void)
{
	RST=1;  
	delay_ms(10);
	RST=0;
	delay_ms(10);
	RST=1;
	delay_ms(10);//��λ

    lcd9648_write_cmd(0xe2);		  //�����λ
	lcd9648_write_cmd(0xc8);		  //0xC8��ͨ����ѡ��ѡ����0xC0Ϊ��������
	lcd9648_write_cmd(0xa0);		  //0xA0�η���ѡ����������0xA1Ϊ������
	lcd9648_write_cmd(0x2f);
	lcd9648_write_cmd(0x26);
	lcd9648_write_cmd(0x81);		  //������Աȶ�
	lcd9648_write_cmd(0x10);
	lcd9648_write_cmd(0xaf);		  //������ʾ
	lcd9648_write_cmd(0x40);		  //���ù���һ������
}

/*******************************************************************************
* �� �� ��       : lcd9648_clear
* ��������		 : LCD9648����
* ��    ��       : ��
* ��    ��    	 : ��
*******************************************************************************/
void lcd9648_clear(void)
{
	u8 i,j;

	for(i=0;i<9;i++)//һ��9ҳ
	{
//		lcd9648_write_cmd(0x40);//���ù���һ������
		lcd9648_write_cmd(0xb0+i);//ҳ��ַ
		lcd9648_write_cmd(0x10);//�и��ֽڵ�ַ
		lcd9648_write_cmd(0x00);//�е��ֽڵ�ַ
		
		for(j = 0; j < LCD_WIDTH; j++)//ÿһ�е����ص�
		{
			lcd9648_write_dat(0x00);//����ʾ	
		}	
	}
	for(i=0;i<6;i++)  
	{    
		for(j=0;j<LCD_WIDTH;j++)
		{
			gdata_buf[j][i]=0;
		}
	}
	lcd_reflash_gram();//������ʾ	
}

void lcd_reflash_gram(void)
{
	u8 i,n;		    
	for(i=0;i<6;i++)  
	{  
		lcd9648_write_cmd(0xb0+i);    //����ҳ��ַ��0~5��
		lcd9648_write_cmd(0x00);      //������ʾλ�á��е͵�ַ
		lcd9648_write_cmd(0x10);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<LCD_WIDTH;n++)lcd9648_write_dat(gdata_buf[n][i]); 
	}
}

//����
//x,y:����
//sta:1����ʾ��0������ʾ
void lcd_draw_dot(u8 x,u8 y,u8 sta)
{
	u8 posy1,posy2;

	if(x>=LCD_WIDTH||y>=LCD_HEIGHT)return;//������Χ��
	posy1=y/8;//�ж��ǵڼ�ҳ
	posy2=y%8;//�жϵ�ҳ���ֽ����еڼ�λ���ֽڵ�λ���ϣ���λ������ʾ��

	if(sta)
		gdata_buf[x][posy1]|=1<<posy2;
	else
		gdata_buf[x][posy1]&=~(1<<posy2);	
}

//��ָ��λ����ʾһ���ַ�
//x,y:��ʼ����
//num:Ҫ��ʾ���ַ�:" "--->"~"
//size:�����С 12/16/24
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
void lcd_show_char(u8 x,u8 y,u8 num,u8 size,u8 mode)
{  							  
    u8 temp,t1,t;
	u16 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);		//�õ�����һ���ַ���Ӧ������ռ���ֽ���	
 	num=num-' ';//�õ�ƫ�ƺ��ֵ��ASCII�ֿ��Ǵӿո�ʼȡģ������-' '���Ƕ�Ӧ�ַ����ֿ⣩
	for(t=0;t<csize;t++)
	{   
		if(size==12)temp=ascii_1206[num][t]; 	 	//����1206����
		else if(size==16)temp=ascii_1608[num][t];	//����1608����
		else if(size==24)temp=ascii_2412[num][t];	//����2412����
		else return;								//û�е��ֿ�
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)lcd_draw_dot(x,y,1);
			else if(mode==0)lcd_draw_dot(x,y,0);
			temp<<=1;
			y++;
			if(y>=LCD_HEIGHT)return;		//��������
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=LCD_WIDTH)return;	//��������
				break;
			}
		}  	 
	}  	    	   	 	  
}   
//m^n����
//����ֵ:m^n�η�.
u32 lcd_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}			  

//��ʾ����,��λΪ0,������ʾ
//x,y:�������
//num:��ֵ(0~999999999);	 
//len:����(��Ҫ��ʾ��λ��)
//size:�����С
//mode:
//[7]:0,�����;1,���0.
//[6:1]:����
//[0]:0,�ǵ�����ʾ;1,������ʾ.
void lcd_show_num(u8 x,u8 y,u32 num,u8 len,u8 size,u8 mode)
{  
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/lcd_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)lcd_show_char(x+(size/2)*t,y,'0',size,mode&0X01);  
				else lcd_show_char(x+(size/2)*t,y,' ',size,mode&0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	lcd_show_char(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
	}
} 
//��ʾ�ַ���
//x,y:�������
//width,height:�����С  
//size:�����С
//*p:�ַ�����ʼ��ַ		  
void lcd_show_string(u8 x,u8 y,u8 width,u8 height,u8 size,u8 *p)
{         
	u8 x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//�˳�
        lcd_show_char(x,y,*p,size,0);
        x+=size/2;
        p++;
    }  
}

//��ʾ����
//x,y:�������
//*cn:�ַ�����ʼ��ַ
void lcd_show_fontHZ(u8 x, u8 y, u8 *cn)
{
	u8 i, j, wordNum;
	u16 color;
	u16 x0=x; 
	u16 y0=y; 
	while (*cn != '\0')
	{
		for (wordNum=0; wordNum<20; wordNum++)
		{	//wordNumɨ���ֿ������
			if ((CnChar16x16[wordNum].Index[0]==*cn)
			     &&(CnChar16x16[wordNum].Index[1]==*(cn+1)))
			{
				for(i=0; i<32; i++) 
				{	//MSK��λ��
					color=CnChar16x16[wordNum].Msk[i];
					for(j=0;j<8;j++) 
					{
						if((color&0x80)==0x80)
						{
							lcd_draw_dot(x,y,1);
						} 						
						else
						{
							lcd_draw_dot(x,y,0);
						} 
						color<<=1;
						x++;
						if((x-x0)==16)
						{
							x=x0;
							y++;
							if((y-y0)==16)
							{
								y=y0;
							}
						}
					}//for(j=0;j<8;j++)����
				}	
			}
			
		} //for (wordNum=0; wordNum<20; wordNum++)���� 	
		cn += 2;
		x += 16;
		x0=x;
	}
}



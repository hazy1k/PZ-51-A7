#include "time.h"

void time0_init(void)
{
	TMOD|=0X01;
	TH0=0xDC;
	TL0=0x00;//��ʱ10ms
	ET0=1;
	EA=1;
	TR0=1;				
}



#ifndef _time_H
#define _time_H

#include "public.h"


//��������
extern u8 gmsec;//ms������
extern u8 gsec;//�붨��
extern u8 gmin;//�ֶ���


//��������
void time0_init(void);
void time0_start(void);
void time0_stop(void);
#endif

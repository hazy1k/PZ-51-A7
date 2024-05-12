#ifndef _24c02_H
#define _24c02_H

#include "public.h"


void at24c02_write_one_byte(u8 addr,u8 dat);//AT24C02指定地址写数据
u8 at24c02_read_one_byte(u8 addr);//AT24C02指定地址读数据
#endif
#ifndef CMOS_H
#define CMOS_H

#define CMOS_READ_WRITE_PORT     0X71
#define CMOS_COMMAND_PORT        0X70


#define CMOS_HR_REGISTER        0X04
#define CMOS_MINUTES_REGISTER   0X02
#define CMOS_SECONDS_REGISTER   0X00
#define CMOS_STATUS_REGISTER_A  0X0A
#define CMOS_STATUS_REGISTER_B  0X0B
#define CMOS_STATUS_REGISTER_C  0X0C


#include "types.h"
#include "pit.h"
#include "write_to_serial.h"

void CMOS_INIT(void);
bool get_time_set_flag(void);




#endif
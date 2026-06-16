#ifndef PIT_H
#define PIT_H

#include "types.h"
#include "io.h"
#include "write_to_serial.h"
#include "helper_function.h"

#define CHANNEL_0_DATA_PORT                     0X40
#define CHANNEL_1_DATA_PORT                     0X41
#define CHANNEL_2_DATA_PORT                     0X42
#define MODE_AND_COMMAND_REGISTER               0X43

#define FREQ_DIVIDER_CHANNEL_0                  0x4A9 // 1193
#define RESULTANT_FREQ_ON_CHANNEL_0             1000.1525565801
#define RESULT_MS_PASSED_PER_TICK_FRACTION      999847746   // POINT IN MS (0.999847746)


#define CHANNEL_0_CLOCK_RATE_GENERATOR_CONFIG   0x34


void clock_update(void);
int get_hr(void);
int get_minutes(void);
int get_seconds(void);
int get_uptime(void);
void PIT_INIT(void);
void set_time(int hour , int minutes, int seconds);


#endif

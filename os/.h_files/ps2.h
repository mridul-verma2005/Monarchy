#ifndef PS2_H
#define PS2_H


#include "io.h"
#include "types.h"
#include "write_to_serial.h"



#define PS_DATA_PORT                0X60
#define PS_STATUS_REGISTER          0X64
#define PS_COMMAND_PORT             0X64


#define TEST_PS2_CONTROLLER         0XAA

#define TEST_FIRST_PS2_PORT         0XAB
#define DISABLE_FIRST_PS2_PORT      0XAD
#define ENABLE_FIRST_PS2_PORT       0XAE

#define TEST_SECOND_PS2_PORT        0XA9
#define DISABLE_SECOND_PS2_PORT     0XA7
#define ENABLE_SECOND_PS2_PORT      0XA8

#define READ_CONFIG_COMMAND         0X20
#define WRITE_CONFIG_COMMAND        0X60

#define READ_OUTPUT_PORT_COMMAND    0XD0 
#define WRITE_OUTPUT_PORT_COMMAND   0XD1

#define RESET_COMMAND               0XFF 
#define DISABLE_SCANNING_COMMAND    0XF5
#define IDENTIFY_COMMAND            0XF2
#define ENALBE_SCANNING_COMMAND     0XF4

#define WRITE_RESET_TO_PORT_2       0XD4


#define DISABLE_BOTH_PORT_CLOCK_AND_INTERRUPT       0X34
#define DISABLE_PORT_1_INTERRUPT_AND_PORT_2_BOTH    0X24
#define ENABLE_PORT_1_AND_PORT_2_DISABLED           0X25



void PS2_INIT(void);
void READ_FROM_PS2_BUFFER(void);
int READ_FROM_PS2_BUFFER_TIMER(uint16_t port);
void WRITE_TO_PS2_BUFFER(void);
void ENABLE_PS2_PORT1_INTERRUPT(void);




#endif
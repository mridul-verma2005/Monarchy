#ifndef PIC_H
#define PIC_H
#include "types.h"
#include "io.h"
#include "write_to_screen.h"
#include "write_to_serial.h"
#include "helper_function.h"
#define MASTER_PIC    0X20
#define SLAVE_PIC     0XA0
#define PIC_EOI       0X20

#define MASTER_PIC_COMMAND_PORT     MASTER_PIC
#define MASTER_PIC_DATA_PORT        (MASTER_PIC +1)
#define SLAVE_PIC_COMMAND_PORT      SLAVE_PIC
#define SLAVE_PIC_DATA_PORT         (SLAVE_PIC + 1)


#define ICW1_INIT                       0X10
#define ICW1_TO_INW4                    0X01
#define MASTER_PIC_OFFSET               0X20
#define SLAVE_PIC_OFFSET                0X28
#define MASTER_SLAVE_IRQ_PIN_CONNECTION 0X04
#define SLAVE_PIC_CAS_IDENTITY          0X02
#define USE_86_MODE                     0X01
#define USE_ALL_IRQ_PINS                0X00
#define DISABLE_ALL_IRQ_PINS            0XFF

#define PIC_READ_IRR                    0X0A
#define PIC_READ_ISR                    0X0B


void PIC_SEND_EOI(uint8_t vector);
void PIC_INIT(void);
void DISABLE_PIC(void);
void DISABLE_A_IRQ_LINE(uint8_t irq_line);
void ENABLE_A_IRQ_LINE(uint8_t irq_line);
uint16_t GET_PIC_ISR(void);
uint16_t GET_PIC_IRR(void);

#endif
#ifndef IDT_H
#define IDT_H

#include "../.h_files/types.h"
#include "../.h_files/write_to_screen.h"
#include "../.h_files/write_to_serial.h"
#include "../.h_files/pic.h"

#define MAX_DESCRIPTOR          256
#define TASK_FLAGS              0X8F
#define INTERRUPTS_FLAGS        0X8E




typedef struct {
    uint16_t isr_low;
    uint16_t kernel_cs;
    uint8_t reserved;
    uint8_t attributes;
    uint16_t isr_high;
} __attribute((packed)) IDT_ENTRY;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute((packed)) IDTR;




__attribute__ ((noreturn)) void exception_handler(int vector);
__attribute__ ((noreturn)) void interupt_handler(int irq);
void IDT_SET_DESCRIPTOR(uint8_t vector , void* isr_address  , uint8_t flags);
void IDT_INIT();

#endif



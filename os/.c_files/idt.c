#include "../.h_files/idt.h"
IDT_ENTRY IDT_ENTRY_TABLE[MAX_DESCRIPTOR];
IDTR idtr;
extern void* isr_stub_table[];


__attribute__ ((noreturn)) void exception_handler(
    
){
    write_error_to_screen("[ERROR]: SOMETHING HAS GONE SERIOUSLY WRONG , HALTING");
    log_error("SOMETHING HAS GONE SERIOUSLY WRONG, HALTING",COM1);
    __asm__ volatile ("cli; hlt");
    while(1);
}

void IDT_SET_DESCRIPTOR(uint8_t vector , void* isr_address  , uint8_t flags){
    IDT_ENTRY* descriptor = &IDT_ENTRY_TABLE[vector];
    descriptor->isr_low = (uint32_t)isr_address & 0xFFFF;
    descriptor->isr_high = ((uint32_t)isr_address >> 16) & 0xFFFFF;
    descriptor->kernel_cs = 0x08;
    descriptor->reserved = 0;
    descriptor->attributes = flags;
}

void IDT_INIT(){
    idtr.base = (uint32_t)IDT_ENTRY_TABLE;
    idtr.limit = (sizeof(IDT_ENTRY) * MAX_DESCRIPTOR) -1;

    for(int i = 0 ; i < 32 ; i++){
        IDT_SET_DESCRIPTOR(i , isr_stub_table[i], TASK_FLAGS);
    }

    __asm__ volatile ("lidt %0" : : "m"(idtr));
    __asm__ volatile("sti");
    log_info("IDT is initialized",COM1);

}
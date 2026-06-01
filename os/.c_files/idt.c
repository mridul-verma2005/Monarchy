#include "../.h_files/idt.h"
IDT_ENTRY IDT_ENTRY_TABLE[MAX_DESCRIPTOR];
IDTR idtr;
extern void* isr_stub_table[];


char* int_to_string(int number){
    int digit;
    static char value[3] = " ";
    value[2] = '\0';
    if(number == 0){
        value[0] = '0';
        value[1] = '\0';
        return value;
    }
        
    else{
        int i = 1;
        while(number > 0 && i >= 0){
            digit = number % 10;
            value[i] = '0' + digit;
            number /= 10;
            i--;
        }
    }
    if(value[0] == ' '){
        value[0] = value[1];
        value[1] = '\0';
    }
    
    return value;
}



__attribute__ ((noreturn)) void exception_handler(int vector){
    char* vector_string = int_to_string(vector);
    clear_screen();
    write_error_to_screen("[ERROR]: Exception occurred, HALTING",12);
    write_error_to_screen("ERROR VECTOR",14);
    write_error_to_screen(vector_string,15);
    log_error("Exception occurred, HALTING",COM1);
    __asm__ volatile ("cli; hlt");
    while(1);
}


__attribute__ ((noreturn)) void interupt_handler(int vector){
    clear_screen();
    write_error_to_screen("[ERROR]: Hardware Interrupt Occured", 12);
    write_error_to_screen("ERROR VECTOR",13);
    log_error("Hardware Interrupt Occured",COM1);
    PIC_SEND_EOI(vector);
    __asm__ volatile ("cli; hlt");
    while(1);
}


void IDT_SET_DESCRIPTOR(uint8_t vector , void* isr_address  , uint8_t flags){
    IDT_ENTRY* descriptor = &IDT_ENTRY_TABLE[vector];
    descriptor->isr_low = (uint32_t)isr_address & 0xFFFF;
    descriptor->isr_high = ((uint32_t)isr_address >> 16) & 0xFFFF;
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

    for(int i = 32 ; i < 48 ; i++){
        IDT_SET_DESCRIPTOR(i , isr_stub_table[i], INTERRUPTS_FLAGS);
    }


    __asm__ volatile ("lidt %0" : : "m"(idtr));
    __asm__ volatile("sti");
    log_info("IDT is initialized",COM1);

}
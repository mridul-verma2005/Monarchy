#include "../.h_files/idt.h"
IDT_ENTRY IDT_ENTRY_TABLE[MAX_DESCRIPTOR];
IDTR idtr;
extern void* isr_stub_table[];





void exception_handler(int vector){
   
    clear_screen(BLACK_COL,WHITE_COL);

    char* vector_string = int_to_string(vector);
    int size_vector_string = strlen_d(vector_string);

    char err_msg_screen[] =  "[ERROR]: Exception occurred halting , vector no :";
    char err_msg_log[] = "Exception occurred halting , vector no :";

    int size_err_msg_screen = strlen_d(err_msg_screen);
    int size_err_msg_log = strlen_d(err_msg_log);
    
    int result_log_size = size_err_msg_log + size_vector_string + 2;
    int result_screen_size = size_err_msg_screen + size_vector_string + 2;

    char log_result[result_log_size];
    char screen_result[result_screen_size];

    concaternate(err_msg_screen, vector_string , screen_result);
    concaternate(err_msg_log, vector_string, log_result);

    write_error_to_screen(screen_result,13);
    log_info(log_result , COM1);
    
    
}




void interupt_handler(int vector){
    int irq = vector - 32;
    if(irq == 0){
        clock_update();
    }
    else if(irq == 1){
        keyboard_handler();
    }
    else if(irq == 8){
        log_info("entered the irq 8 handler",COM1);
        set_time_from_cmos();
    }
    
    else 
    {
        char* irq_string = int_to_string(irq);
        int size_irq_string = strlen_d(irq_string);
   
        char err_msg_screen[] =  "[ERROR]: Interrupt occurred halting , irq no :";
        char err_msg_log[] = "Interrupt occurred halting , irq no :";

        int size_err_msg_screen = strlen_d(err_msg_screen);
        int size_err_msg_log = strlen_d(err_msg_log);
    
        int result_log_size = size_err_msg_log + size_irq_string + 2;
        int result_screen_size = size_err_msg_screen + size_irq_string + 2;

        char log_result[result_log_size];
        char screen_result[result_screen_size];

        concaternate(err_msg_screen, irq_string , screen_result);
        concaternate(err_msg_log, irq_string, log_result);
   
        write_error_to_screen(screen_result,13);
        // log_info(log_result , COM1);
    
    }
    PIC_SEND_EOI(irq);
    
}


// void keyboard_handler(int vector){
//     int irq = vector - 32;
//     char* irq_string = int_to_string(irq);
//     int size_irq_string = strlen_d(irq_string);
   
//     char err_msg_screen[] =  "[ERROR]: Interrupt occurred halting , irq no :";
//     char err_msg_log[] = "Interrupt occurred halting , irq no :";

//     int size_err_msg_screen = strlen_d(err_msg_screen);
//     int size_err_msg_log = strlen_d(err_msg_log);
    
//     int result_log_size = size_err_msg_log + size_irq_string + 2;
//     int result_screen_size = size_err_msg_screen + size_irq_string + 2;

//     char log_result[result_log_size];
//     char screen_result[result_screen_size];

//     concaternate(err_msg_screen, irq_string , screen_result);
//     concaternate(err_msg_log, irq_string, log_result);
   
//     write_error_to_screen(screen_result,13);
//     log_info(log_result , COM1);
    
//     PIC_SEND_EOI(irq);
// }


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
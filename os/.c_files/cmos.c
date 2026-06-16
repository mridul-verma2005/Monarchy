#include "../.h_files/cmos.h"

static bool time_set = false;

uint8_t bcd_to_binary(uint8_t bcd_value){
    uint8_t binary_value;
    binary_value = ( (bcd_value & 0xF0) >> 1) + ( (bcd_value & 0xF0) >> 3) + (bcd_value & 0xf);
    return binary_value;
}


uint8_t get_data(uint8_t which_register){
    outb(CMOS_COMMAND_PORT , (1 << 7 | which_register));  
    int data = inb(CMOS_READ_WRITE_PORT);
    return data;
}

void send_data(uint8_t which_register , uint8_t data){
    uint8_t current_bitmap = get_data(which_register);
    uint8_t new_bitmap = current_bitmap | data;
    outb(CMOS_COMMAND_PORT , (1 << 7 | which_register));
    outb(CMOS_READ_WRITE_PORT,new_bitmap);

}




bool get_time_set_flag(void){
    return time_set;
}

void set_time_from_cmos(void){
    if(time_set == true){
        return;
    }

    else{
        int update_timer_interrupt = get_data(CMOS_STATUS_REGISTER_C) &0X10;
        if(update_timer_interrupt == 0x10){
            int seconds = bcd_to_binary(get_data(CMOS_SECONDS_REGISTER));
            int minutes = bcd_to_binary(get_data(CMOS_MINUTES_REGISTER));
            int hrs = bcd_to_binary(get_data(CMOS_HR_REGISTER));
            set_time(hrs , minutes , seconds);
            log_info("time is set from the CMOS to the user_time",COM1);
            time_set = true;
            outb(CMOS_COMMAND_PORT , (0 << 7)); 
        }
        else{
            return;
        }
        
    }
}





void CMOS_INIT(void){
    __asm__ volatile("cli");
    int bcd_or_binary = get_data(CMOS_STATUS_REGISTER_B) & 0X04;
    int twelve_or_24 = get_data(CMOS_STATUS_REGISTER_B) & 0X02;
    send_data(CMOS_STATUS_REGISTER_B,1<<4);
    log_info("update_ended interrupt is now active",COM1);
    __asm__ volatile("sti");
    outb(CMOS_COMMAND_PORT , (0 << 7)); 
    if(bcd_or_binary == 0x04){
        log_info("using binary mode", COM1);
    }
    else{
        log_info("using bcd mode",COM1);
    }
    if(twelve_or_24 == 0X02){
        log_info("using 24 hrs format",COM1);
    }
    else{
        log_info("using a 12 hrs format",COM1);
    }
    log_info("CMOS is initialised",COM1);
    
}

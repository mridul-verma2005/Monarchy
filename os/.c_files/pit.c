#include "../.h_files/pit.h"

static int SYSTEM_CLOCK_MS_WHOLE = 0;  // WILL HOLD THE TIME IN MS (THE WHOLE PART)
static int SYSTEM_CLOCK_MS_FRACTION = 0;  // WILL HOLD THE TIME IN MS (FRACTION PART)
static int SYSTEM_CLOCK_SECONDS = 0;  // WILL HOLD THE TIME IN SECONDS(sys uptime)
static int USER_CLOCK_SECONDS = 0;    // user local time

void PIT_channel_config(uint8_t config_byte,uint16_t freq_divider){
    outb(MODE_AND_COMMAND_REGISTER, config_byte);
    outb(CHANNEL_0_DATA_PORT,(freq_divider & 0X00FF));  // LOW BYTES 
    outb(CHANNEL_0_DATA_PORT,(freq_divider >> 8) & 0X00FF);  // HIGH BYTES
}

void clock_update(void){
    
    SYSTEM_CLOCK_MS_FRACTION += RESULT_MS_PASSED_PER_TICK_FRACTION;
    if(SYSTEM_CLOCK_MS_FRACTION >= 1000000000){
        SYSTEM_CLOCK_MS_WHOLE += 1;
        SYSTEM_CLOCK_MS_FRACTION -= 1000000000;
    }
    if(SYSTEM_CLOCK_MS_WHOLE >= 1000){
        SYSTEM_CLOCK_SECONDS += 1;
        USER_CLOCK_SECONDS +=1;
        SYSTEM_CLOCK_MS_WHOLE -= 1000;
    }
    if(SYSTEM_CLOCK_SECONDS >= 86400){
        USER_CLOCK_SECONDS -= 86400;   // resets after a 24 hr , day will be implemented next (later on)
    }
    log_info(int_to_string(SYSTEM_CLOCK_MS_WHOLE),COM1);

}
int get_hr(void){
    int hr = SYSTEM_CLOCK_SECONDS / 3600;
    return hr;
}

int get_minutes(void){
    int min = (SYSTEM_CLOCK_SECONDS % 3600) / 60;
    return min;
}

int get_seconds(void){
    int sec = SYSTEM_CLOCK_SECONDS % 60;
    return sec;
}


void set_time(int hour , int minutes , int seconds){  // using a 24 hr format
    int total_elapsed_second = (hour * 60 * 60) + (minutes * 60) + seconds;
    USER_CLOCK_SECONDS = 0;
    USER_CLOCK_SECONDS = total_elapsed_second;
}

int get_uptime(void){
    int min = (SYSTEM_CLOCK_SECONDS % 3600) / 60;
    return min;
}


void PIT_INIT(){
    PIT_channel_config(CHANNEL_0_CLOCK_RATE_GENERATOR_CONFIG,FREQ_DIVIDER_CHANNEL_0);
    log_info("PIT initialised using channel 0 as a clock",COM1);
}
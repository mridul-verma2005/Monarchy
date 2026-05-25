#define DIVISOR 12
#define COM1 0X3F8
#define FREE_TO_SEND 0X20
#include "serial_port_config.h"
#include "write_to_screen.h"
#include "write_to_serial.h"



int serial_port_check(){
    if(serial_port_config(COM1,DIVISOR) == FREE_TO_SEND){
        write_to_log("serial port 1 is ready to use",0,COM1);
        return 0;

    }
    else{
        write_to_screen("cant use serial port 1, printing to screen , aborting loading kernel");
        return 1;
        

    }
}
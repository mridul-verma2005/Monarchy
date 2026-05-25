#include "../.h_files/write_to_screen.h"
#include "../.h_files/move_cursor.h"
#include "../.h_files/serial_port_config.h"
#include "../.h_files/write_to_serial.h"

#define DIVISOR 12
#define COM1 0X3F8
#define FREE_TO_SEND 0X20

int main(){
    if(serial_port_config(COM1,DIVISOR) == FREE_TO_SEND){
        write_to_screen("serial port 1 is ready to use");
        write_to_log("serial port 1 is ready to use",0,COM1);

    }
    else{
        write_to_screen("cant use serial port 1");

    }
    write_to_log("Kernel Loaded Sucessfully", 0,COM1);
    write_to_screen("Welcome to Monarchy");

    return 0;
    
}
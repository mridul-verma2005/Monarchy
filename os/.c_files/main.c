#include "../.h_files/write_to_screen.h"
#include "../.h_files/move_cursor.h"
#include "../.h_files/serial_port_config.h"
#include "../.h_files/write_to_serial.h"
#define COM1 0X3F8


int main(){
    write_to_log("Kernel Loaded Sucessfully", 0,COM1);
    write_to_screen("Welcome to Monarchy");
    return 0;
    
}
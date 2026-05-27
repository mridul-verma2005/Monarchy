#include "../.h_files/write_to_screen.h"
#include "../.h_files/move_cursor.h"
#include "../.h_files/serial_port.h"
#include "../.h_files/write_to_serial.h"
#include "../.h_files/gdt.h"



int main(){
    gdt_start();
    log_info("Kernel Loaded Sucessfully",COM1);
    write_to_screen("Welcome to Monarchy");
    return 0;
}
#include "../.h_files/write_to_screen.h"
#include "../.h_files/move_cursor.h"
#include "../.h_files/serial_port.h"
#include "../.h_files/write_to_serial.h"
#include "../.h_files/gdt.h"
#include "../.h_files/idt.h"



int main(){
    gdt_start();
    IDT_INIT();
    log_info("Kernel Loaded Sucessfully",COM1);
    write_to_screen("Welcome to Monarchy");

    return 0;
}
#include "../.h_files/write_to_screen.h"
#include "../.h_files/move_cursor.h"
#include "../.h_files/serial_port.h"
#include "../.h_files/write_to_serial.h"
#include "../.h_files/gdt.h"
#include "../.h_files/idt.h"
#include "../.h_files/pic.h"



int main(){
    gdt_start();
    PIC_INIT();
    // DISABLE_A_IRQ_LINE(0);
    // DISABLE_A_IRQ_LINE(12);  
    IDT_INIT();
    log_info("Kernel Loaded Sucessfully",COM1);
    write_to_screen("Welcome to Monarchy");
    // int a = 2/0;

    return 0;
}
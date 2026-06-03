#include "../.h_files/write_to_screen.h"
#include "../.h_files/move_cursor.h"
#include "../.h_files/serial_port.h"
#include "../.h_files/write_to_serial.h"
#include "../.h_files/gdt.h"
#include "../.h_files/idt.h"
#include "../.h_files/pic.h"
#include "../.h_files/ps2.h"



int main(){
    gdt_start();
    PIC_INIT();
    DISABLE_A_IRQ_LINE(0);      // to disalbe the timer interupts which is not needed for now 
    IDT_INIT();
    PS2_INIT();
    log_info("Kernel Loaded Sucessfully",COM1);
    write_to_screen("Welcome to Monarchy");

    return 0;
}
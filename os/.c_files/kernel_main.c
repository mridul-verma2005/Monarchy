#include "../.h_files/write_to_screen.h"
#include "../.h_files/move_cursor.h"
#include "../.h_files/serial_port.h"
#include "../.h_files/write_to_serial.h"
#include "../.h_files/gdt.h"
#include "../.h_files/idt.h"
#include "../.h_files/pic.h"
#include "../.h_files/ps2.h"
#include "../.h_files/keyboard.h"
#include "../.h_files/shell.h"



int kernel_main(){
    gdt_start();
    PIC_INIT();
    DISABLE_A_IRQ_LINE(0);      // to disalbe the timer interupts which is not needed for now 
    IDT_INIT();
    PS2_INIT();
    KEYBOARD_INIT();
    ENABLE_PS2_PORT1_INTERRUPT();
    SHELL_INIT();
    SCREEN_INIT();
    write_to_screen("type help to get to know the commands ;)",BLACK_COL,WHITE_COL);
    next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,true);
    log_info("Kernel Loaded Sucessfully",COM1);

    return 0;
}
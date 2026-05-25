#include "../.h_files/io.h"



#define SERIAL_DATA_PORT(base)              (base)
#define SERIAL_FIFO_COMMAND_PORT(base)      (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)      (base + 3)
#define SERIAL_MODEM_PORT(base)             (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)       (base + 5)


#define SERIAL_LINE_ENABLE_DLAB             0X80





void serial_line_config_baud_rate(unsigned short com , unsigned short divisor){
    outb(SERIAL_LINE_COMMAND_PORT(com),SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com),((divisor>>8) & 0x00ff));  // higher bytes
    outb(SERIAL_DATA_PORT(com),(divisor & 0x00ff));       // lower bytes

}

void serial_line_config_data(unsigned short com){
    outb (SERIAL_LINE_COMMAND_PORT(com),0x03);
}


void serial_fifo_line_config(unsigned short com){
    outb(SERIAL_FIFO_COMMAND_PORT(com),0xc7);
}

void serial_modem_line_config(unsigned short com){
    outb(SERIAL_MODEM_PORT(com), 0x03);
}

int is_tramit_buffer_empty(unsigned short com){
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}


int serial_port_config(unsigned short com , unsigned short divisor){
    serial_line_config_baud_rate(com , divisor);
    serial_line_config_data(com);
    serial_fifo_line_config(com);
    serial_modem_line_config(com);
    return is_tramit_buffer_empty(com);
}

void write_data(unsigned short com , char data){
    while(is_tramit_buffer_empty(com) == 0);
    outb(SERIAL_DATA_PORT(com),data);
}
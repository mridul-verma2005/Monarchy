#ifndef SERIAL_PORT_CONFIG_H
#define SERIAL_PORT_CONFIG_H

void serial_line_config_baud_rate(unsigned short com , unsigned short divisor);
void serial_line_config_data(unsigned short com);
void serial_fifo_line_config(unsigned short com);
void serial_modem_line_config(unsigned short com);
void is_tramit_buffer_empty(unsigned short com);
int serial_port_config(unsigned short com , unsigned short divisor);
void write_data(unsigned short com , char data);

#endif
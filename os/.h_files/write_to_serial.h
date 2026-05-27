#ifndef WRITE_TO_SERIAL_H
#define WRITE_TO_SERIAL_H
#define COM1 0X3F8
void write_to_serial(char* msg, unsigned short com);
void write_to_log(char* msg , int type , unsigned short com);
void log_error(char* msg, unsigned short com);
void log_info(char* msg, unsigned short com);

#endif
#include "../.h_files/serial_port.h"

void write_to_serial(char* msg, unsigned short com){
    int i = 0;
    while(msg[i] != '\0'){
        write_data(com , msg[i]);
        i++;
    }
}

void write_to_log(char* msg , int type , unsigned short com){
    if(type == 0){
        write_to_serial("[INFO]: " , com);
    }
    if(type == 1){
        write_to_serial("[ERROR]: ", com);
    }
    write_to_serial(msg , com);
    write_data(com, '\r');
    write_data(com, '\n');
    
}

void log_error(char* msg, unsigned short com){
    write_to_log(msg , 1 , com);
}


void log_info(char* msg, unsigned short com){
    write_to_log(msg , 0 , com);
}
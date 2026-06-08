#include "../.h_files/shell.h"

static char command_buffer[256];
static int i = 0;

void command_buffer_init(void){
    for(int start = 0 ; i < 256 ; i++){
        command_buffer[start] = '\0';
    }
}
void command_buffer_stack_push(char keychar){
    command_buffer[i] = keychar;
    i++;
}
char command_buffer_stack_pop(void){
    char result = command_buffer[i];
    i--;
}

char* command_retrival(void){
    int end = i;
    char command[60];
    while(i != 0){
        command[i] = command_buffer_stack_pop();
        i--;
    }

}

void command_proccessing(char* command){
    
}



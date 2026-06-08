#include "../.h_files/shell.h"
#define COMMAND_BUFFER_LIMIT_INDEX       255
static char command_buffer[COMMAND_BUFFER_LIMIT_INDEX + 1];
static char main_command[40];
static char rest[256];
static int command_buffer_counter = 0;
static char hello_command[] = "Hello user i am Monarchy a 32 bit custom OS made by Mridul Verma";
// static char about_command[] = "Currenty there are 4 commands \n Hello just greets you and tell about some stuff related to the OS and the Creator. \n echo prints the same thing you typed. \n clear just clear the screen like in linux \n About tell about the types of command the shell currenly allows.";

void command_buffer_clean(char *buffer){
    for(int start = 0 ; start < 256 ; start++){
        buffer[start] = '\0';
    }
    command_buffer_counter = 0;
}
void command_buffer_stack_push(char keychar){
    if(command_buffer_counter == COMMAND_BUFFER_LIMIT_INDEX){
        next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1);
        write_to_screen("Command is too long cleaning the buffer , please type a correct command",BLACK_COL,WHITE_COL);
        command_buffer_clean(command_buffer);
        next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1);
    }
    command_buffer[command_buffer_counter] = keychar;
    command_buffer_counter++;
}
char command_buffer_stack_pop(void){
    char result = command_buffer[command_buffer_counter];
    command_buffer_counter--;
    return result;
}

char command_buffer_stack_top(void){
    char result;
    if(command_buffer_counter == 0){
        result = command_buffer[command_buffer_counter];
    }
    else {
        result = command_buffer[command_buffer_counter-1];
    }
    return result;
   
}


void command_parcer(char* command){
    log_info("entered command parcer",COM1);
    int i = 0;
    int j = 0;
    while(command[i] != ' '){
        if(command[i] == '\0'){
          break;  
        }
        main_command[i] = command[i];
        i++;
    }
    while(command[i] != '\0'){
        rest[j] = command[i+1];
        i++;
        j++;
    }
    if(strcmp_d(main_command, "hello") == true){
        write_to_screen(hello_command,BLACK_COL,WHITE_COL);
        next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1);
    }
    else if(strcmp_d(main_command, "clear") == true){
        clear_screen(BLACK_COL,WHITE_COL);

    }
    else if(strcmp_d(main_command, "echo") == true){
        write_to_screen(rest,BLACK_COL,WHITE_COL);
    }
    else if(strcmp_d(main_command, "about") == true){
        char testing[] = "testing";
        int testing_len = strlen_d(testing);
        int i = 0;
        while(i < testing_len){
            write_char(testing[i],BLACK_COL,WHITE_COL);
            i++;
        }
    }
    else{
        write_to_screen("Unknown Command",BLACK_COL,WHITE_COL);
        next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1);
    }
    command_buffer_clean(command);
    command_buffer_clean(main_command);
    command_buffer_clean(rest);
     log_info("leaving command parcer",COM1);
    
   
}


void command_retrival(void){
    if(command_buffer_stack_top() == '\0'){
        return;
    }
    log_info("entering command parcer",COM1);
    command_parcer(command_buffer);

}




void SHELL_INIT(void){
    command_buffer_clean(command_buffer);
    command_buffer_clean(main_command);
    command_buffer_clean(rest);

}


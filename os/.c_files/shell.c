#include "../.h_files/shell.h"

#define COMMAND_BUFFER_LIMIT_INDEX            255
#define COMMAND_LIMIT_INDEX                   16  
static char command_buffer[COMMAND_BUFFER_LIMIT_INDEX + 1];
static char main_command_buffer[COMMAND_BUFFER_LIMIT_INDEX + 1];  
static char command_retriver_array[COMMAND_LIMIT_INDEX + 1][COMMAND_BUFFER_LIMIT_INDEX + 1];


static int current_command_counter = 0;  // for the command_retrival array
static int command_buffer_counter = 0;   // for the command_buffer

static char hello_command[] = "Hello user i am Monarchy a 32 bit custom OS.";
static char help_command[] = "Currenty there are 4 commands :- \n1. Hello just greets you and tell about some stuff related to the OS and the Creator. \n2. echo prints the same thing you typed. \n3. clear just clear the screen like in linux \n4. help tell about the types of command the shell currenly allows.";
static int up_pressed_count = 0;

void up_pressed_count_increase(){
    up_pressed_count++;
}

void up_pressed_count_decrease(){
    up_pressed_count--;
}

void make_space_command_retriver(){
    int current_buffer = 0;
    while(current_buffer != COMMAND_LIMIT_INDEX - 1 ){
        for(int i = 0 ; i < COMMAND_BUFFER_LIMIT_INDEX + 1 ; i++){
            command_retriver_array[current_buffer][i] = command_retriver_array[current_buffer +1 ][i];
        }
        current_buffer++;
    }
    current_buffer++;
    for(int i = 0 ; i < COMMAND_BUFFER_LIMIT_INDEX +1 ; i++){
        command_retriver_array[current_buffer][i] = '\0';
    }
    current_command_counter--;
}

void command_saver(){
    log_info("entered the command saver",COM1);
    for(int i = 0 ; i < COMMAND_BUFFER_LIMIT_INDEX + 1 ; i++){
        if(current_command_counter == 15){
            make_space_command_retriver();
        }
        command_retriver_array[current_command_counter][i] = main_command_buffer[i];
        
    }
    current_command_counter++;
    log_info("counter increased",COM1);
}

void command_buffer_clean(char *buffer, int buffer_size){

    for(int start = 0 ; start < buffer_size ; start++){

        buffer[start] = '\0';
    }
}



void command_buffer_stack_push(char keychar){

    if(command_buffer_counter == COMMAND_BUFFER_LIMIT_INDEX){

        next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,false);
        write_to_screen("Command is too long cleaning the buffer , please type a correct command",BLACK_COL,WHITE_COL);
        command_buffer_clean(command_buffer, COMMAND_BUFFER_LIMIT_INDEX +1);

        command_buffer_counter = 0;

        next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,true);
    }

    command_buffer[command_buffer_counter] = keychar;
    command_buffer_counter++;
    command_buffer[command_buffer_counter] = '\0';
}



char command_buffer_stack_pop(void){

    char result;

    if(command_buffer_counter == 0){

        result = command_buffer[command_buffer_counter];
        command_buffer[command_buffer_counter] = '\0';
        
    }

    else {

        result = command_buffer[command_buffer_counter-1];
        command_buffer[command_buffer_counter-1] = '\0';
        command_buffer_counter--;

    }

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


void command_parcer(){

    // log_info("entered command parcer",COM1);

    int space = 0;

    for(int start = 0 ; start < COMMAND_BUFFER_LIMIT_INDEX +1 ; start++){

        if(command_buffer[start] == ' '  || command_buffer[start] == '\0' ){

            if(command_buffer[start] == ' ' ){

                space = start;
            }
           
            break;
        }

        else{

            main_command_buffer[start] = command_buffer[start];

        }

    }


    if(strcmp_d(main_command_buffer, "hello") == true){

        next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,false);

        write_to_screen(hello_command,BLACK_COL,WHITE_COL);

        next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,true);
    }
    else if(strcmp_d(main_command_buffer, "clear") == true){

        clear_screen(BLACK_COL,WHITE_COL);

    }
    else if(strcmp_d(main_command_buffer, "echo") == true){

        next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,false);
        if(space == 0){
            write_to_screen(" ",BLACK_COL,WHITE_COL);
        }
        else{
            write_to_screen(command_buffer+ space +1,BLACK_COL,WHITE_COL);
        }
        

        next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,true);
    }
    else if(strcmp_d(main_command_buffer, "help") == true){

        next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,false);

        int index = 0;
        int help_command_len = strlen_d(help_command);

        for(int i  = 0 ; i < 5 ; i++){

            while(help_command[index] != '\n' && index < help_command_len){

                write_char(help_command[index],BLACK_COL,WHITE_COL);
                index++;
            }

            index++;

            if(i < 4){

                next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,false);

            }
        }

        next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,true);
    }
    else{

        next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,false);

        write_to_screen("Unknown command try help to know the commands",BLACK_COL,WHITE_COL);

        next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,true);
    }
    command_saver();
    command_buffer_clean(command_buffer,COMMAND_BUFFER_LIMIT_INDEX + 1);
    command_buffer_clean(main_command_buffer,COMMAND_BUFFER_LIMIT_INDEX + 1);

    command_buffer_counter = 0;

    // log_info("leaving command parcer",COM1);
    
   
}


void command_retrival(void){

    if(command_buffer_stack_top() == '\0'){
        next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,true);
        return;

    }

    log_info("entering command parcer",COM1);
    command_parcer();

}

void prev_command_show(){
    // log_info("entered prev command",COM1);
    if(current_command_counter == 0){
        clear_current_line(BLACK_COL,BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL);       
        write_to_screen("no commands to retrive",BLACK_COL,WHITE_COL);
    }
    else{
        while(command_buffer_stack_top() != '\0'){
            command_buffer_stack_pop();
        }
        int i = 0;
        int which_command_shown = 0;
        if(current_command_counter - up_pressed_count < 0){
            up_pressed_count = 0;
        }
        which_command_shown = current_command_counter - up_pressed_count;
        while(command_retriver_array[which_command_shown][i] != '\0'){
            command_buffer_stack_push(command_retriver_array[which_command_shown][i]);
            write_char(command_retriver_array[which_command_shown][i],BLACK_COL,WHITE_COL);
            i++;
        }

    }
}


void SHELL_INIT(void){

    command_buffer_clean(command_buffer,COMMAND_BUFFER_LIMIT_INDEX + 1);
    command_buffer_clean(main_command_buffer,COMMAND_BUFFER_LIMIT_INDEX + 1);
    for(int i = 0 ; i < COMMAND_LIMIT_INDEX + 1; i++){
        command_buffer_clean(command_retriver_array[i],COMMAND_BUFFER_LIMIT_INDEX + 1);
    }

    command_buffer_counter = 0;
    current_command_counter = 0;

}


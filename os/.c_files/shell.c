#include "../.h_files/shell.h"

#define COMMAND_BUFFER_LIMIT_INDEX            255
#define COMMAND_LIMIT_INDEX                   15 
static char command_buffer[COMMAND_BUFFER_LIMIT_INDEX + 1];
static char main_command_buffer[COMMAND_BUFFER_LIMIT_INDEX + 1];  
static char command_retriver_array[COMMAND_LIMIT_INDEX + 1][COMMAND_BUFFER_LIMIT_INDEX + 1];

static int total_argument_in_help = 6;
static int total_commands_in_help = 5;
static int current_command_counter = 0;  // for the command_retrival array
static int command_buffer_counter = 0;   // for the command_buffer
static int up_pressed_count = 0;

static char hello_command[] = "Hello user i am Monarchy a 32 bit custom OS.";
static char help_command[] =
    "Currently there are 4 commands:\n"
    "1. hello just greets you and tells about some stuff related "
    "to the OS and the creator.\n"
    "2. echo prints the same thing you typed.\n"
    "3. clear just clears the screen like in Linux.\n"
    "4. help tells about the types of commands the shell "
    "currently allows.\n"
    "5. the cbuff will clean the command history , the shell can currently hold upto 16 previous command and the least recently used is removed."
    ;


void up_pressed_count_increase(){
    up_pressed_count++;
}

void up_pressed_count_to_zero(){
    up_pressed_count = 0;
}

int current_up_pressed_value(){
    return up_pressed_count;
}

int space_checker(int start){
    if(start == 0){
        return 1;
    }
    int i = 0;
    while((command_buffer + start + 1)[i] != '\0'){
        if((command_buffer + start + 1)[i] != ' '){
            return 0;
        }
        i++;
    }
    return 1;
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
    if(command_buffer[0] == '\0' || command_buffer[0] == ' '){
        return;
    }
    // log_info("entered the command saver",COM1);
    for(int i = 0 ; i < COMMAND_BUFFER_LIMIT_INDEX + 1 ; i++){
        if(current_command_counter == 16){
            make_space_command_retriver();
        }
        command_retriver_array[current_command_counter][i] = command_buffer[i];
        
    }
    current_command_counter++;
    // log_info("counter increased",COM1);
}

void command_buffer_clean(char *buffer, int buffer_size){
    for(int start = 0 ; start < buffer_size ; start++){
        buffer[start] = '\0';
    }
}

void clear_command_history(){
    for(int i = 0 ; i < COMMAND_LIMIT_INDEX + 1; i++){
        command_buffer_clean(command_retriver_array[i],COMMAND_BUFFER_LIMIT_INDEX + 1);
    }
    current_command_counter = 0;
    next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,false);
    write_to_screen("command history is cleared",BLACK_COL,WHITE_COL);
    next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,true);

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

void incorrect_flags(char* msg){
    next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,false);
    write_to_screen(msg,BLACK_COL,WHITE_COL);
    next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,true);
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
        if((space_checker(space) ==0)){
            incorrect_flags("hey there is no known flag with hello, try help (no flag)");
        }
        else{
             next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,false);
            write_to_screen(hello_command,BLACK_COL,WHITE_COL);
            next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,true);
        }
       
    }

    else if(strcmp_d(main_command_buffer, "clear") == true){
        if(space_checker(space) == 1){
            clear_screen(BLACK_COL,WHITE_COL);
        }
        else if(strcmp_d(command_buffer + space +1 , "-b")){
            clear_command_history();
        }
        else if(strcmp_d(command_buffer + space +1 , "-b") == false){
            incorrect_flags("hey this is not a known flag with clear, try help (no flag)");
        }
       
        
    }

    else if(strcmp_d(main_command_buffer, "echo") == true){
        next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,false);
        if(space_checker(space) == 1){
            write_to_screen(" ",BLACK_COL,WHITE_COL);       // echo issued fixed , as there wasnt any space used so the space value was still 0 and it was using that 
        }
        else{
            write_to_screen(command_buffer+ space +1,BLACK_COL,WHITE_COL);
        }
        
        next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,true);
    }

    else if(strcmp_d(main_command_buffer, "help") == true){
        if((space_checker(space) ==0)){
            incorrect_flags("hey there is no known flag with help, try help (no flag)");
        }
        else{
            next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,false);
            int index = 0;
            int help_command_len = strlen_d(help_command);
            for(int i  = 0 ; i < total_argument_in_help ; i++){
                while(help_command[index] != '\n' && index < help_command_len){
                    write_char(help_command[index],BLACK_COL,WHITE_COL);
                    index++;
                }
                index++;
                if(i < total_commands_in_help){
                    next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,false);
                }
            }
            next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,true);
            
        }
        
    }


    else if (strcmp_d(main_command_buffer , "time")){
        if((space_checker(space) ==0)){
            incorrect_flags("hey there is no known flag with time, try help (no flag)");
        }
        else{
            next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,false);
            show_time(BLACK_COL,WHITE_COL);
            next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,true);

        }
        
    }

    else if(strcmp_d(main_command_buffer , "uptime")){
        if((space_checker(space) ==0)){
            incorrect_flags("hey there is no known flag with uptime, try help (no flag)");
        }
        else{
            next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,false);
            show_uptime(BLACK_COL,WHITE_COL);
            next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,true);

        }
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

    
   
}


void command_retrival(void){

    if(command_buffer_stack_top() == '\0'){
        next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,true);
        return;

    }

    
    command_parcer();

}

void prev_command_show(){
   
    if(current_command_counter == 0){
        clear_current_line(BLACK_COL,BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL);      // prints noting now 
        up_pressed_count = 0; 
        return;
    }
    else{
        while(command_buffer_stack_top() != '\0'){
            command_buffer_stack_pop();
        }
        int i = 0;
        int which_command_shown = 0;
        if(current_command_counter -1 - up_pressed_count < 0){
            up_pressed_count = 0;
        }
        which_command_shown = current_command_counter -1 - up_pressed_count;
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
    up_pressed_count = 0;
    command_buffer_counter = 0;
    current_command_counter = 0;

}


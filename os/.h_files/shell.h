#ifndef SHELL_H
#define SHELL_H




#include "write_to_screen.h"
#include "write_to_serial.h"



void SHELL_INIT();
void command_buffer_stack_push(char keychar);
char command_buffer_stack_pop(void);
char command_buffer_stack_top(void);
void command_retrival(void);
void prev_command_show();
void up_pressed_count_increase(void);
void up_pressed_count_to_zero(void);
int current_up_pressed_value(void);
#endif

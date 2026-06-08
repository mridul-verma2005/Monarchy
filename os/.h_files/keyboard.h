#ifndef KEYBOARD_HANDLER_H
#define KEYBOARD_HANDLER_H

#include "ps2.h"
#include "helper_function.h"
#include "types.h"
#include "write_to_screen.h"





#define SCANCODE_SET                        0XF0
#define GET_SCANCODE                        0X00
#define CURRENT_TYPEMATIC_RATE_AND_DELAY    0X24
#define SET_TYPEMATIC_RATE_AND_DELAY        0XF3
#define SET_SCANCODE_2                      0X02



#define RELEASE_SCANCODE_2                  0XF0
#define EXTENDED_SCANCODE_2                 0XE0
#define L_SHIFT                             0X12
#define R_SHIFT                             0X59
#define L_CTRL                              0X14
#define R_CTRL                              0X14 // BUT WITH EXTENEDED FIRST
#define CAPS                                0X58
#define ENTER                               0X5A
#define BACKSPACE                           0X66
#define TAB                                 0x0D
#define UP_KEY                              0X75   // USING EXTENDED
#define DOWN_KEY                            0X72   // USING EXTENDED


void keyboard_handler(void);
void get_scancode(void);
void KEYBOARD_INIT(void);







#endif
#ifndef WRITE_TO_SCREEN_H
#define WRITE_TO_SCREEN_H

#define BLACK_COL               0X0
#define BLUE_COL                (BLACK_COL + 1)
#define GREEN_COL               (BLACK_COL + 2)
#define CYAN_COL                (BLACK_COL + 3)
#define RED_COL                 (BLACK_COL + 4)
#define MEGENTA_COL             (BLACK_COL + 5)
#define BROWN_COL               (BLACK_COL + 6)
#define LIGHT_GREY_COL          (BLACK_COL + 7)
#define DARK_GREY_COL           (BLACK_COL + 8)
#define LIGHT_BLUE_COL          (BLACK_COL + 9)
#define LIGHT_GREEN_COL         (BLACK_COL + 10)
#define LIGHT_CYAN_COL          (BLACK_COL + 11)
#define LIGHT_RED_COL           (BLACK_COL + 12)
#define LIGHT_MAGENTA_COL       (BLACK_COL + 13)
#define LIGHT_BROWN_COL         (BLACK_COL + 14)
#define WHITE_COL               (BLACK_COL + 15)


#define MIDDLE_ROW_CURSOR_START         959


#include "helper_function.h"
#include "types.h"
#include "move_cursor.h"


void write_to_screen( char* msg_pointer ,uint8_t bg , uint8_t fg);
void write_error_to_screen(char * err_msg, int row);
void clear_screen(uint8_t bg,uint8_t fg );
void write_char(char ascii_code, uint8_t bg , uint8_t fg);
void next_line(uint8_t osname_bg , uint8_t osname_fg, uint8_t seperator_bg , uint8_t seperator_fg, int start_row, bool write_prompt);
void back_space(uint8_t bg , uint8_t fg);
void SCREEN_INIT(void);

#endif
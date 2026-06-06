#include "../.h_files/write_to_screen.h"
#define FRAMEBUFFER_START 0X000B8000
#define MAX_ROW_COUNT     24

static int row = 0;
static int position = 0;
// static int char_row = 0;
 char* OS_NAME = "Monarchy@> ";

void set_position_initial(){
    int os_name_size = strlen_d(OS_NAME);
    position += os_name_size;
}

void clear_screen(){
    char* fb_start = (char*) FRAMEBUFFER_START;
    int i = 0;
    while(i < 2000){
        fb_start[2*i] = ' ';
        fb_start[2*i + 1] = ((BLACK_COL & 0xf) << 4) | (BLACK_COL & 0xf);
        i++;
    }
    

}

void clear_line(int row){
    char* fb_start = (char*) FRAMEBUFFER_START;
    int row_start = row * 160;
    int i = 0;
    while(i < 80){
        fb_start[2*i + row_start] = ' ';
        fb_start[2*i + 1 + row_start] = ((BLACK_COL & 0xf) << 4) | (BLACK_COL & 0xf);
        i++;
    }
}

void write_to_screen(char* msg_pointer){
    char* fb_start;
    fb_start = (char*) (FRAMEBUFFER_START + ((row)*160));
    row++;
    if(row > 24){
        row--;
    }
    int i = 0;
    while(msg_pointer[i]!= '\0'){
        fb_start[2*i] = msg_pointer[i];
        fb_start[2*i + 1] = ((BLACK_COL & 0xf) << 4) | (WHITE_COL & 0xf);  // BG AND THEN FG
        i++;
    }
    fb_move_cursor(i + 80*(row -1));
    
}

void write_char(char ascii_code, uint8_t fg , uint8_t bg){
    char* fb_start;
    fb_start = (char*) (FRAMEBUFFER_START + (position * 2));
    fb_start[0] = ascii_code;
    fb_start[1] = (((bg & 0xf) << 4) | (fg & 0xf));
    position++;
    fb_move_cursor(position);
}

void clear_from_top(){
    int row_count_start = 0;
    char* fb_start = (char*)FRAMEBUFFER_START;
    while(row_count_start < MAX_ROW_COUNT){
        clear_line(row_count_start);
        int i = ((row_count_start + 2) * 160) - 1;
        while(i >= ((row_count_start +1)* 160)){
            fb_start[i - 160] = fb_start[i];
            fb_start[i - 160 - 1] = fb_start[i - 1];
            i--;
        }
        row_count_start++;
    }
    clear_line(row_count_start);
    position -=80;
    
}

void next_line(void){
    int used_up = position % 80;
    int remaining = 80 -used_up;
    position += remaining;
    if(position >= 2000){
        clear_from_top();
    }
    write_to_screen(OS_NAME);
    set_position_initial();
    fb_move_cursor(position);
}

void back_space(void){
    position--;
    char* fb_start;
    fb_start = (char*) (FRAMEBUFFER_START + (position * 2));
    fb_start[0] = ' ';
    fb_start[1] = (((BLACK_COL & 0xf) << 4) | (WHITE_COL & 0xf));
    fb_move_cursor(position);
}



void write_error_to_screen(char * err_msg, int row){
    char* fb_start = (char*) (FRAMEBUFFER_START + (160 *row));  // ON THE 13TH LINE, THE MIDDLE ROW
    int err_msg_len = strlen_d(err_msg);
    int space = 80 - err_msg_len;
    int side_gap = space/2;
    int i = 0;
    int j = 0;
    while(i < side_gap){
        fb_start[2*i] = ' ';
        fb_start[2*i + 1] = ((BLACK_COL & 0xf) << 4) | (BLACK_COL & 0xf);
        i++;
    }
    i--;
    while(err_msg[j] != '\0'){
        fb_start[2*(i+j)] = err_msg[j];
        fb_start[2*(i+j) + 1] = ((RED_COL & 0xf) << 4) | (WHITE_COL & 0xf);
        j++;
    }
    fb_move_cursor((row *80 -1) + i + j);

}






void SCREEN_INIT(void){
    set_position_initial();
    write_to_screen(OS_NAME);
}
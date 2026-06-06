#include "../.h_files/write_to_screen.h"
#define FRAMEBUFFER_START 0X000B8000

static int row = -1;
static int position = 0;
static int char_row = 0;


void write_to_screen(char* msg_pointer){
    char* fb_start;
    fb_start = (char*) (FRAMEBUFFER_START + ((row+1)*160));
    row++;
    int i = 0;
    while(msg_pointer[i]!= '\0'){
        fb_start[2*i] = msg_pointer[i];
        fb_start[2*i + 1] = ((BLACK_COL & 0xf) << 4) | (WHITE_COL & 0xf);  // BG AND THEN FG
        i++;
    }
    fb_move_cursor(i + row * 80);
    
}

void write_char(char ascii_code, uint8_t fg , uint8_t bg){
    char* fb_start;
    fb_start = (char*) (FRAMEBUFFER_START + (position * 2) + (char_row * 160));
    fb_start[0] = ascii_code;
    fb_start[1] = (((bg & 0xf) << 4) | (fg & 0xf));
    position++;
    char_row = (position/80) + 1;
}

void next_line(void){
    char_row++;
}

void back_space(void){
    position--;
    write_char(' ',BLACK_COL,BLACK_COL);
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
#include "../.h_files/move_cursor.h"

#define FRAMEBUFFER_START 0X000B8000

int rows = -1;

void write_to_screen(char* msg_pointer){
    char* fb_start;
    fb_start = (char*) (FRAMEBUFFER_START + ((rows+1)*160));
    rows++;
    int i = 0;
    while(msg_pointer[i]!= '\0'){
        fb_start[2*i] = msg_pointer[i];
        fb_start[2*i + 1] = ((0 & 0xf) << 4) | (15 & 0xf);
        i++;
    }
    fb_move_cursor(i + rows * 80);
    
}
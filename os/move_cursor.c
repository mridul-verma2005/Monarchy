#define FB_COMMAND_PORT 0X3D4
#define FB_DATA_PORT 0X3D5

#define LOWER_BYTE_SEND 15
#define HIGHER_BYTE_SEND 14

#include "io.h"
#include "move_cursor.h"

void fb_move_cursor(unsigned short pos){
    outb(FB_COMMAND_PORT , LOWER_BYTE_SEND);
    outb(FB_DATA_PORT,(pos & 0x00ff));
    outb(FB_COMMAND_PORT , HIGHER_BYTE_SEND);
    outb(FB_DATA_PORT ,((pos & 0xff00)>> 8));

}
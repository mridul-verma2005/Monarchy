#include "fb.h"
#include "move_cursor.h"

void sample(int a , int b , int c){
    int result = a + b + c;
    write_to_fb(0,result + '0', 15 , 1);
    fb_move_cursor(3);
    // return result;
    
}
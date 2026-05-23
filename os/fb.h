#ifndef FB_H
#define FB_H

#define FB_START 0X000B8000
void write_to_fb(unsigned int i , char c , unsigned char fg , unsigned char bg);

#endif
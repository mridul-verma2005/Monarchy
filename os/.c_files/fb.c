#define FB_START 0X000B8000


void write_to_fb(unsigned int i , char c , unsigned char fg , unsigned char bg){
    char* fb = (char*)FB_START;
    fb[i] = c;
    fb[i+1] = ((bg & 0xf) << 4) | (fg & 0xf);
}
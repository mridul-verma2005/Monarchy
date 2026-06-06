extern char bss_start[];
extern char bss_end[];


void bss_cleaning(void){
    char* start = bss_start;
    char* end = bss_end;
    while(start < end){
        *start = 0;
        start++;
    }
}
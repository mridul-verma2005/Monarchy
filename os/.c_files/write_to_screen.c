#include "../.h_files/write_to_screen.h"
#define FRAMEBUFFER_START 0X000B8000
#define FIRST_FRAMBUFFER_ROW_START 80
#define MAX_ROW_COUNT     24

// static int row = 1;
static int position = FIRST_FRAMBUFFER_ROW_START;    
static char* OS_NAME = "Monarchy";
static char* seperator = "$: ";
static char* OS_TERMINAL_NAME = "Monarchy Shell v.0.0.1";

static char* logo[] =  {"            _            ",
                        "          _\\ /_          ",
                        "          >_X_<          ",
                        "   .---._  /_\\  _.---.   ",
                       " /`.---._`{/ \\}`_.---.`\\ ",
                       "| /   ___`{\\_/}`___   \\ |",
                       "\\ \\.\"`*  `\"{_}\"`  *`\"./ /",
                       " \\ \\  )\\  _\\ /_  /(  / / ",
                       "  \\ *<()( >_X_< )()>* /  ",
                       "   |._)/._./_\\._.\\(_.|   ",
                       "   |() () () () () ()|   ",
                       "   <<o>><<o>><o>><<o>>   ",
                       "  `\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"`  "};

static char* description[] = {"  host user","  ---------","  OS: Monarchy 0.0.1", "  Uptime: ", "  Shell: Monarchy Shell 0.0.1", "  Resolution: 20*80, VGA text buffer"};

// static char* TEXT_EDITOR = "Text Editor v.0.0.1";




void clear_screen(uint8_t bg ,uint8_t fg){

    char* fb_start = (char*) FRAMEBUFFER_START;
    int i = 0;

    while(i < 2000){
        fb_start[2*i] = ' ';
        fb_start[2*i + 1] = ((bg & 0xf) << 4) | (fg & 0xf);
        i++;
    }
    position = FIRST_FRAMBUFFER_ROW_START;
    SCREEN_INIT();
    
}

void clear_current_line(uint8_t bg,uint8_t osname_bg,uint8_t osname_fg,uint8_t seperator_bg,uint8_t seperator_fg){
    clear_line(position/80,bg);
    position -= position %80;
    write_to_screen(OS_NAME,osname_bg,osname_fg);
    write_to_screen(seperator,seperator_bg,seperator_fg);
}

void clear_line(int row , uint8_t bg){

    char* fb_start = (char*) FRAMEBUFFER_START;
    int row_start = row * 160;
    int i = 0;

    while(i < 80){
        fb_start[2*i + row_start] = ' ';
        fb_start[2*i + 1 + row_start] = ((bg & 0xf) << 4) | (bg & 0xf);
        i++;
    }

}


void scroll_from_top(int start_row){

    int row_count_start = start_row;
    char* fb_start = (char*)FRAMEBUFFER_START;

    while(row_count_start < MAX_ROW_COUNT){
        int i = ((row_count_start + 1) * 80) ;

        while(i <= ((row_count_start +2)* 80 - 1)){
            fb_start[2*i - 160] = fb_start[2*i];
            fb_start[2*i - 160 + 1] = fb_start[2*i + 1];
            i++;

        }

        row_count_start++;
    }
    position -= 80;
    
}


void terminal_name_set(uint8_t osname_bg , uint8_t osname_fg){
    char* fb_start = (char*) (FRAMEBUFFER_START); 
    int terminal_name_len = strlen_d(OS_TERMINAL_NAME);
    int space = 80 - terminal_name_len;
    int right_gap = space/2;
    int right_gap_len = 0;
    int os_name_len = 0;


    while(right_gap_len < right_gap){
        fb_start[2*right_gap_len] = ' ';
        fb_start[2*right_gap_len + 1] = ((osname_bg & 0xf) << 4) | (osname_fg & 0xf);
        right_gap_len++;
    }

    right_gap_len--;
    while(OS_TERMINAL_NAME[os_name_len] != '\0'){
        fb_start[2*(right_gap_len+os_name_len)] = OS_TERMINAL_NAME[os_name_len];
        fb_start[2*(right_gap_len+os_name_len) + 1] = ((osname_bg & 0xf) << 4) | (osname_fg & 0xf);
        os_name_len++;
    }

    int left_gap = right_gap_len + os_name_len;
     while(left_gap < 80){
        fb_start[2*left_gap] = ' ';
        fb_start[2*left_gap + 1] = ((osname_bg & 0xf) << 4) | (osname_fg & 0xf);
        left_gap++;
    }

}



void write_char(char ascii_code, uint8_t bg , uint8_t fg){
    if(position >= 2000){
        scroll_from_top(1);
        clear_line(MAX_ROW_COUNT,bg);
    }
    char* fb_start;
    fb_start = (char*) (FRAMEBUFFER_START + (position * 2));
    fb_start[0] = ascii_code;
    fb_start[1] = (((bg & 0xf) << 4) | (fg & 0xf));
    position++;
    fb_move_cursor(position);
}

void write_to_screen(char* msg_pointer, uint8_t bg , uint8_t fg){

    int msg_len = strlen_d(msg_pointer);

    for(int i = 0 ; i < msg_len ; i++){
        write_char(msg_pointer[i],bg,fg);
    }
    
}

void show_time(uint8_t bg , uint8_t fg){
    write_to_screen(int_to_string(get_hr()), bg, fg);
    write_char(':', bg, fg);
    write_to_screen(int_to_string(get_minutes()), bg, fg);
    write_char(':', bg, fg);
    write_to_screen(int_to_string(get_seconds()), bg, fg);
}

void show_uptime(uint8_t bg , uint8_t fg){
    write_to_screen(int_to_string(get_uptime_days()), bg, fg);
    write_to_screen(" days, ", bg, fg);
    write_to_screen(int_to_string(get_uptime_hrs()), bg, fg);
    write_to_screen(" hours, ", bg, fg);
    write_to_screen(int_to_string(get_uptime_min()), bg, fg);
    write_to_screen(" minutes, ", bg, fg);
    write_to_screen(int_to_string(get_uptime_sec()), bg, fg);
    write_to_screen(" seconds", bg, fg);

}

// void get_uptime_string(){
//     char* days = int_to_string(get_uptime_days());
//     char* hrs = int_to_string(get_uptime_hrs());
//     char* min = int_to_string(get_uptime_min());
//     char* sec = int_to_string(get_uptime_sec());
//     int total_size = strlen_d(days)  + strlen_d(" days,")+ strlen_d(hrs) +strlen_d(" hours,") + strlen_d(min) +strlen_d(" minutes,")+ strlen_d(sec) + strlen_d(" seconds") + 1;
//     char uptime_arra

// }






void next_line(uint8_t osname_bg , uint8_t osname_fg, uint8_t seperator_bg , uint8_t seperator_fg , int start_row, bool write_prompt){
    int used_up = position % 80;
    int remaining = 80 -used_up;
    position += remaining;
    if(position >= 2000){
        scroll_from_top(start_row);
        clear_line(MAX_ROW_COUNT,osname_bg);
    }
    if(write_prompt == true){
        write_to_screen(OS_NAME,osname_bg,osname_fg);
        write_to_screen(seperator,seperator_bg,seperator_fg);
    }
        fb_move_cursor(position);
    
   
}

void back_space(uint8_t bg , uint8_t fg){
    int current_position_on_the_line = (position%80) + 1;
    int total_label_size = strlen_d(OS_NAME) + strlen_d(seperator);
    if((current_position_on_the_line - total_label_size) <= 1){
        return;
    }
    position--;
    char* fb_start;
    fb_start = (char*) (FRAMEBUFFER_START + (position * 2));
    fb_start[0] = ' ';
    fb_start[1] = (((bg & 0xf) << 4) | (fg & 0xf));
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

void show_logo(uint8_t bg , uint8_t fg){
    char* fb_start = (char*) FRAMEBUFFER_START;
    int i = 0;

    while(i < 2000){
        fb_start[2*i] = ' ';
        fb_start[2*i + 1] = ((bg & 0xf) << 4) | (fg & 0xf);
        i++;
    }
    position = FIRST_FRAMBUFFER_ROW_START;
    next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,false);
    terminal_name_set(DARK_GREY_COL,WHITE_COL);
    int logo_rows = 13;
    int info_row = 6;
    for(int i = 0 ; i < logo_rows;i++){
        write_to_screen(logo[i],bg , fg);
        if(i < info_row){
            write_to_screen(description[i],bg,fg);
            if(strcmp_d(description[i],"  Uptime: ")){  
                show_uptime(bg , fg);
            }
            
        }
        next_line(BLACK_COL,WHITE_COL,BLACK_COL,BLUE_COL,1,false);
    }
}







void SCREEN_INIT(void){
    terminal_name_set(DARK_GREY_COL,WHITE_COL);
    // set_position_initial();
    write_to_screen(OS_NAME,BLACK_COL,WHITE_COL);
    write_to_screen(seperator,BLACK_COL,BLUE_COL);
}
#include "../.h_files/keyboard.h"

static bool extended_flag = false;
// static bool ctrl_flag = false;
static bool shift_flag = false;
static bool caps_flag = false;
static bool release_flag = false;



const char sc2_to_ascii[256] = {
    [0X1C] = 'a',[0X32] = 'b',[0X21] = 'c',[0X23] = 'd',[0X24] = 'e',
    [0X2B] = 'f',[0X34] = 'g',[0X33] = 'h',[0X43] = 'i',[0X3B] = 'j',
    [0X42] = 'k',[0X4B] = 'l',[0X3A] = 'm',[0X31] = 'n',[0X44] = 'o',
    [0X4D] = 'p',[0X15] = 'q',[0X2D] = 'r',[0X1B] = 's',[0X2C] = 't',
    [0X3C] = 'u',[0X2A] = 'v',[0X1D] = 'w',[0X22] = 'x',[0X35] = 'y',
    [0X1A] = 'z', [0X29] = ' ',


    [0X45] = '0',[0X16] = '1',[0X1E] = '2',[0X26] = '3',[0X25] = '4',
    [0X2E] = '5',[0X36] = '6',[0X3D] = '7',[0X3E] = '8',[0X46] = '9',

   
};


const char sc2_to_shift_caps_ascii[256] = {
    [0X1C] = 'A',[0X32] = 'B',[0X21] = 'C',[0X23] = 'D',[0X24] = 'E',
    [0X2B] = 'F',[0X34] = 'G',[0X33] = 'H',[0X43] = 'I',[0X3B] = 'J',
    [0X42] = 'K',[0X4B] = 'L',[0X3A] = 'M',[0X31] = 'N',[0X44] = 'O',
    [0X4D] = 'P',[0X15] = 'Q',[0X2D] = 'R',[0X1B] = 'S',[0X2C] = 'T',
    [0X3C] = 'U',[0X2A] = 'V',[0X1D] = 'W',[0X22] = 'X',[0X35] = 'Y',
    [0X1A] = 'Z', [0X29] = ' ',
    
    
    [0X45] = ')',[0X16] = '!',[0X1E] = '@',[0X26] = '#',[0X25] = '$',
    [0X2E] = '%',[0X36] = '^',[0X3D] = '&',[0X3E] = '*',[0X46] = '(',

};



void get_scancode(void){
    WRITE_TO_PS2_BUFFER();
    outb(PS_DATA_PORT,SCANCODE_SET);
    WRITE_TO_PS2_BUFFER();
    outb(PS_DATA_PORT,GET_SCANCODE);
    READ_FROM_PS2_BUFFER();
    uint8_t reply = inb(PS_DATA_PORT);
    if(reply == 0XFA){
        READ_FROM_PS2_BUFFER();
        uint8_t scan_code = inb(PS_DATA_PORT);
        char scan_code_info[] = "using scancode set:";
        char* set_no = int_to_string(scan_code);
        int resut_size = strlen_d(scan_code_info) + strlen_d(set_no) + 2;
        char result[resut_size];
        concaternate(scan_code_info , set_no , result);
        log_info(result,COM1);
    }
    else if(reply == 0XFE){
        log_error("cant get scancode in one try resend error",COM1);
    }


}

void set_scancode(void){
    WRITE_TO_PS2_BUFFER();
    outb(PS_DATA_PORT,SCANCODE_SET);
    WRITE_TO_PS2_BUFFER();
    outb(PS_DATA_PORT,GET_SCANCODE);
    READ_FROM_PS2_BUFFER();
    uint8_t reply = inb(PS_DATA_PORT);
    if(reply == 0xFA){
        WRITE_TO_PS2_BUFFER();
        outb(PS_DATA_PORT,SET_SCANCODE_2);
        log_info("scancode set 2 is being set on the keyboard",COM1);
        get_scancode();
    }
    else if (reply == 0XFE){
        log_error("cant set the scancode in one try resend error",COM1);
    }
}

void set_repeat_rate_and_delay(void){
    WRITE_TO_PS2_BUFFER();
    outb(PS_DATA_PORT,SET_TYPEMATIC_RATE_AND_DELAY);
    READ_FROM_PS2_BUFFER();
    uint8_t reply = inb(PS_DATA_PORT);
    if(reply == 0XFA){
        WRITE_TO_PS2_BUFFER();
        outb(PS_DATA_PORT,CURRENT_TYPEMATIC_RATE_AND_DELAY);
        READ_FROM_PS2_BUFFER();
        inb(PS_DATA_PORT);
        log_info("typematic and repeat rate is set",COM1);
    }
    else if(reply == 0XFE){
        log_error("cant set typematic and repeat rate , resend errror",COM1);
    }
}


void keyboard_handler(void){
    uint8_t scancode = inb(PS_DATA_PORT);
    log_info("keybboard",COM1);
    if(release_flag == true){
        if(scancode == L_SHIFT || scancode == R_SHIFT){
            shift_flag = false;
        }
        release_flag = false;
        return;
    }

    if(scancode == RELEASE_SCANCODE_2){
        release_flag = true;
        return;
       
    }
    else if(scancode == EXTENDED_SCANCODE_2){
        extended_flag = true;
        return;
    }
    else if(scancode == L_SHIFT || scancode == R_SHIFT){
        shift_flag = true;
        return;
    }

    else if(scancode == CAPS){
        if(caps_flag == 0){
            caps_flag = 1;
        }
        else if(caps_flag == 1){
            caps_flag = 0;
        }
        return;
    }

    else if(scancode == ENTER){
        next_line();
        return;
    }
    else if(scancode == L_CTRL || scancode == R_CTRL){
        return;
    }
    else if(scancode == BACKSPACE){
        back_space();
        return;
    }

    else{
        char ascii;
        if(shift_flag == true){
            ascii = sc2_to_shift_caps_ascii[scancode];
            write_char(ascii,WHITE_COL,BLACK_COL);
        }
        else if(caps_flag == true){
            
            ascii = sc2_to_ascii[scancode];
            if((ascii  <= 57) && (ascii >= 48)){
                write_char(ascii,WHITE_COL,BLACK_COL);
            }
            else{
                ascii = sc2_to_shift_caps_ascii[scancode];
                write_char(ascii,WHITE_COL,BLACK_COL);
                
            }
        }
        else{
            ascii = sc2_to_ascii[scancode];
            write_char(ascii,WHITE_COL,BLACK_COL);
        }
    }
}




void KEYBOARD_INIT(void){
    get_scancode();
    set_scancode();
    set_repeat_rate_and_delay();
}


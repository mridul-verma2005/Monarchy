#include "../.h_files/ps2.h"

void READ_FROM_PS2_BUFFER(void){
    while((inb(PS_STATUS_REGISTER) & 0X01) == 0);
}


int READ_FROM_PS2_BUFFER_TIMER(uint16_t port){
    int timer = 10000000;
    while(timer > 0){
        if((inb(PS_STATUS_REGISTER) & 0X01) != 0){
            return inb(port);
        }
        else{
            timer--;
        }
        
    }
    return 0;
}


void WRITE_TO_PS2_BUFFER(void){
    while((inb(PS_STATUS_REGISTER) & 0X02) != 0);
}



void DISABLE_PS2_PORTS(void){
    WRITE_TO_PS2_BUFFER();
    outb(PS_COMMAND_PORT,DISABLE_FIRST_PS2_PORT);
    WRITE_TO_PS2_BUFFER();
    outb(PS_COMMAND_PORT,DISABLE_SECOND_PS2_PORT);
}

void FLUSH_OUTPUT_BUFFER(void){
    while((inb(PS_STATUS_REGISTER) & 0X01) != 0){  
        inb(PS_DATA_PORT);
    }
    
}

void SET_CONFIG_BYTES(uint8_t new_config){
    WRITE_TO_PS2_BUFFER();
    outb(PS_COMMAND_PORT, WRITE_CONFIG_COMMAND);
    WRITE_TO_PS2_BUFFER();
    outb(PS_DATA_PORT,new_config);
}

int PS2_CONTROLLER_TEST(void){
    WRITE_TO_PS2_BUFFER();
    outb(PS_COMMAND_PORT,TEST_PS2_CONTROLLER);
    READ_FROM_PS2_BUFFER();
    if(inb(PS_DATA_PORT) == 0x55){
        // log_info("ps2 controller self test passed", COM1);
        SET_CONFIG_BYTES(DISABLE_BOTH_PORT_CLOCK_AND_INTERRUPT);;
        return 0;
    }
    else{
        // log_error("ps2 controller self test failed",COM1);
        SET_CONFIG_BYTES(DISABLE_BOTH_PORT_CLOCK_AND_INTERRUPT);
        return 1;
    }
    
}

void DETERMINING_NO_OF_PS2_PORTS(void){
    WRITE_TO_PS2_BUFFER();
    outb(PS_COMMAND_PORT,ENABLE_SECOND_PS2_PORT);
    WRITE_TO_PS2_BUFFER();
    outb(PS_COMMAND_PORT,READ_CONFIG_COMMAND);
    READ_FROM_PS2_BUFFER();
    if((inb(PS_DATA_PORT) & 0X20)  == 0){
        // log_info("second ps2 port detected",COM1);
    }
    else{
        log_info("there is not second ps2 port",COM1);
    }
    SET_CONFIG_BYTES(DISABLE_BOTH_PORT_CLOCK_AND_INTERRUPT);
}

void PS2_PORT_TEST(void){
    WRITE_TO_PS2_BUFFER();
    outb(PS_COMMAND_PORT,TEST_FIRST_PS2_PORT);
    READ_FROM_PS2_BUFFER();
    if(inb(PS_DATA_PORT) == 0){
        // log_info("first ps2 port self test passed",COM1);
    }
    else{
        log_info("first ps2 port self test failed",COM1);
    }

    WRITE_TO_PS2_BUFFER();
    outb(PS_COMMAND_PORT,TEST_SECOND_PS2_PORT);
    READ_FROM_PS2_BUFFER();
    if(inb(PS_DATA_PORT) == 0){
        // log_info("second ps2 port self test passed",COM1);
    }
    else{
        log_info("second ps2 port self test failed",COM1);
    }
}

void ENABLE_PS2_PORTS(void){
    SET_CONFIG_BYTES(DISABLE_PORT_1_INTERRUPT_AND_PORT_2_BOTH);           // port 2 is disabled and port 1 clock is only active not the interrupt
    WRITE_TO_PS2_BUFFER();
    outb(PS_COMMAND_PORT,ENABLE_FIRST_PS2_PORT);
    log_info("port 1 clock is enabled but the interupts is disalbed in the config byte",COM1);
    // WRITE_TO_PS2_BUFFER();
    // outb(PS_COMMAND_PORT,ENABLE_SECOND_PS2_PORT);
}

void RESET_PS2_DEVICES(void){
    // log_info("before the keyboard is reset",COM1);
    WRITE_TO_PS2_BUFFER();
    outb(PS_DATA_PORT,RESET_COMMAND);
    // log_info("after the keyboard is reset",COM1);
    READ_FROM_PS2_BUFFER();
    if((inb(PS_DATA_PORT) == 0xFA)){
        // log_info("device at port 1 has acknowledged the self test command",COM1);    
        READ_FROM_PS2_BUFFER();
        if(inb(PS_DATA_PORT) == 0xAA){
            // log_info("device at port 1 has passed the self test",COM1);
        }
        
    }
    else{
        log_error("device at port 1 has failed the test",COM1);
        outb(PS_COMMAND_PORT,DISABLE_FIRST_PS2_PORT);
    }


}

void DETECTING_PS2_DEVICES(void){
    WRITE_TO_PS2_BUFFER();
    outb(PS_DATA_PORT,DISABLE_SCANNING_COMMAND);
    READ_FROM_PS2_BUFFER();
    if((inb(PS_DATA_PORT) == 0xFA)){
        // log_info("device at port 1 has acknowledged the disable scanning command",COM1);
        WRITE_TO_PS2_BUFFER();
        outb(PS_DATA_PORT,IDENTIFY_COMMAND);
        READ_FROM_PS2_BUFFER();
        if(inb(PS_DATA_PORT) == 0xFA){
            // log_info("device at port 1 has acknowledged the identify command",COM1);
            READ_FROM_PS2_BUFFER();
            uint8_t fisrt_byte = inb(PS_DATA_PORT);
            uint16_t second_byte = 0x00;
            second_byte = READ_FROM_PS2_BUFFER_TIMER(PS_DATA_PORT);
            if((fisrt_byte == 0XAB) && ((second_byte == 0X83)||(second_byte == 0XC1))){
                log_info("using a MF2 keyboard",COM1);
            }
            else{
                log_info("not using a MF2 keyboard",COM1);
            }
            WRITE_TO_PS2_BUFFER();
            outb(PS_DATA_PORT,ENALBE_SCANNING_COMMAND);
            READ_FROM_PS2_BUFFER();
            if(inb(PS_DATA_PORT) == 0xFA){
                // log_info("device at port 1 has acknowledged the enable scanning command",COM1);
                log_info("ps2 controller and devices intialization is complete , only port 1 is enabled (keyboard)",COM1);
                
            }

        }

    }
    else{
        log_error("device at port 1 cant be detected , disabling port 1", COM1);
        WRITE_TO_PS2_BUFFER();
        outb(PS_COMMAND_PORT,DISABLE_FIRST_PS2_PORT);

    }


}

void ENABLE_PS2_PORT1_INTERRUPT(void){
    SET_CONFIG_BYTES(ENABLE_PORT_1_AND_PORT_2_DISABLED);
    log_info("port 1 interrupt are now active",COM1);

}

void PS2_INIT(void){
    DISABLE_PS2_PORTS();
    FLUSH_OUTPUT_BUFFER();
    SET_CONFIG_BYTES(DISABLE_BOTH_PORT_CLOCK_AND_INTERRUPT);
    PS2_CONTROLLER_TEST();
    DETERMINING_NO_OF_PS2_PORTS();
    PS2_PORT_TEST();
    ENABLE_PS2_PORTS();
    RESET_PS2_DEVICES();
    DETECTING_PS2_DEVICES();

}




#include "../.h_files/pic.h"




void PIC_SEND_EOI(uint8_t irq){
    if (irq > 8){
        outb(SLAVE_PIC, PIC_EOI);
    }
    outb(MASTER_PIC,PIC_EOI);
}

void PIC_INIT(void){
    outb(MASTER_PIC_COMMAND_PORT,ICW1_INIT| ICW1_TO_INW4);
    outb(SLAVE_PIC_COMMAND_PORT,ICW1_INIT| ICW1_TO_INW4);

    outb(MASTER_PIC_DATA_PORT, MASTER_PIC_OFFSET);
    outb(SLAVE_PIC_DATA_PORT, SLAVE_PIC_OFFSET);

    outb(MASTER_PIC_DATA_PORT,MASTER_SLAVE_IRQ_PIN_CONNECTION);
    outb(SLAVE_PIC_DATA_PORT,SLAVE_PIC_CAS_IDENTITY);

    outb(MASTER_PIC_DATA_PORT,USE_86_MODE);
    outb(SLAVE_PIC_DATA_PORT,USE_86_MODE);

    outb(MASTER_PIC_DATA_PORT,USE_ALL_IRQ_PINS);
    outb(SLAVE_PIC_DATA_PORT,USE_ALL_IRQ_PINS);
    log_info("PIC is initialized",COM1);

}

void DISABLE_PIC(void){
    outb(MASTER_PIC_DATA_PORT,DISABLE_ALL_IRQ_PINS);
    outb(SLAVE_PIC_DATA_PORT,DISABLE_ALL_IRQ_PINS);
    log_info("PIC is disabled",COM1);
}

void DISABLE_A_IRQ_LINE(uint8_t irq_line){
    uint8_t complete_irq_line  = irq_line;
    uint16_t port;
    uint8_t new_bitmap;
    uint8_t current_bitmap;
    
    if(irq_line <8){
        port = MASTER_PIC_DATA_PORT;
    }
    else{
        port = SLAVE_PIC_DATA_PORT;
        irq_line -= 8;
    }

    current_bitmap = inb(port);
    new_bitmap = current_bitmap | (1<< irq_line);
    outb(port,new_bitmap);
                    

    char* irq_line_string = int_to_string(complete_irq_line);
    int size_irq_line_string = strlen_d(irq_line_string);

    char msg[] = "IRQ LINE DISABLED , LINE NO:";
    int size_msg = strlen_d(msg);

    
    int size_result = size_msg + size_irq_line_string + 1;
    char result[size_result];

    concaternate(msg , irq_line_string, result);
    log_info(result, COM1);
    
    
}


void ENABLE_A_IRQ_LINE(uint8_t irq_line){
    uint8_t complete_irq_line  = irq_line;
    uint16_t port;
    uint8_t new_bitmap;
    uint8_t current_bitmap;

    if(irq_line <8){
        port = MASTER_PIC_DATA_PORT;
    }
    else{
        port = SLAVE_PIC_DATA_PORT;
        irq_line -= 8;
    }

    current_bitmap = inb(port);
    new_bitmap = current_bitmap & ~(1<< irq_line);
    outb(port,new_bitmap);

    char* irq_line_string = int_to_string(complete_irq_line);
    int size_irq_line_string = strlen_d(irq_line_string);

    char msg[] = "IRQ LINE ENABLED , LINE NO:";
    int size_msg = strlen_d(msg);
    
    int size_result = size_msg + size_irq_line_string + 2;
    char result[size_result];

    concaternate(msg , irq_line_string, result);
    log_info(result, COM1);
    
}

uint16_t GET_PIC_ISR(){
    outb(MASTER_PIC_COMMAND_PORT,PIC_READ_ISR);
    outb(SLAVE_PIC_COMMAND_PORT,PIC_READ_ISR);

    return (inb(SLAVE_PIC_COMMAND_PORT)<< 8) | inb(MASTER_PIC_COMMAND_PORT);

}
uint16_t GET_PIC_IRR(){
    outb(MASTER_PIC_COMMAND_PORT,PIC_READ_IRR);
    outb(SLAVE_PIC_COMMAND_PORT,PIC_READ_IRR);

    return (inb(SLAVE_PIC_COMMAND_PORT)<< 8) | inb(MASTER_PIC_COMMAND_PORT);
}
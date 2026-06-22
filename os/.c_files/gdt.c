#include "../.h_files/write_to_serial.h"
#include "../.h_files/gdt.h"
#include "../.h_files/gdt_init.h"

#define GDT_TABLE_SIZE  24
uint8_t GDT_TABLE[GDT_TABLE_SIZE];

GDT_32 code_segment;
GDT_32 data_segment;
GDT_32 null_segment;
GDT_DESCRIPTOR GDTR;


void encode_gdt_32(uint8_t *target, GDT_32 source){
    if(source.limit > 0xFFFFF) {
        log_error("limit is too big , reduce limit size",COM1);
        return;
    }
    target[0] = source.limit & 0xFF;
    target[1] = (source.limit >> 8) & 0xFF;
    target[2] = source.base & 0xFF;
    target[3] = (source.base >> 8) & 0xFF;
    target[4] = (source.base >> 16) & 0xFF;
    target[5] = source.access_byte;
    target[6] = (source.limit >> 16) & 0xF;
    target[6] |= (source.flags << 4) & 0xF0;
    target[7] = (source.base >> 24) & 0xFF;

}



void gdt_segment_init(){
    null_segment.base = 0x0;
    null_segment.limit = 0x0;
    null_segment.access_byte = 0x0;
    null_segment.flags = 0x0;

    code_segment.base = 0x0;
    code_segment.limit = 0xFFFFF;
    code_segment.access_byte = 0b10011011;
    code_segment.flags = 0b1100;


    data_segment.base = 0x0;
    data_segment.limit = 0xFFFFF;
    data_segment.access_byte = 0b10010011;
    data_segment.flags = 0b1100;
}

void gdt_table_filling(){
   encode_gdt_32(GDT_TABLE,null_segment);
   encode_gdt_32(GDT_TABLE + 8,code_segment);
   encode_gdt_32(GDT_TABLE + 16,data_segment);
}

void gdtr_value(){
    GDTR.limit = GDT_TABLE_SIZE - 1;
    GDTR.base = (uint32_t)GDT_TABLE;
    gdtr_value_placing(&GDTR);
}

void gdt_start(){
    gdt_segment_init();
    gdt_table_filling();
    gdtr_value();
    log_info("gdt initialized currently using a flat memory system",COM1);
}







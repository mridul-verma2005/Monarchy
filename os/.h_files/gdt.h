#ifndef GDT_H
#define GDT_H
#include "types.h"

typedef struct {
    uint32_t base;
    uint32_t limit;
    uint8_t access_byte;
    uint8_t flags;


} GDT_32;


typedef struct  __attribute__((packed)) {
    uint16_t limit;
    uint32_t base;

} GDT_DESCRIPTOR;


void encode_gdt_32(uint8_t *target, GDT_32 source);
void gdt_segment_init();
void gdt_table_filling();
void gdtr_value();
void gdt_start();

#endif
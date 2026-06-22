#ifndef HEAP_ALLOCATOR_H
#define HEAP_ALLOCATOR_H
#define HEAP_SIZE           (1024 * 1024 * 2)  // 2 MB

#include "types.h"
#include "write_to_screen.h"
__attribute__((section(".heap_reserved")))  uint8_t RESERVED_HEAP_AREA [HEAP_SIZE];

#define ALLOCATION_BLOCK_SIZE           4               // a single block size is of 4 bytes of which in a free 
                                                        //list 4 is used by the linked list so all the of the bytes is used by the linked list

__attribute__((packed)) typedef struct {
    struct LIST_ENTRY* next;
} LIST_ENTRY;


#endif


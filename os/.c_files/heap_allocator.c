#include "../.h_files/heap_allocator.h"

//  credits to https://brokenthorn.com/Resources/OSDev26.html as I am using this document for the free list implementation]


extern char heap_start[];
extern char heap_end[];

static char* current_heap_start_pointer = heap_start;     

 LIST_ENTRY* link;

void init_free_list(void){
    uint8_t* block = current_heap_start_pointer;
    for(int i = 0 ; i < HEAP_SIZE/ALLOCATION_BLOCK_SIZE -1 ;i++){
        link = (LIST_ENTRY*) block;
        link->next = (LIST_ENTRY*)(block + ALLOCATION_BLOCK_SIZE);
        block += ALLOCATION_BLOCK_SIZE;
    }
    link = (LIST_ENTRY*)block;
    link->next = NULL;

}

void* alloc(int size){       // size is in bytes
    int no_of_blocks = 0;
    void* allocation_unit;
    link = (LIST_ENTRY*)current_heap_start_pointer;
    if(size < ALLOCATION_BLOCK_SIZE){
        no_of_blocks = 1;
    }
    else{
        no_of_blocks = size/ALLOCATION_BLOCK_SIZE;
    }
    for(int i = 0 ; i < no_of_blocks; i++){

    }
    void* allocation_unit;
    link = (LIST_ENTRY*)current_heap_start_pointer;
    allocation_unit = heap_start;
    current_heap_start_pointer = link->next;
    return allocation_unit;
}


void* free_memory(void* memory){
    void* new_free_memory = memory;
    link = (LIST_ENTRY*)new_free_memory;
    link->next = (LIST_ENTRY*)current_heap_start_pointer;
    current_heap_start_pointer = link;
}

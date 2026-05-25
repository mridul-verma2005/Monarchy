global loader
extern main
extern write_to_screen

MAGIC_NUMBER equ 0x1BADB002
FLAGS equ 0x0
CHECKSUM equ -(MAGIC_NUMBER)
KERNEL_STACK_SIZE equ 4096

section .bss 
    align 4
    kernel_stack:
        resb KERNEL_STACK_SIZE

section .rodata
    stack_init db "Stack initialized",0  
    stact_err db "Error in Stack initialization",0

section .multiboot
    ; db 0x0
    align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

section .text
loader:
    mov esp , kernel_stack + KERNEL_STACK_SIZE
    mov ebx , 0xCAFEBABE
    cmp esp , 0x00104000
    jne stact_err_print
    stack_init_print:
        push dword stack_init
        call write_to_screen
        add esp , 4



    call main
    .loop:
        hlt 
        jmp .loop


stact_err_print:
        push dword stact_err
        call write_to_screen
        add esp , 4
        .err_loop:
            hlt
            jmp .err_loop


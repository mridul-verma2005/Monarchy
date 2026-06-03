global loader
extern main
extern log_info
extern serial_port_check

COM1 equ 0x3F8

section .multiboot
MAGIC_NUMBER equ 0x1BADB002
FLAGS equ 0x0
CHECKSUM equ -(MAGIC_NUMBER)
KERNEL_STACK_SIZE equ 4096

section .bss 
    kernel_stack:
        resb KERNEL_STACK_SIZE

section .rodata
    stack_init db "Stack initialized",0  
    stack_err db "Error in Stack initialization aborting loading kernel",0

section .multiboot
    db 0x0
    align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

section .text
loader:
    call serial_port_check
    cmp eax , 0
    jne serial_port_error
    mov esp , kernel_stack + KERNEL_STACK_SIZE
   
    stack_init_log:
        push dword COM1
        push dword stack_init
        call log_info
        add esp , 8



    call main
    mov ebx , 0xCAFEBABE
    .loop:
        hlt 
        jmp .loop



serial_port_error:
    hlt
    jmp serial_port_error;
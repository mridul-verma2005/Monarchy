global loader
extern main
extern write_to_log
extern serial_port_check
COM1 equ 0x3F8

section .multiboot
MAGIC_NUMBER equ 0x1BADB002
FLAGS equ 0x0
CHECKSUM equ -(MAGIC_NUMBER)
KERNEL_STACK_SIZE equ 4096

section .bss 
    align 4
    kernel_stack:
        resb KERNEL_STACK_SIZE

section .rodata
    stack_init db "Stack initialized at 0x00104000",0  
    stack_err db "Error in Stack initialization aborting loading kernel",0

section .multiboot
    ; db 0x0
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
    mov ebx , 0xCAFEBABE
    cmp esp , 0x00104000
    jne stack_err_print
    stack_init_print:
        push dword COM1
        push dword 0x0
        push dword stack_init
        call write_to_log
        add esp , 16



    call main
    .loop:
        hlt 
        jmp .loop


stack_err_print:     ;cause if the stack is not set correcly then how you can even push var on it 
        .err_loop:
            hlt
            jmp .err_loop


serial_port_error:
    hlt
    jmp serial_port_error;
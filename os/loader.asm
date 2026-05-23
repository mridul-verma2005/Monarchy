global loader
extern sample

MAGIC_NUMBER equ 0x1BADB002
FLAGS equ 0x0
CHECKSUM equ -(MAGIC_NUMBER)
KERNEL_STACK_SIZE equ 4096

section .bss 
    align 4
    kernel_stack:
        resb KERNEL_STACK_SIZE

      

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
    push dword 1
    push dword 2
    push dword 3
    call sample



.loop:
    hlt 
    jmp .loop


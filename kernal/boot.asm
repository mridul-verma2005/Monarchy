[org 0x7c00]
KERNAL_OFFSET equ 0x1000

mov [BOOT_DRIVE] , dl
mov bp ,0x9000
mov sp , bp
mov bx , MSG_REAL_MODE
call print_string

call load_kernal

call switch_to_pm

jmp $


%include "../print_functions/print_string.asm"
%include "../diskload.asm"
%include "../32_bit/switch_to_pm.asm"
%include "../32_bit/print_text.asm"
%include "../32_bit/gdt_table.asm"

[bits 16]

load_kernal:
    mov bx , MSG_LOAD_KERNEL
    call print_string

    mov bx , KERNAL_OFFSET
    mov dh , 9
    mov dl , [BOOT_DRIVE]
    call diskload
    ret
[bits 32]


BEGIN_PM:
    mov ebx , MSG_PROT_MODE
    call print_string_pm

    call KERNAL_OFFSET

    jmp $


BOOT_DRIVE db 0
MSG_REAL_MODE db "Started in 16 - bit Real Mode",10 ,13 , 0
MSG_PROT_MODE db "Successfully landed in 32 - bit Protected Mode" , 0
MSG_LOAD_KERNEL db "Loading kernel into memory." , 0


times 510 -( $ - $$ ) db 0
dw 0xaa55
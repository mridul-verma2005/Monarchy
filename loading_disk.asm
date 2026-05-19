[org 0x7c00]

mov [BOOT_DRIVE] , dl

mov bp , 0x8000
mov sp , bp

mov bx , 0x9000
mov ax , 0
mov ds , ax
mov es , ax
mov dh , 2
mov dl , [BOOT_DRIVE]

call diskload

mov dx , [0x9000]
call print_hex

mov dx , [0x9200]
call print_hex

jmp $

%include "print_functions/print_hex.asm"
%include "diskload.asm"


BOOT_DRIVE: db 0

times 510 - ($ - $$) db 0
dw 0xaa55

times 512 db 0xda
times 512 db 0xfa



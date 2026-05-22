[org 0x7c00]
jmp start
HEX_OUT : db '0x0000' , 0
%include "print_string.asm"

print_hex:

loop:
    cmp cx , 4
    jge done1
    mov ax , dx
    and ax , 0x000f
    cmp ax , 0x0009
    jg alpha_hex
    jmp numerical_hex



alpha_hex:
    add al , 87
    jmp store_digit

numerical_hex:
    add al , '0'

store_digit:
    mov bx , HEX_OUT + 5
    sub bx , cx
    mov [bx] , al 
    shr dx , 4
    inc cx
    jmp loop


done1:
    mov bx , HEX_OUT
    call print_string
    ret


start:
    mov dx , 0x1fb6
    mov cx , 0
    call print_hex
    jmp end



end:
    jmp $

times 510 - ($ - $$) db 0

dw 0xaa55
    
    


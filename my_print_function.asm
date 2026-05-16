jmp start

%include "funtions.asm"
start:
    mov al , 'H'
    call my_print_function
    jmp end

end:
    jmp $


times 510 - ($ -$$) db 0

dw 0xaa55

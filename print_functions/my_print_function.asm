jmp start  ; using jmp here to have a correct flow of the code as if not then it will first go the the print_string part which we dont want

%include "funtions.asm" 
start:
    mov al , 'H' 
    call my_print_function
    jmp end

end:
    jmp $


times 510 - ($ -$$) db 0

dw 0xaa55

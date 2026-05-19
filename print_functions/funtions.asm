
my_print_function:
    mov ah , 0x0e
    int 0x10
    ret


some_function:
    pusha
    mov bx , 1
    add bx , 20
    mov ah , 0x0e
    mov al, bl
    int 0x10
    popa
    ret



[org 0x7c00]

print_string:
    mov ah , 0x0e
    mov al , [bx]
    cmp al , 0
    je done
    int 0x10
    add bx , 1
    jmp print_string

done:
    ret

[org 0x7c00]  ; telling our cpu the the bootloader is stored from 0x7c00 so the calculate the address using the offset correctly

print_string: ; call for our function
    mov ah , 0x0e ; move 0x0e in ah for the tele type function of the video interupt
    mov al , [bx]   ; move the value which is on the address which is stored in bx onto al
    cmp al , 0      ; cmp with 0 to check if we have reached the null terminaiting value ie '0'
    je done         ; jump if they are equal meaning the entire string has been printed
    int 0x10        ; calling the interrupt
    add bx , 1      ; go to the next consicutive address as the string is stored using db
    jmp print_string ; continue the loop

done:
    ret  ; go back the the next line from which the function was called

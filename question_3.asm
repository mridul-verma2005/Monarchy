mov bx , 30
cmp bx , 4
jle less_then_equal_4
cmp bx , 40
jl less_then_40
jmp else

less_then_equal_4:
    mov al , 'A'
    jmp end

less_then_40:
    mov al , 'B'
    jmp end

else:
    mov al , 'C'
    jmp end



end:
    mov ah , 0x0e
    int 0x10
    jmp $

; if(bx <= 4){
;     mov al , 'A'
; }
; else if (bx < 40){
;     mov al , 'B'
; }
; else {
;     mov al , 'C'
; }

; mov ah , 0x0e;
; int 0x10

; jmp $

times 510 - ($-$$) db 0

dw 0xaa55
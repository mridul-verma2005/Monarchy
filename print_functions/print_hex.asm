[org 0x7c00]  ; telling our cpu the the bootloader is stored from 0x7c00 so the calculate the address using the offset correctly
HEX_OUT : db '0x0000' , 0 ; outputing label , never let cpu run on the data , keep the data seperate
%include "print_functions/print_string.asm"  
; using print_stirng.asm file for the print_string function

print_hex:  ; main function
    pusha                 ; push all the register values to the stack
    mov cx , 0
loop:
    cmp cx , 4        ; comparing the count value in cx to confirm how much we have parsed the hex value
    jge done1         ; if cx = 4 then we have completed the parsing
    mov ax , dx       ; main value will be in dx , we are copying the value to ax
    and ax , 0x000f   ; AND wil 0x000f to get the last digit
    cmp ax , 0x0009   ; comparing with 0x0009 to see whether we have a nummerical value or a alpha value
    jg alpha_hex      ; if the value is greater the 0x009 then jump to the alpha part 
    jmp numerical_hex ; else to the numerical part



alpha_hex:
    add al , 87      ; add 87 to get alpha ascii of the alpha digit
    jmp store_digit  ; jump to store the digit in HEX_OUT

numerical_hex:
    add al , '0'  ; add '0' to the get ascii value of the numerical digit

store_digit:
    mov bx , HEX_OUT + 5  ; as the pointer will be on the first 0 of the 0x0000 we will have to do +5 to get to the last digit
    sub bx , cx           ; then we will subtract the value bx from cx to get to the inner value as if cx is 1 then the last digit transfromation is completed then we go the second last digit
    mov [bx] , al         ; mov the value stored in al to the current address stored in bx
    shr dx , 4            ; shift to 4 digit right in dx to get the inner digit
    inc cx                ; increment the counter cx
    jmp loop              ; continue the loop till the counter cx reaches 4


done1:
    mov bx , HEX_OUT      ; now move the offset of the HEX_OUT in bx to be used for the print_string function
    call print_string     ; call the print_string function
    popa                  ; pop all the value stored in the stack to there respective registers
    ret                   ; go back the next line from which the function was called


start:
                ; start the counter cx with value 0
    call print_hex        ; call the print hex solution
              




    
    


diskload:
    push dx         ; push the value of dx to store them on the stack
    mov ah , 0x02   ; moving the value 0x02 in ah for the disk service interrupt
    mov al , dh     ; moving the no of sectors which we need to read in al which were stored in dh , it is required by bios to have them in al
    mov ch , 0x00   ; selecting the cylinder ( 0 in this case)
    mov dh , 0x00     ; selecing the head ( 0 in case , which uses base 0 , ie starts from 0)
    mov cl , 0x02   ; selecting start reading from which sector (2 in this case , uses base 1 in here)
    int 0x13        ; calling the interrupt

    jc disk_error   ; jump if the carry flag are set , after the 0x13 interrupt the cpu will put new values 
                    ; in regsiter cf and al , cf will have 0 if the disk read is sucessful and 1 if failed , similary al will have 
                    ; how many sectors were read sucessfully , if the cf = 0 then jump to disk error

    pop dx          ; retrieve back the value stored in dx (done just to be safe)
    cmp dh , al     ; compare the value in al and dh , if same then the disk read is sucessful, else some sectors werent read
    jne disk_error  ; jump if not equal to disk_error
    ret

disk_error:
    mov bx , DISK_ERROR_MSG  ; moving the address of the DISK_ERROR_MSG into the bx for the  print_string to work
    call print_string
    ret                      ; return to the caller

DISK_ERROR_MSG: db "Disk read error !" , 0



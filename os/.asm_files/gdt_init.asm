global gdtr_value_placing


section .text
gdtr_value_placing:
    mov eax , [esp + 4]
    lgdt [eax];
    jmp 0x08:reload_other_segments

reload_other_segments:
    mov eax , 0x08
    mov eax , 0x10
    mov ds , ax
    mov es , ax
    mov ss , ax
    mov gs , ax
    mov fs , ax
    ret




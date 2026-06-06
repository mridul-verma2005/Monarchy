NAMSFLAGS = -f elf
GCCFLAGS = -m32 -nostdlib -nostdinc -fno-builtin 
GCCFLAGS += -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -I.h_files/
LINKERFLAGS =  -T .ld_files/link.ld -m elf_i386
RUNQEMU = qemu-system-i386
FILES_KERNEL = loader.o io.o gdt_init.o gdt.o kernel_main.o move_cursor.o serial_port.o write_to_screen.o 
FILES_KERNEL += write_to_serial.o idt.o idt_isr.o pic.o helper_function.o ps2.o keyboard.o bss_cleaning.o 
FILES_ISO = kernel.elf .cfg_files/grub.cfg serial1.log 
FILES_EXE = Monarchy.iso kernel.elf serial1.log

Monarchy.iso : $(FILES_ISO)
	mkdir -p iso/boot/grub

	cp kernel.elf iso/boot/

	cp .cfg_files/grub.cfg iso/boot/grub

	grub-mkrescue -o Monarchy.iso iso

serial1.log:
	touch serial1.log

kernel.elf : $(FILES_KERNEL)
	ld $(LINKERFLAGS) $(FILES_KERNEL) -o kernel.elf


loader.o : .asm_files/loader.asm
	nasm $(NAMSFLAGS) .asm_files/loader.asm -o loader.o

io.o : .asm_files/io.asm 
	nasm $(NAMSFLAGS) .asm_files/io.asm -o io.o

idt_isr.o : .asm_files/idt_isr.asm 
	nasm $(NAMSFLAGS) .asm_files/idt_isr.asm -o idt_isr.o

gdt_init.o : .asm_files/gdt_init.asm 
	nasm $(NAMSFLAGS) .asm_files/gdt_init.asm -o gdt_init.o

move_cursor.o : .c_files/move_cursor.c .h_files/io.h .h_files/move_cursor.h
	gcc $(GCCFLAGS) .c_files/move_cursor.c -o move_cursor.o

kernel_main.o : .c_files/kernel_main.c .h_files/move_cursor.h .h_files/write_to_screen.h .h_files/write_to_serial.h
	gcc $(GCCFLAGS) .c_files/kernel_main.c -o kernel_main.o

serial_port.o : .c_files/serial_port.c .h_files/write_to_screen.h  .h_files/write_to_serial.h  .h_files/io.h
	gcc $(GCCFLAGS) .c_files/serial_port.c -o serial_port.o

write_to_screen.o : .c_files/write_to_screen.c .h_files/move_cursor.h
	gcc $(GCCFLAGS) .c_files/write_to_screen.c -o write_to_screen.o

write_to_serial.o : .c_files/write_to_serial.c .h_files/serial_port.h
	gcc $(GCCFLAGS) .c_files/write_to_serial.c -o write_to_serial.o

gdt.o : .c_files/gdt.c .h_files/gdt.h .h_files/write_to_serial.h .h_files/gdt_init.h
	gcc $(GCCFLAGS) .c_files/gdt.c -o gdt.o

idt.o : .c_files/idt.c .h_files/idt.h
	gcc $(GCCFLAGS) .c_files/idt.c -o idt.o

pic.o : .c_files/pic.c .h_files/pic.h
	gcc $(GCCFLAGS) .c_files/pic.c -o pic.o

ps2.o : .c_files/ps2.c .h_files/ps2.h
	gcc $(GCCFLAGS) .c_files/ps2.c -o ps2.o

helper_function.o : .c_files/helper_function.c 
	gcc $(GCCFLAGS) .c_files/helper_function.c -o helper_function.o

keyboard.o : .c_files/keyboard.c .h_files/keyboard.h
	gcc $(GCCFLAGS) .c_files/keyboard.c -o keyboard.o

bss_cleaning.o : .c_files/bss_cleaning.c 
	gcc $(GCCFLAGS) .c_files/bss_cleaning.c -o bss_cleaning.o



run : Monarchy.iso 
	$(RUNQEMU) Monarchy.iso -monitor stdio -serial file:serial1.log

clean :
	rm *.elf *.iso *.o *.log
	rm -rf iso/
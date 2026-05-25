NAMSFLAGS = -f elf
GCCFLAGS = -m32 -nostdlib -nostdinc -fno-builtin 
GCCFLAGS += -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -I.h_files/
LINKERFLAGS =  -T .ld_files/link.ld -m elf_i386
RUNQEMU = qemu-system-i386
FILES_KERNEL = loader.o main.o fb.o move_cursor.o io.o 
FILES_KERNEL += write_to_screen.o serial_port_config.o write_to_serial.o serial_port_check.o
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

move_cursor.o : .c_files/move_cursor.c .h_files/io.h .h_files/move_cursor.h
	gcc $(GCCFLAGS) .c_files/move_cursor.c -o move_cursor.o

main.o : .c_files/main.c .h_files/fb.h .h_files/move_cursor.h .h_files/write_to_screen.h .h_files/write_to_serial.h
	gcc $(GCCFLAGS) .c_files/main.c -o main.o

fb.o : .c_files/fb.c .h_files/fb.h
	gcc $(GCCFLAGS) .c_files/fb.c -o fb.o

serial_port_config.o : .c_files/serial_port_config.c .h_files/serial_port_config.h .h_files/io.h
	gcc $(GCCFLAGS) .c_files/serial_port_config.c -o serial_port_config.o

serial_port_check.o : .c_files/serial_port_check.c .h_files/serial_port_config.h .h_files/write_to_screen.h  .h_files/write_to_serial.h
	gcc $(GCCFLAGS) .c_files/serial_port_check.c -o serial_port_check.o

write_to_screen.o : .c_files/write_to_screen.c .h_files/move_cursor.h
	gcc $(GCCFLAGS) .c_files/write_to_screen.c -o write_to_screen.o


write_to_serial.o : .c_files/write_to_serial.c .h_files/serial_port_config.h
	gcc $(GCCFLAGS) .c_files/write_to_serial.c -o write_to_serial.o

run : Monarchy.iso 
	$(RUNQEMU) Monarchy.iso -monitor stdio -serial file:serial1.log

clean :
	rm *.elf *.iso *.o *.log
	rm -rf iso/
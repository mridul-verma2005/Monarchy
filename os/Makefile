NAMSFLAGS = -f elf
GCCFLAGS = -m32 -nostdlib -nostdinc -fno-builtin 
GCCFLAGS += -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -I.
LINKERFLAGS =  -T link.ld -m elf_i386
RUNQEMU = qemu-system-i386
FILES_KERNEL = loader.o sample.o fb.o move_cursor.o io.o
FILES_ISO = kernel.elf grub.cfg



Monarchy.iso : $(FILES_ISO)
	mkdir -p iso/boot/grub

	cp kernel.elf iso/boot/

	cp grub.cfg iso/boot/grub

	grub-mkrescue -o Monarchy.iso iso

kernel.elf : $(FILES_KERNEL)
	ld $(LINKERFLAGS) $(FILES_KERNEL) -o kernel.elf


loader.o : loader.asm
	nasm $(NAMSFLAGS) loader.asm -o loader.o

io.o : io.asm 
	nasm $(NAMSFLAGS) io.asm -o io.o

move_cursor.o : move_cursor.c io.h move_cursor.h
	gcc $(GCCFLAGS) move_cursor.c -o move_cursor.o

sample.o : sample.c fb.h move_cursor.h
	gcc $(GCCFLAGS) sample.c -o sample.o

fb.o : fb.c fb.h
	gcc $(GCCFLAGS) fb.c -o fb.o

run : Monarchy.iso
	$(RUNQEMU) Monarchy.iso -monitor stdio

clean :
	rm *.elf *.iso *.o 
	rm -rf iso/

os-image: boot.bin kernel.bin
	cat boot.bin kernel.bin > os-image

kernel.bin: kernel_entry.o kernel.o
	ld -m elf_i386 -o kernel.bin -Ttext 0x1000 --oformat binary kernel_entry.o kernel.o

kernel.o : kernel.c
	gcc -m32 -ffreestanding -fno-pie -c kernel.c -o kernel.o

kernel_entry.o : kernel_entry.asm
	nasm -f elf kernel_entry.asm -o kernel_entry.o

boot.bin : boot.asm
	nasm boot.asm -f bin -o boot.bin

clean:
	rm *.bin *.o os-image

run: 
	qemu-system-x86_64 os-image


so , I am trying to make a OS from scratch in this summer vacation , ITS is not related to arch linux at all , kinda liked monarchy hence used that name , currently the kernal prints kernal loaded succesfully 
only , to run it go into cd kernel and run these command ( it will produce 32 bit machine code)
cd kernal to go into the kernel directory 
nasm -f bin boot.asm -o boot.bin 
gcc -m32 -ffreestanding -fno-pie -c kernel.c -o kernel.o 
ld -m elf_i386 -o kernel.bin -Ttext 0x1000 --oformat binary kernel.o
cat boot.bin kernel.bin > os-image
qemu-system-x86_64 os-image
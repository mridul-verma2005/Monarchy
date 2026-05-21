# Monarchy OS 

A hobby operating system built completely from scratch during summer vacation.

> **Note:** Despite the name, this project is completely unrelated to Arch Linux—I just happen to like the name. Currently, the OS boots successfully from a custom bootloader, transitions into 32-bit Protected Mode, and hands execution over to a C kernel which prints a "Kernel loaded successfully" message.

---

##  Prerequisites

To build and run Monarchy OS, you will need the following tools installed:
* **NASM** (Netwide Assembler)
* **GCC** (with 32-bit compilation support, e.g., `gcc-multilib`)
* **GNU Linker (ld)**
* **QEMU** (`qemu-system-x86_64`)

---

## How to Build and Run

Run these commands in your terminal to compile the 32-bit machine code, merge the components, and boot the OS image in the emulator:

```bash
# 1. Navigate to the kernel directory
cd kernel

# 2. Assemble the bootloader into a raw binary
nasm -f bin boot.asm -o boot.bin

# 3. Compile the C kernel (32-bit, freestanding, no-pie)
gcc -m32 -ffreestanding -fno-pie -c kernel.c -o kernel.o

# 4. Link the kernel to physical address 0x1000
ld -m elf_i386 -o kernel.bin -Ttext 0x1000 --oformat binary kernel.o

# 5. Combine the bootloader and kernel into a master OS image
cat boot.bin kernel.bin > os-image

# 6. Boot it up in QEMU!
qemu-system-x86_64 os-image

# Monarchy OS 

A hobby operating system currently in progress built completely from scratch during summer vacation. Please checkout the vidoe it has a preview of the OS.

> **Note:** Despite the name, this project is completely unrelated to Arch Linux—I just happen to like the name. Currently, the OS boots successfully via grub and a custom loader script, transitions into 32-bit Protected Mode, and hands execution over to a C kernel which start a custom Monarchy shell , the shell currenly currrently support command history which can store upto 16 command in a LRU manner which can be used by the up arrow key, the shell currently have a 256 bytes command buffer , enough for the scope of project and buffer overflow protection, currently the shell support commands such as hello , help , clear , clear -b (to clear the command history) , fetch to get sys info , uptime and time , everything is interrupt driven except the serial logger (not a part of os just for dubugging) , after the file manager implemenatation the sys.log file be created instead. currently because of the intership the project is halted and will be started in the near future , the heap allocator , text editor and a persistent file system will be implemented.

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
cd os

# 2. Run Make clean
Make clean

# 3. Run Make to make the os-image and all the other necessary executables and object files
Make

# 4. Run Make run to boot it on QEMU
Make run



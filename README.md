# wl-00-riscv
A simple Unix-like OS implemented for RISC-V based machine.\n
To run:\n
make\n
qemu-system-riscv64 -machine virt -bios none -kernel kernel.elf -serial stdio

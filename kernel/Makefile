CC = riscv64-unknown-elf-gcc
LD = $(CC)

CFLAGS = -ffreestanding -nostdlib -mcmodel=medany -O2 -Wall
LDFLAGS = -T kernel.ld -nostdlib -ffreestanding

C_SRC = boot.c main.c print.c uart.c mem.c
ASM_SRC = boot_asm.S

C_OBJ = $(C_SRC:.c=.o)
ASM_OBJ = $(ASM_SRC:.S=.o)
OBJ = $(ASM_OBJ) $(C_OBJ)

OUTPUT = kernel.elf

all: $(OUTPUT)

$(OUTPUT): $(OBJ) kernel.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(OUTPUT)
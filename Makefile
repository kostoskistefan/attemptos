NASM := nasm
NASMFLAGS := -I src/

LD := ld
LDFLAGS := -Ttext 0x1000 --oformat binary

CC := gcc
CCFLAGS := -ffreestanding

QEMU := qemu-system-x86_64
QEMUFLAGS := -fda

SOURCE_DIR := src/x86_64
BUILD_DIR := build

# Build everything needed for our OS
all: $(BUILD_DIR)/os-image.bin
	chmod 777 -R $(BUILD_DIR)

# Run QEMU to test our OS
run:
	$(QEMU) $(QEMUFLAGS) $(BUILD_DIR)/os-image.bin

# Build the OS image
$(BUILD_DIR)/os-image.bin: $(BUILD_DIR)/boot_sector.bin $(BUILD_DIR)/kernel.bin
	cat $^ > $@

# Build the kernel binary
$(BUILD_DIR)/kernel.bin : $(BUILD_DIR)/kernel_entry.o $(BUILD_DIR)/kernel.o
	$(LD) $^ $(LDFLAGS) -o $@

# Build the kernel object file
$(BUILD_DIR)/kernel.o : $(SOURCE_DIR)/boot/kernel.c
	$(CC) -c $< $(CCFLAGS) -o $@

# Build the kernel entry object file
$(BUILD_DIR)/kernel_entry.o: $(SOURCE_DIR)/boot/kernel_entry.asm
	$(NASM) $< $(NASMFLAGS) -f elf64 -o $@

# Build the boot sector
$(BUILD_DIR)/boot_sector.bin: $(SOURCE_DIR)/boot/boot_sector.asm
	mkdir -p $(BUILD_DIR)
	$(NASM) $< $(NASMFLAGS) -f bin -o $@

clean:
	rm -rf build

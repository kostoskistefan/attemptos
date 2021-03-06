NASM := nasm
NASMFLAGS := -I src/

LD := ld
LDFLAGS := -Ttext 0x1000 --oformat binary -m elf_i386

CC := gcc
CFLAGS := -ffreestanding -m32 -g -Wall -Wextra -Werror -fno-exceptions

QEMU := qemu-system-x86_64

SOURCE_DIR := src
BUILD_DIR := build

C_SOURCES = $(shell find ${SOURCE_DIR} -name "*.c")
HEADERS = $(shell find ${SOURCE_DIR} -name "*.h")

OBJ = ${C_SOURCES:.c=.o}

all: dir os-image.bin
	chmod 777 os-image.bin

dir:
	mkdir -p ${BUILD_DIR}

os-image.bin: ${SOURCE_DIR}/boot/boot_sector.bin kernel.bin
	cat $^ > os-image.bin

kernel.bin: ${SOURCE_DIR}/boot/kernel_entry.o ${OBJ} ${SOURCE_DIR}/cpu/interrupt.o
	${LD} -o $@ ${LDFLAGS} $^

kernel.elf: ${SOURCE_DIR}/boot/kernel_entry.o ${OBJ} ${SOURCE_DIR}/cpu/interrupt.o
	${LD} -o $@ -m elf_i386 -Ttext 0x1000 $^ 

run:
	${QEMU} -blockdev driver=file,node-name=f0,filename=os-image.bin -device floppy,drive=f0 

debug: os-image.bin kernel.elf
	${QEMU} -s -S -blockdev driver=file,node-name=f0,filename=os-image.bin -device floppy,drive=f0 &
	gdb -tui -ex "target remote :1234" -ex "symbol-file kernel.elf"


%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

%.o: %.asm
	${NASM} ${NASMFLAGS} $< -f elf32 -o $@

%.bin: %.asm
	${NASM} ${NASMFLAGS} $< -f bin -o $@

clean:
	find ./ -type f \( -iname \*.bin -o -iname \*.o \) -delete
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o
	rm -rf build

# # Build everything needed for our OS
# all: dir $(BUILD_DIR)/os-image.bin
# 	chmod 777 -R $(BUILD_DIR)
#
# dir:
# 	mkdir -p $(BUILD_DIR)
#
# # Run QEMU to test our OS
# run:
# 	$(QEMU) $(QEMUFLAGS) $(BUILD_DIR)/os-image.bin
#
# # Build the OS image
# $(BUILD_DIR)/os-image.bin: $(BUILD_DIR)/boot_sector.bin $(BUILD_DIR)/kernel.bin
# 	cat $^ > $@
#
# # Build the kernel binary
# $(BUILD_DIR)/kernel.bin : $(BUILD_DIR)/kernel_entry.o $(BUILD_DIR)/kernel.o
# 	$(LD) $^ $(LDFLAGS) -o $@
#
# # Build the kernel object file
# $(BUILD_DIR)/kernel.o : $(SOURCE_DIR)/kernel/kernel.c
# 	$(CC) -c $< $(CCFLAGS) -o $@
#
# # Build the kernel entry object file
# $(BUILD_DIR)/kernel_entry.o: $(SOURCE_DIR)/boot/kernel_entry.asm
# 	$(NASM) $< $(NASMFLAGS) -f elf64 -o $@
#
# # Build the boot sector
# $(BUILD_DIR)/boot_sector.bin: $(SOURCE_DIR)/boot/boot_sector.asm
# 	$(NASM) $< $(NASMFLAGS) -f bin -o $@
#
# clean:
# 	find ./ -type f \( -iname \*.bin -o -iname \*.o \) -delete
# 	rm -rf build

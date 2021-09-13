export NASMENV = -I src/

SOURCES := $(shell find src/ -name "*.asm")

all:
	mkdir -p build/x86_64/ && \
	nasm -f bin src/x86_64/boot/boot_sector.asm -o build/x86_64/kernel.bin

clean:
	rm -rf build
	
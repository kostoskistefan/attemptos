export NASMENV = -f bin -I src/

SOURCES := $(shell find src/ -name "*.asm")

all:
	mkdir -p build/x86_64/ && \
	nasm src/x86_64/boot/boot_sector.asm -o build/x86_64/kernel.bin && \
	chmod 777 -R build

clean:
	rm -rf build && \
	rm *.bin *.o
	
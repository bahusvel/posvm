.PHONY: clean

ARCH=amd64
CFLAGS=-g -Iinclude -Wall
SOURCES=src/main.c src/sb_set.c
OBJECTS=$(SOURCES:.c=.o)

echo:
	echo $(OBJECTS)

clean:
	rm -f build/*
	rm -f src/*.o

entry: src/arch/$(ARCH)/entry.asm src/arch/$(ARCH)/c_entry.c
	nasm -f elf64 src/arch/$(ARCH)/entry.asm -o build/entry.o
	gcc $(CFLAGS) -o build/c_entry.o -c src/arch/$(ARCH)/c_entry.c -Iinclude/arch/$(ARCH)

build_dis: src/arch/amd64/dis.c
	gcc $< -lcapstone -o build/dis
	build/dis


build_main: entry $(OBJECTS)
	gcc $(CFLAGS) build/entry.o build/c_entry.o $(OBJECTS) -o build/posvm

debug_main: build_main
	gdb build/posvm

run_main: build_main
	build/posvm

dump_main: build_main
	objdump -d build/posvm -j .text

hello_test: test/hello.asm
	nasm -f elf64 test/hello.asm -o build/hello.o
	ld -o build/hello build/hello.o
	build/hello

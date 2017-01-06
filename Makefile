.PHONY: clean

ARCH=amd64
CFLAGS=-g

all: clean

clean:

run:

entry: src/arch/$(ARCH)/entry.asm src/arch/$(ARCH)/c_entry.c
	nasm -f elf64 src/arch/$(ARCH)/entry.asm -o build/entry.o
	gcc $(CFLAGS) -o build/c_entry.o -c src/arch/$(ARCH)/c_entry.c -Iinclude/arch/$(ARCH)

build_main: entry src/main.c
	gcc $(CFLAGS) -c src/main.c -o build/main.o
	gcc $(CFLAGS) build/entry.o build/c_entry.o build/main.o -o build/posvm


debug_main: build_main
	gdb build/posvm

run_main: build_main
	build/posvm

hello_build: test/hello.asm
	nasm -f elf64 test/hello.asm
	ld -o test/hello test/hello.o
	test/hello

.PHONY: clean

ARCH=amd64

all: clean

clean:

run:

entry: src/arch/$(ARCH)/entry.asm src/arch/$(ARCH)/c_entry.c
	nasm -f elf64 src/arch/$(ARCH)/entry.asm -o build/entry.o
	gcc -o build/c_entry.o -c src/arch/$(ARCH)/c_entry.c -Iinclude/arch/$(ARCH)

main: entry src/main.c
	gcc -c src/main.c -o build/main.o
	gcc build/entry.o build/c_entry.o build/main.o -o build/posvm
	build/posvm

hello_build: test/hello.asm
	nasm -f elf64 test/hello.asm
	ld -o test/hello test/hello.o
	test/hello

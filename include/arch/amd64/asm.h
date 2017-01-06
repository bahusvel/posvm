#ifndef _POSVM_ASM_
#define _POSVM_ASM_

typedef struct {
	unsigned long rip;
	unsigned long rflags;
	unsigned long rax;
	unsigned long rsp;
	unsigned long rbx;
	unsigned long rcx;
	unsigned long rdx;
	unsigned long rsi;
	unsigned long rdi;
	unsigned long rbp;
	unsigned long r8;
	unsigned long r9;
	unsigned long r10;
	unsigned long r11;
	unsigned long r12;
	unsigned long r13;
	unsigned long r14;
	unsigned long r15;
} pt_regs;

#endif

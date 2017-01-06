#ifndef _POSVM_ASM_
#define _POSVM_ASM_
#include <stdio.h>

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

void print_regs(pt_regs *regs) {
	printf("RIP: [<%016lx>]\n", regs->rip);
	printf("RSP: %016lx  EFLAGS: %08lx\n", regs->rsp, regs->rflags);
	printf("RAX: %016lx RBX: %016lx RCX: %016lx\n",regs->rax, regs->rbx, regs->rcx);
    printf("RDX: %016lx RSI: %016lx RDI: %016lx\n",regs->rdx, regs->rsi, regs->rdi);
    printf("RBP: %016lx R08: %016lx R09: %016lx\n",regs->rbp, regs->r8, regs->r9);
    printf("R10: %016lx R11: %016lx R12: %016lx\n",regs->r10, regs->r11, regs->r12);
    printf("R13: %016lx R14: %016lx R15: %016lx\n",regs->r13, regs->r14, regs->r15);
}

#endif

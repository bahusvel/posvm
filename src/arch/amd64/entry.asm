section .text
global posvm_entry
global _posvm_prep
extern _c_posvm_entry

_posvm_prep:
	call posvm_entry
	
posvm_entry:
	push rax
	push rbx
	push rcx
	push rdx
	push rsi
	push rdi
	push rbp
	push rsp
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
	pushf
	mov rdi, rsp
	sub rdi, (17 * 8)
	call _c_posvm_entry

posvm_exit:

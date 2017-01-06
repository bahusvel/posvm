section .text
global posvm_entry
global _posvm_prep
extern _c_posvm_entry

_posvm_prep:
	call near [posvm_entry_ptr]
posvm_entry:
	pushf
	push rax
	mov rax, rsp
	add rax, (2 * 8) ; rax + rip(from call)
	push rax
	push rbx
	push rcx
	push rdx
	push rsi
	push rdi
	push rbp
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
	mov rdi, rsp
	add rdi, (18 * 8)
_before_c_call:
	call _c_posvm_entry
posvm_exit:
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rbp
	pop rdi
	pop rsi
	pop rdx
	pop rcx
	pop rbx
	add rsp, 8
	pop rax
	popf
	ret

section .rodata
	global posvm_entry_ptr
	global posvm_call_ptr
	global posvm_call_len
	posvm_entry_ptr dq posvm_entry
	posvm_call_ptr dq _posvm_prep
	posvm_call_len dq posvm_entry - _posvm_prep

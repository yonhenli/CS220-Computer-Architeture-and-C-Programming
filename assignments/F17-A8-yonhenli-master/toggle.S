.intel_syntax noprefix
.text
.global toggle_bit

toggle_bit:

mov	r8, rdi
mov	r9, rsi
cmp	r9, 0x3f
jbe	operation
mov	rax, 0x0
jmp	exit

operation:
mov	rax, r9
mov	rdx, 0x1
mov	rcx, rax
shl	rdx, cl
mov	rax, rdx

xor	r8, rax
mov	rax, r8

exit:
ret

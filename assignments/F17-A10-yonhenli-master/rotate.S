.intel_syntax noprefix
.text
.global rotate

rotate:
push	r12
mov		r10, rdi
mov		r11, rsi
mov 	r12, rdx

mov		eax, r11d
cdq
mov		rcx, 0x40
div		ecx
mov		ecx, edx

cmp		r12, 0x0
je		right_rotate

left_rotate:
rol		r10, cl
jmp		exit

right_rotate:
ror 	r10, cl

exit:
mov rax, r10
pop r12
ret
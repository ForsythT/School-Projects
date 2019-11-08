	.file	"prime_number.c"
	.text
	.globl	main
	.type	main, @function
main:
	movl	$2, %ecx
	movl	$1, %edi
	movl	$59, %esi
	jmp	.L2
.L4:
	movl	%esi, %eax
	cltd
	idivl	%ecx
	testl	%edx, %edx
	jne	.L3
	movl	$0, %edi
.L3:
	addl	$1, %ecx
.L2:
	cmpl	$58, %ecx
	jle	.L4
	movl	%edi, %eax
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-16)"
	.section	.note.GNU-stack,"",@progbits

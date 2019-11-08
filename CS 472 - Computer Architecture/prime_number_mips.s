	.file	1 "prime_number.c"
	.section .mdebug.abiN32
	.previous
	.gnu_attribute 4, 1
	.abicalls
	.text
	.align	2
	.globl	main
	.set	nomips16
	.ent	main
	.type	main, @function
main:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	li	$3,2			# 0x2
	li	$2,1			# 0x1
	.option	pic0
	j	.L2
	.option	pic2
	li	$5,59			# 0x3b

.L4:
	div	$0,$5,$3
	teq	$3,$0,7
	mfhi	$4
	beql	$4,$0,.L3
	move	$2,$0

.L3:
	addiu	$3,$3,1
.L2:
	slt	$4,$3,59
	bne	$4,$0,.L4
	nop

	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-16)"

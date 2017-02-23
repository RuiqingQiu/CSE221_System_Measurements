	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.section	__TEXT,__literal8,8byte_literals
	.align	3
LCPI0_0:
	.quad	4696837146684686336     ## double 1.0E+6
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp2:
	.cfi_def_cfa_register %rbp
	subq	$240, %rsp
	leaq	L_.str(%rip), %rdi
	movl	$0, -4(%rbp)
	movb	$0, %al
	callq	_printf
	leaq	-160(%rbp), %rdi
	xorl	%ecx, %ecx
	movl	%ecx, %esi
	movl	%eax, -188(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_gettimeofday
	## InlineAsm Start
	cpuid
	## InlineAsm End
	movl	%eax, -192(%rbp)        ## 4-byte Spill
	## InlineAsm Start
	rdtsc
	## InlineAsm End
	movq	%rdx, __hi(%rip)
	movq	%rax, __lo(%rip)
	movq	__hi(%rip), %rax
	shlq	$32, %rax
	orq	__lo(%rip), %rax
	movq	%rax, -16(%rbp)
	movq	$0, -168(%rbp)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpq	$1000000, -168(%rbp)    ## imm = 0xF4240
	jae	LBB0_4
## BB#2:                                ##   in Loop: Header=BB0_1 Depth=1
	movq	_bigmem@GOTPCREL(%rip), %rax
	movq	-168(%rbp), %rcx
	movb	$17, (%rax,%rcx)
## BB#3:                                ##   in Loop: Header=BB0_1 Depth=1
	movq	-168(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -168(%rbp)
	jmp	LBB0_1
LBB0_4:
	## InlineAsm Start
	rdtscp
	## InlineAsm End
	movq	%rdx, __hi(%rip)
	movq	%rax, __lo(%rip)
	movq	__hi(%rip), %rax
	shlq	$32, %rax
	orq	__lo(%rip), %rax
	movq	%rax, -24(%rbp)
	## InlineAsm Start
	cpuid
	## InlineAsm End
	leaq	-144(%rbp), %rdi
	xorl	%ecx, %ecx
	movl	%ecx, %esi
	movb	$0, %al
	callq	_gettimeofday
	leaq	L_.str.1(%rip), %rdi
	movsd	LCPI0_0(%rip), %xmm0    ## xmm0 = mem[0],zero
	movq	-24(%rbp), %rdx
	subq	-16(%rbp), %rdx
	movq	%rdx, -32(%rbp)
	movl	-136(%rbp), %ecx
	subl	-152(%rbp), %ecx
	movslq	%ecx, %rdx
	movq	%rdx, -104(%rbp)
	cvtsi2sdq	-104(%rbp), %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, -120(%rbp)
	movq	-32(%rbp), %rsi
	movl	%eax, -196(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	L_.str.2(%rip), %rdi
	movq	-104(%rbp), %rsi
	movl	%eax, -200(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	L_.str.3(%rip), %rdi
	movsd	-120(%rbp), %xmm0       ## xmm0 = mem[0],zero
	movl	%eax, -204(%rbp)        ## 4-byte Spill
	movb	$1, %al
	callq	_printf
	leaq	L_.str.4(%rip), %rdi
	movl	%eax, -208(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	-160(%rbp), %rdi
	xorl	%ecx, %ecx
	movl	%ecx, %esi
	movq	$0, -176(%rbp)
	movl	%eax, -212(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_gettimeofday
	## InlineAsm Start
	cpuid
	## InlineAsm End
	movl	%eax, -216(%rbp)        ## 4-byte Spill
	## InlineAsm Start
	rdtsc
	## InlineAsm End
	movq	%rdx, __hi(%rip)
	movq	%rax, __lo(%rip)
	movq	__hi(%rip), %rax
	shlq	$32, %rax
	orq	__lo(%rip), %rax
	movq	%rax, -16(%rbp)
	movq	$0, -184(%rbp)
LBB0_5:                                 ## =>This Inner Loop Header: Depth=1
	cmpq	$1000000, -184(%rbp)    ## imm = 0xF4240
	jae	LBB0_8
## BB#6:                                ##   in Loop: Header=BB0_5 Depth=1
	movq	_bigmem@GOTPCREL(%rip), %rax
	movq	-176(%rbp), %rcx
	movq	-184(%rbp), %rdx
	movzbl	(%rax,%rdx), %esi
	movl	%esi, %eax
	addq	%rax, %rcx
	movq	%rcx, -176(%rbp)
## BB#7:                                ##   in Loop: Header=BB0_5 Depth=1
	movq	-184(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -184(%rbp)
	jmp	LBB0_5
LBB0_8:
	## InlineAsm Start
	rdtscp
	## InlineAsm End
	movq	%rdx, __hi(%rip)
	movq	%rax, __lo(%rip)
	movq	__hi(%rip), %rax
	shlq	$32, %rax
	orq	__lo(%rip), %rax
	movq	%rax, -24(%rbp)
	## InlineAsm Start
	cpuid
	## InlineAsm End
	leaq	-144(%rbp), %rdi
	xorl	%ecx, %ecx
	movl	%ecx, %esi
	movb	$0, %al
	callq	_gettimeofday
	leaq	L_.str.5(%rip), %rdi
	movsd	LCPI0_0(%rip), %xmm0    ## xmm0 = mem[0],zero
	movq	-24(%rbp), %rdx
	subq	-16(%rbp), %rdx
	movq	%rdx, -32(%rbp)
	movl	-136(%rbp), %ecx
	subl	-152(%rbp), %ecx
	movslq	%ecx, %rdx
	movq	%rdx, -112(%rbp)
	cvtsi2sdq	-112(%rbp), %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, -128(%rbp)
	movq	-32(%rbp), %rsi
	movl	%eax, -220(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	L_.str.6(%rip), %rdi
	movq	-112(%rbp), %rsi
	movl	%eax, -224(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	L_.str.7(%rip), %rdi
	movsd	-128(%rbp), %xmm0       ## xmm0 = mem[0],zero
	movl	%eax, -228(%rbp)        ## 4-byte Spill
	movb	$1, %al
	callq	_printf
	xorl	%ecx, %ecx
	movl	%eax, -232(%rbp)        ## 4-byte Spill
	movl	%ecx, %eax
	addq	$240, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"Beginning writes.\n"

.zerofill __DATA,__bss,__hi,8,3         ## @_hi
.zerofill __DATA,__bss,__lo,8,3         ## @_lo
	.comm	_bigmem,1000000,4       ## @bigmem
L_.str.1:                               ## @.str.1
	.asciz	"Write cycles:\n%llu\n"

L_.str.2:                               ## @.str.2
	.asciz	"Write time in msec:\n%ld\n"

L_.str.3:                               ## @.str.3
	.asciz	"Write byte/msec:\n%f\n"

L_.str.4:                               ## @.str.4
	.asciz	"\n\nBeginning reads.\n"

L_.str.5:                               ## @.str.5
	.asciz	"Read cycles:\n%llu\n"

L_.str.6:                               ## @.str.6
	.asciz	"Read time in msec:\n%ld\n"

L_.str.7:                               ## @.str.7
	.asciz	"Read byte/msec:\n%f\n"


.subsections_via_symbols

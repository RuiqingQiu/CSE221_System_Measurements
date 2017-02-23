	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_rdtsc
	.align	4, 0x90
_rdtsc:                                 ## @rdtsc
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
	movl	%edi, -4(%rbp)
	## InlineAsm Start
	rdtsc
	## InlineAsm End
	movl	%eax, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, %ecx
	shlq	$32, %rcx
	movl	-8(%rbp), %eax
	movl	%eax, %esi
	orq	%rsi, %rcx
	movq	%rcx, %rax
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_f0
	.align	4, 0x90
_f0:                                    ## @f0
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp3:
	.cfi_def_cfa_offset 16
Ltmp4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp5:
	.cfi_def_cfa_register %rbp
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_f1
	.align	4, 0x90
_f1:                                    ## @f1
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp6:
	.cfi_def_cfa_offset 16
Ltmp7:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp8:
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_f2
	.align	4, 0x90
_f2:                                    ## @f2
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp9:
	.cfi_def_cfa_offset 16
Ltmp10:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp11:
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_f3
	.align	4, 0x90
_f3:                                    ## @f3
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp12:
	.cfi_def_cfa_offset 16
Ltmp13:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp14:
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_f4
	.align	4, 0x90
_f4:                                    ## @f4
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp15:
	.cfi_def_cfa_offset 16
Ltmp16:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp17:
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	%ecx, -16(%rbp)
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_f5
	.align	4, 0x90
_f5:                                    ## @f5
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp18:
	.cfi_def_cfa_offset 16
Ltmp19:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp20:
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	%ecx, -16(%rbp)
	movl	%r8d, -20(%rbp)
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_f6
	.align	4, 0x90
_f6:                                    ## @f6
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp21:
	.cfi_def_cfa_offset 16
Ltmp22:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp23:
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	%ecx, -16(%rbp)
	movl	%r8d, -20(%rbp)
	movl	%r9d, -24(%rbp)
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_f7
	.align	4, 0x90
_f7:                                    ## @f7
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp24:
	.cfi_def_cfa_offset 16
Ltmp25:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp26:
	.cfi_def_cfa_register %rbp
	movl	16(%rbp), %eax
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	%ecx, -16(%rbp)
	movl	%r8d, -20(%rbp)
	movl	%r9d, -24(%rbp)
	movl	%eax, -28(%rbp)
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp27:
	.cfi_def_cfa_offset 16
Ltmp28:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp29:
	.cfi_def_cfa_register %rbp
	pushq	%rbx
	subq	$56, %rsp
Ltmp30:
	.cfi_offset %rbx, -24
	movl	$0, -12(%rbp)
	movl	$100, -52(%rbp)
	movl	$0, -56(%rbp)
LBB9_1:                                 ## =>This Inner Loop Header: Depth=1
	movl	-56(%rbp), %eax
	cmpl	-52(%rbp), %eax
	jge	LBB9_4
## BB#2:                                ##   in Loop: Header=BB9_1 Depth=1
	## InlineAsm Start
	cpuid
	## InlineAsm End
	## InlineAsm Start
	rdtsc
	## InlineAsm End
	movl	%eax, -36(%rbp)
	movl	%edx, -40(%rbp)
	callq	_f0
	## InlineAsm Start
	rdtsc
	## InlineAsm End
	movl	%eax, -44(%rbp)
	movl	%edx, -48(%rbp)
	## InlineAsm Start
	cpuid
	## InlineAsm End
	leaq	L_.str(%rip), %rdi
	movl	-40(%rbp), %esi
	movl	%esi, %eax
	shlq	$32, %rax
	movl	-36(%rbp), %esi
	movl	%esi, %ecx
	orq	%rcx, %rax
	movq	%rax, -24(%rbp)
	movl	-48(%rbp), %esi
	movl	%esi, %eax
	shlq	$32, %rax
	movl	-44(%rbp), %esi
	movl	%esi, %ecx
	orq	%rcx, %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	subq	-24(%rbp), %rax
	movq	%rax, %rsi
	movb	$0, %al
	callq	_printf
	movl	%eax, -60(%rbp)         ## 4-byte Spill
## BB#3:                                ##   in Loop: Header=BB9_1 Depth=1
	movl	-56(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -56(%rbp)
	jmp	LBB9_1
LBB9_4:
	movl	$1, %eax
	addq	$56, %rsp
	popq	%rbx
	popq	%rbp
	retq
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"function execution time is %llu clock cycles\n"


.subsections_via_symbols

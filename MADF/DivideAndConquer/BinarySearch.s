	.file	"BinarySearch.c"
	.text
	.def	_rdtsc;	.scl	3;	.type	32;	.endef
_rdtsc:
LFB18:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	.cfi_offset 7, -12
	.cfi_offset 6, -16
	.cfi_offset 3, -20
/APP
 # 9 ".\BinarySearch.c" 1
	rdtsc
 # 0 "" 2
/NO_APP
	movl	%eax, -20(%ebp)
	movl	%edx, -24(%ebp)
	movl	-24(%ebp), %eax
	movl	$0, %edx
	movl	%eax, %edx
	movl	$0, %eax
	movl	-20(%ebp), %esi
	movl	$0, %edi
	movl	%eax, -40(%ebp)
	movl	%edx, -36(%ebp)
	orl	%esi, %eax
	movl	%eax, %ecx
	movl	-36(%ebp), %eax
	orl	%edi, %eax
	movl	%eax, %ebx
	movl	%ecx, %eax
	movl	%ebx, %edx
	addl	$28, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%edi
	.cfi_restore 7
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE18:
	.section .rdata,"dr"
LC0:
	.ascii " %02d      %02d\12\0"
LC1:
	.ascii " %02d  %02d  %02d\12\0"
	.text
	.globl	_binarySearch
	.def	_binarySearch;	.scl	2;	.type	32;	.endef
_binarySearch:
LFB19:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	12(%ebp), %eax
	cmpl	16(%ebp), %eax
	jl	L4
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC0, (%esp)
	call	_printf
	movl	12(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	20(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L5
	movl	12(%ebp), %eax
	jmp	L6
L5:
	movl	$-1, %eax
	jmp	L6
L4:
	movl	12(%ebp), %edx
	movl	16(%ebp), %eax
	addl	%edx, %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	movl	%eax, -12(%ebp)
	movl	16(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC1, (%esp)
	call	_printf
	movl	-12(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	20(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L7
	movl	-12(%ebp), %eax
	jmp	L6
L7:
	movl	-12(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	20(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_strcmp
	testl	%eax, %eax
	jle	L8
	movl	-12(%ebp), %eax
	leal	-1(%eax), %edx
	movl	20(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	%edx, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_binarySearch
	jmp	L6
L8:
	movl	-12(%ebp), %eax
	leal	1(%eax), %edx
	movl	20(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	%edx, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_binarySearch
L6:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE19:
	.section .rdata,"dr"
LC2:
	.ascii "Enter string %d: \0"
LC3:
	.ascii "%s\0"
	.text
	.globl	_inputStrings
	.def	_inputStrings;	.scl	2;	.type	32;	.endef
_inputStrings:
LFB20:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$36, %esp
	.cfi_offset 3, -12
	movl	$0, -12(%ebp)
	jmp	L10
L11:
	movl	-12(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	leal	(%edx,%eax), %ebx
	movl	$100, (%esp)
	call	_malloc
	movl	%eax, (%ebx)
	movl	-12(%ebp), %eax
	addl	$1, %eax
	movl	%eax, 4(%esp)
	movl	$LC2, (%esp)
	call	_printf
	movl	-12(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, 4(%esp)
	movl	$LC3, (%esp)
	call	_scanf
	addl	$1, -12(%ebp)
L10:
	movl	-12(%ebp), %eax
	cmpl	12(%ebp), %eax
	jl	L11
	nop
	addl	$36, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE20:
	.globl	_freeStrings
	.def	_freeStrings;	.scl	2;	.type	32;	.endef
_freeStrings:
LFB21:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	$0, -12(%ebp)
	jmp	L13
L14:
	movl	-12(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, (%esp)
	call	_free
	addl	$1, -12(%ebp)
L13:
	movl	-12(%ebp), %eax
	cmpl	12(%ebp), %eax
	jl	L14
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_free
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE21:
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC4:
	.ascii "\12Menu:\0"
LC5:
	.ascii "1. Input strings\0"
LC6:
	.ascii "2. Search for a string\0"
LC7:
	.ascii "3. Exit\0"
LC8:
	.ascii "Enter your choice: \0"
LC9:
	.ascii "%d\0"
LC10:
	.ascii "Enter number of strings: \0"
LC11:
	.ascii "Please input strings first.\0"
LC12:
	.ascii "Enter string to search: \0"
LC13:
	.ascii "\12Low Mid High\0"
LC14:
	.ascii "String found at index %d\12\0"
LC15:
	.ascii "String not found\0"
	.def	___udivdi3;	.scl	2;	.type	32;	.endef
	.align 4
LC16:
	.ascii "Time taken for binary search: %lu seconds\12\12\0"
LC17:
	.ascii "Exiting...\0"
	.align 4
LC18:
	.ascii "Invalid choice. Please try again.\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB22:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$192, %esp
	call	___main
	movl	$0, 188(%esp)
L27:
	movl	$LC4, (%esp)
	call	_puts
	movl	$LC5, (%esp)
	call	_puts
	movl	$LC6, (%esp)
	call	_puts
	movl	$LC7, (%esp)
	call	_puts
	movl	$LC8, (%esp)
	call	_printf
	leal	52(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$LC9, (%esp)
	call	_scanf
	movl	52(%esp), %eax
	cmpl	$2, %eax
	je	L17
	cmpl	$3, %eax
	je	L18
	cmpl	$1, %eax
	jne	L29
	cmpl	$0, 188(%esp)
	je	L20
	movl	156(%esp), %eax
	movl	%eax, 4(%esp)
	movl	188(%esp), %eax
	movl	%eax, (%esp)
	call	_freeStrings
L20:
	movl	$LC10, (%esp)
	call	_printf
	leal	156(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$LC9, (%esp)
	call	_scanf
	movl	156(%esp), %eax
	sall	$2, %eax
	movl	%eax, (%esp)
	call	_malloc
	movl	%eax, 188(%esp)
	movl	156(%esp), %eax
	movl	%eax, 4(%esp)
	movl	188(%esp), %eax
	movl	%eax, (%esp)
	call	_inputStrings
	jmp	L21
L17:
	cmpl	$0, 188(%esp)
	jne	L22
	movl	$LC11, (%esp)
	call	_puts
	jmp	L21
L22:
	movl	$LC12, (%esp)
	call	_printf
	leal	56(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$LC3, (%esp)
	call	_scanf
	movl	$LC13, (%esp)
	call	_puts
	call	_rdtsc
	movl	%eax, 176(%esp)
	movl	%edx, 180(%esp)
	movl	156(%esp), %eax
	leal	-1(%eax), %edx
	leal	56(%esp), %eax
	movl	%eax, 12(%esp)
	movl	%edx, 8(%esp)
	movl	$0, 4(%esp)
	movl	188(%esp), %eax
	movl	%eax, (%esp)
	call	_binarySearch
	movl	%eax, 172(%esp)
	call	_rdtsc
	movl	%eax, 160(%esp)
	movl	%edx, 164(%esp)
	cmpl	$-1, 172(%esp)
	je	L24
	movl	172(%esp), %eax
	addl	$1, %eax
	movl	%eax, 4(%esp)
	movl	$LC14, (%esp)
	call	_printf
	jmp	L25
L24:
	movl	$LC15, (%esp)
	call	_puts
L25:
	movl	160(%esp), %eax
	movl	164(%esp), %edx
	subl	176(%esp), %eax
	sbbl	180(%esp), %edx
	movl	$1000, 8(%esp)
	movl	$0, 12(%esp)
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	___udivdi3
	movl	%eax, 4(%esp)
	movl	%edx, 8(%esp)
	movl	$LC16, (%esp)
	call	_printf
	jmp	L21
L18:
	cmpl	$0, 188(%esp)
	je	L26
	movl	156(%esp), %eax
	movl	%eax, 4(%esp)
	movl	188(%esp), %eax
	movl	%eax, (%esp)
	call	_freeStrings
L26:
	movl	$LC17, (%esp)
	call	_puts
	jmp	L21
L29:
	movl	$LC18, (%esp)
	call	_puts
L21:
	movl	52(%esp), %eax
	cmpl	$3, %eax
	jne	L27
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE22:
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
	.def	_printf;	.scl	2;	.type	32;	.endef
	.def	_strcmp;	.scl	2;	.type	32;	.endef
	.def	_malloc;	.scl	2;	.type	32;	.endef
	.def	_scanf;	.scl	2;	.type	32;	.endef
	.def	_free;	.scl	2;	.type	32;	.endef
	.def	_puts;	.scl	2;	.type	32;	.endef

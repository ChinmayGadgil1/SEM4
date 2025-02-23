	.file	"MultiStageGraph.c"
	.comm	_n, 4, 2
	.comm	_k, 4, 2
	.section .rdata,"dr"
LC0:
	.ascii "Enter number of vertices: \0"
LC1:
	.ascii "%d\0"
LC2:
	.ascii "Enter number of stages:\0"
	.align 4
LC3:
	.ascii "Enter edge %d((-1 -1) to quit): \0"
LC4:
	.ascii "%d%d\0"
LC5:
	.ascii "Invalid edge\0"
LC6:
	.ascii "Enter cost: \0"
	.text
	.globl	_create
	.def	_create;	.scl	2;	.type	32;	.endef
_create:
LFB15:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$56, %esp
	movl	$LC0, (%esp)
	call	_printf
	movl	$_n, 4(%esp)
	movl	$LC1, (%esp)
	call	_scanf
	movl	_n, %eax
	leal	-1(%eax), %edx
	movl	_n, %eax
	imull	%edx, %eax
	movl	%eax, -24(%ebp)
	movl	$LC2, (%esp)
	call	_printf
	movl	$_k, 4(%esp)
	movl	$LC1, (%esp)
	call	_scanf
	movl	$1, -12(%ebp)
	jmp	L2
L5:
	movl	$1, -16(%ebp)
	jmp	L3
L4:
	movl	-12(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$4, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	addl	%eax, %edx
	movl	-16(%ebp), %eax
	movl	$2147483647, (%edx,%eax,4)
	addl	$1, -16(%ebp)
L3:
	movl	_n, %eax
	cmpl	%eax, -16(%ebp)
	jle	L4
	addl	$1, -12(%ebp)
L2:
	movl	_n, %eax
	cmpl	%eax, -12(%ebp)
	jle	L5
	movl	$1, -20(%ebp)
	jmp	L6
L12:
	movl	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC3, (%esp)
	call	_printf
	leal	-32(%ebp), %eax
	movl	%eax, 8(%esp)
	leal	-28(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC4, (%esp)
	call	_scanf
	movl	-28(%ebp), %eax
	cmpl	$-1, %eax
	jne	L7
	movl	-32(%ebp), %eax
	cmpl	$-1, %eax
	je	L13
L7:
	movl	-28(%ebp), %edx
	movl	_n, %eax
	cmpl	%eax, %edx
	jg	L9
	movl	-32(%ebp), %edx
	movl	_n, %eax
	cmpl	%eax, %edx
	jg	L9
	movl	-28(%ebp), %eax
	testl	%eax, %eax
	jle	L9
	movl	-32(%ebp), %eax
	testl	%eax, %eax
	jg	L10
L9:
	movl	$LC5, (%esp)
	call	_puts
	subl	$1, -20(%ebp)
	jmp	L11
L10:
	movl	$LC6, (%esp)
	call	_printf
	leal	-36(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC1, (%esp)
	call	_scanf
	movl	-28(%ebp), %eax
	movl	%eax, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$4, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	leal	(%edx,%eax), %ecx
	movl	-32(%ebp), %eax
	movl	-36(%ebp), %edx
	movl	%edx, (%ecx,%eax,4)
L11:
	addl	$1, -20(%ebp)
L6:
	movl	-20(%ebp), %eax
	cmpl	-24(%ebp), %eax
	jle	L12
	jmp	L8
L13:
	nop
L8:
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE15:
	.globl	_selectVertex
	.def	_selectVertex;	.scl	2;	.type	32;	.endef
_selectVertex:
LFB16:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$16, %esp
	.cfi_offset 3, -12
	movl	12(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, -12(%ebp)
	jmp	L15
L17:
	movl	12(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$4, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	addl	%eax, %edx
	movl	-12(%ebp), %eax
	movl	(%edx,%eax,4), %eax
	cmpl	$2147483647, %eax
	je	L16
	movl	12(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$4, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	addl	%eax, %edx
	movl	-12(%ebp), %eax
	movl	(%edx,%eax,4), %edx
	movl	-12(%ebp), %eax
	leal	0(,%eax,4), %ecx
	movl	16(%ebp), %eax
	addl	%ecx, %eax
	movl	(%eax), %eax
	leal	(%edx,%eax), %ecx
	movl	12(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$4, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	addl	%eax, %edx
	movl	-8(%ebp), %eax
	movl	(%edx,%eax,4), %edx
	movl	-8(%ebp), %eax
	leal	0(,%eax,4), %ebx
	movl	16(%ebp), %eax
	addl	%ebx, %eax
	movl	(%eax), %eax
	addl	%edx, %eax
	cmpl	%eax, %ecx
	jge	L16
	movl	-12(%ebp), %eax
	movl	%eax, -8(%ebp)
L16:
	addl	$1, -12(%ebp)
L15:
	movl	_n, %eax
	cmpl	%eax, -12(%ebp)
	jle	L17
	movl	-8(%ebp), %eax
	addl	$16, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE16:
	.section .rdata,"dr"
LC8:
	.ascii "Cost(%02d,%02d)=%02d  \0"
LC9:
	.ascii "r(%02d,%02d)=%02d\12\0"
LC10:
	.ascii "Shortest path is: \0"
LC11:
	.ascii "->%d\0"
LC12:
	.ascii "\12Mincost=%d\12\0"
	.text
	.globl	_Fgraph
	.def	_Fgraph;	.scl	2;	.type	32;	.endef
_Fgraph:
LFB17:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%edi
	subl	$228, %esp
	.cfi_offset 7, -12
	leal	-116(%ebp), %edx
	movl	$0, %eax
	movl	$20, %ecx
	movl	%edx, %edi
	rep stosl
	movl	$2147483647, -116(%ebp)
	leal	-196(%ebp), %edx
	movl	$0, %eax
	movl	$20, %ecx
	movl	%edx, %edi
	rep stosl
	movl	$0, -28(%ebp)
	movl	16(%ebp), %eax
	movl	$0, -116(%ebp,%eax,4)
	fildl	12(%ebp)
	movl	12(%ebp), %eax
	leal	-1(%eax), %edi
	movl	$1, %eax
	cltd
	idivl	%edi
	movl	%eax, -208(%ebp)
	fildl	-208(%ebp)
	fsubrp	%st, %st(1)
	fstps	-12(%ebp)
	movl	12(%ebp), %eax
	subl	$1, %eax
	movl	%eax, -32(%ebp)
	movl	16(%ebp), %eax
	subl	$1, %eax
	movl	%eax, -16(%ebp)
	jmp	L20
L21:
	flds	-12(%ebp)
	flds	LC7
	fsubrp	%st, %st(1)
	fstps	-12(%ebp)
	flds	-12(%ebp)
	fnstcw	-202(%ebp)
	movzwl	-202(%ebp), %eax
	movb	$12, %ah
	movw	%ax, -204(%ebp)
	fldcw	-204(%ebp)
	fistpl	-32(%ebp)
	fldcw	-202(%ebp)
	leal	-116(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_selectVertex
	movl	%eax, -36(%ebp)
	movl	-16(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$4, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	addl	%eax, %edx
	movl	-36(%ebp), %eax
	movl	(%edx,%eax,4), %edx
	movl	-36(%ebp), %eax
	movl	-116(%ebp,%eax,4), %eax
	addl	%eax, %edx
	movl	-16(%ebp), %eax
	movl	%edx, -116(%ebp,%eax,4)
	movl	-16(%ebp), %eax
	movl	-116(%ebp,%eax,4), %eax
	movl	%eax, 12(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-32(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC8, (%esp)
	call	_printf
	movl	-36(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-32(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC9, (%esp)
	call	_printf
	movl	-16(%ebp), %eax
	movl	-36(%ebp), %edx
	movl	%edx, -196(%ebp,%eax,4)
	subl	$1, -16(%ebp)
L20:
	cmpl	$0, -16(%ebp)
	jg	L21
	movl	20(%ebp), %eax
	addl	$4, %eax
	movl	$1, (%eax)
	movl	12(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	20(%ebp), %eax
	addl	%eax, %edx
	movl	16(%ebp), %eax
	movl	%eax, (%edx)
	movl	$2, -20(%ebp)
	jmp	L22
L23:
	movl	-20(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	20(%ebp), %eax
	addl	%eax, %edx
	movl	-20(%ebp), %eax
	addl	$1073741823, %eax
	leal	0(,%eax,4), %ecx
	movl	20(%ebp), %eax
	addl	%ecx, %eax
	movl	(%eax), %eax
	movl	-196(%ebp,%eax,4), %eax
	movl	%eax, (%edx)
	addl	$1, -20(%ebp)
L22:
	movl	12(%ebp), %eax
	subl	$1, %eax
	cmpl	-20(%ebp), %eax
	jge	L23
	movl	$LC10, (%esp)
	call	_printf
	movl	20(%ebp), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	movl	%eax, 4(%esp)
	movl	$LC1, (%esp)
	call	_printf
	movl	$2, -24(%ebp)
	jmp	L24
L25:
	movl	-24(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	20(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, 4(%esp)
	movl	$LC11, (%esp)
	call	_printf
	addl	$1, -24(%ebp)
L24:
	movl	-24(%ebp), %eax
	cmpl	12(%ebp), %eax
	jle	L25
	movl	-112(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC12, (%esp)
	call	_printf
	nop
	addl	$228, %esp
	popl	%edi
	.cfi_restore 7
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE17:
	.globl	_selectVertexB
	.def	_selectVertexB;	.scl	2;	.type	32;	.endef
_selectVertexB:
LFB18:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	$2147483647, -4(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	$1, -12(%ebp)
	jmp	L27
L29:
	movl	-12(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$4, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	addl	%eax, %edx
	movl	12(%ebp), %eax
	movl	(%edx,%eax,4), %eax
	cmpl	$2147483647, %eax
	je	L28
	movl	-12(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	16(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	cmpl	$2147483647, %eax
	je	L28
	movl	-12(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$4, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	addl	%eax, %edx
	movl	12(%ebp), %eax
	movl	(%edx,%eax,4), %edx
	movl	-12(%ebp), %eax
	leal	0(,%eax,4), %ecx
	movl	16(%ebp), %eax
	addl	%ecx, %eax
	movl	(%eax), %eax
	addl	%edx, %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	cmpl	-4(%ebp), %eax
	jge	L28
	movl	-16(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, -8(%ebp)
L28:
	addl	$1, -12(%ebp)
L27:
	movl	-12(%ebp), %eax
	cmpl	12(%ebp), %eax
	jl	L29
	movl	-8(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE18:
	.globl	_Bgraph
	.def	_Bgraph;	.scl	2;	.type	32;	.endef
_Bgraph:
LFB19:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$232, %esp
	fld1
	fstps	-12(%ebp)
	movl	$1, -32(%ebp)
	movl	$0, -16(%ebp)
	jmp	L32
L33:
	movl	-16(%ebp), %eax
	movl	$2147483647, -116(%ebp,%eax,4)
	movl	-16(%ebp), %eax
	movl	$0, -196(%ebp,%eax,4)
	addl	$1, -16(%ebp)
L32:
	cmpl	$19, -16(%ebp)
	jle	L33
	movl	$0, -112(%ebp)
	movl	$2, -20(%ebp)
	jmp	L34
L35:
	flds	-12(%ebp)
	flds	LC7
	faddp	%st, %st(1)
	fstps	-12(%ebp)
	flds	-12(%ebp)
	fnstcw	-202(%ebp)
	movzwl	-202(%ebp), %eax
	movb	$12, %ah
	movw	%ax, -204(%ebp)
	fldcw	-204(%ebp)
	fistpl	-32(%ebp)
	fldcw	-202(%ebp)
	leal	-116(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_selectVertexB
	movl	%eax, -36(%ebp)
	movl	-36(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$4, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	addl	%eax, %edx
	movl	-20(%ebp), %eax
	movl	(%edx,%eax,4), %edx
	movl	-36(%ebp), %eax
	movl	-116(%ebp,%eax,4), %eax
	addl	%eax, %edx
	movl	-20(%ebp), %eax
	movl	%edx, -116(%ebp,%eax,4)
	movl	-20(%ebp), %eax
	movl	-36(%ebp), %edx
	movl	%edx, -196(%ebp,%eax,4)
	movl	-20(%ebp), %eax
	movl	-116(%ebp,%eax,4), %eax
	movl	%eax, 12(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-32(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC8, (%esp)
	call	_printf
	movl	-36(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-32(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC9, (%esp)
	call	_printf
	addl	$1, -20(%ebp)
L34:
	movl	-20(%ebp), %eax
	cmpl	16(%ebp), %eax
	jle	L35
	movl	20(%ebp), %eax
	addl	$4, %eax
	movl	$1, (%eax)
	movl	12(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	20(%ebp), %eax
	addl	%eax, %edx
	movl	16(%ebp), %eax
	movl	%eax, (%edx)
	movl	12(%ebp), %eax
	subl	$1, %eax
	movl	%eax, -24(%ebp)
	jmp	L36
L37:
	movl	-24(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	20(%ebp), %eax
	addl	%eax, %edx
	movl	-24(%ebp), %eax
	addl	$1, %eax
	leal	0(,%eax,4), %ecx
	movl	20(%ebp), %eax
	addl	%ecx, %eax
	movl	(%eax), %eax
	movl	-196(%ebp,%eax,4), %eax
	movl	%eax, (%edx)
	subl	$1, -24(%ebp)
L36:
	cmpl	$1, -24(%ebp)
	jg	L37
	movl	$LC10, (%esp)
	call	_printf
	movl	20(%ebp), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	movl	%eax, 4(%esp)
	movl	$LC1, (%esp)
	call	_printf
	movl	$2, -28(%ebp)
	jmp	L38
L39:
	movl	-28(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	20(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, 4(%esp)
	movl	$LC11, (%esp)
	call	_printf
	addl	$1, -28(%ebp)
L38:
	movl	-28(%ebp), %eax
	cmpl	12(%ebp), %eax
	jle	L39
	movl	16(%ebp), %eax
	movl	-116(%ebp,%eax,4), %eax
	movl	%eax, 4(%esp)
	movl	$LC12, (%esp)
	call	_printf
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE19:
	.def	___main;	.scl	2;	.type	32;	.endef
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB20:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%edi
	andl	$-16, %esp
	subl	$2608, %esp
	.cfi_offset 7, -12
	call	___main
	leal	1000(%esp), %edx
	movl	$0, %eax
	movl	$400, %ecx
	movl	%edx, %edi
	rep stosl
	movl	$2147483647, 1000(%esp)
	leal	20(%esp), %edx
	movl	$0, %eax
	movl	$225, %ecx
	movl	%edx, %edi
	rep stosl
	movl	$2147483647, 20(%esp)
	movl	$2147483647, 80(%esp)
	movl	$2147483647, 84(%esp)
	movl	$9, 88(%esp)
	movl	$8, 92(%esp)
	movl	$6, 96(%esp)
	movl	$7, 100(%esp)
	movl	$2147483647, 104(%esp)
	movl	$2147483647, 108(%esp)
	movl	$2147483647, 112(%esp)
	movl	$2147483647, 116(%esp)
	movl	$2147483647, 120(%esp)
	movl	$2147483647, 124(%esp)
	movl	$2147483647, 128(%esp)
	movl	$2147483647, 132(%esp)
	movl	$2147483647, 136(%esp)
	movl	$2147483647, 140(%esp)
	movl	$2147483647, 144(%esp)
	movl	$2147483647, 148(%esp)
	movl	$2147483647, 152(%esp)
	movl	$2147483647, 156(%esp)
	movl	$2147483647, 160(%esp)
	movl	$10, 164(%esp)
	movl	$11, 168(%esp)
	movl	$12, 172(%esp)
	movl	$2147483647, 176(%esp)
	movl	$2147483647, 180(%esp)
	movl	$2147483647, 184(%esp)
	movl	$2147483647, 188(%esp)
	movl	$2147483647, 192(%esp)
	movl	$2147483647, 196(%esp)
	movl	$2147483647, 200(%esp)
	movl	$2147483647, 204(%esp)
	movl	$2147483647, 208(%esp)
	movl	$2147483647, 212(%esp)
	movl	$2147483647, 216(%esp)
	movl	$2147483647, 220(%esp)
	movl	$15, 224(%esp)
	movl	$2147483647, 228(%esp)
	movl	$14, 232(%esp)
	movl	$13, 236(%esp)
	movl	$2147483647, 240(%esp)
	movl	$2147483647, 244(%esp)
	movl	$2147483647, 248(%esp)
	movl	$2147483647, 252(%esp)
	movl	$2147483647, 256(%esp)
	movl	$2147483647, 260(%esp)
	movl	$2147483647, 264(%esp)
	movl	$2147483647, 268(%esp)
	movl	$2147483647, 272(%esp)
	movl	$2147483647, 276(%esp)
	movl	$2147483647, 280(%esp)
	movl	$2147483647, 284(%esp)
	movl	$10, 288(%esp)
	movl	$11, 292(%esp)
	movl	$12, 296(%esp)
	movl	$2147483647, 300(%esp)
	movl	$2147483647, 304(%esp)
	movl	$2147483647, 308(%esp)
	movl	$2147483647, 312(%esp)
	movl	$2147483647, 316(%esp)
	movl	$2147483647, 320(%esp)
	movl	$2147483647, 324(%esp)
	movl	$2147483647, 328(%esp)
	movl	$2147483647, 332(%esp)
	movl	$2147483647, 336(%esp)
	movl	$2147483647, 340(%esp)
	movl	$8, 344(%esp)
	movl	$9, 348(%esp)
	movl	$2147483647, 352(%esp)
	movl	$10, 356(%esp)
	movl	$2147483647, 360(%esp)
	movl	$2147483647, 364(%esp)
	movl	$2147483647, 368(%esp)
	movl	$2147483647, 372(%esp)
	movl	$2147483647, 376(%esp)
	movl	$2147483647, 380(%esp)
	movl	$2147483647, 384(%esp)
	movl	$2147483647, 388(%esp)
	movl	$2147483647, 392(%esp)
	movl	$2147483647, 396(%esp)
	movl	$2147483647, 400(%esp)
	movl	$2147483647, 404(%esp)
	movl	$2147483647, 408(%esp)
	movl	$2147483647, 412(%esp)
	movl	$2147483647, 416(%esp)
	movl	$5, 420(%esp)
	movl	$6, 424(%esp)
	movl	$2147483647, 428(%esp)
	movl	$7, 432(%esp)
	movl	$2147483647, 436(%esp)
	movl	$2147483647, 440(%esp)
	movl	$2147483647, 444(%esp)
	movl	$2147483647, 448(%esp)
	movl	$2147483647, 452(%esp)
	movl	$2147483647, 456(%esp)
	movl	$2147483647, 460(%esp)
	movl	$2147483647, 464(%esp)
	movl	$2147483647, 468(%esp)
	movl	$2147483647, 472(%esp)
	movl	$2147483647, 476(%esp)
	movl	$8, 480(%esp)
	movl	$9, 484(%esp)
	movl	$7, 488(%esp)
	movl	$2147483647, 492(%esp)
	movl	$2147483647, 496(%esp)
	movl	$2147483647, 500(%esp)
	movl	$2147483647, 504(%esp)
	movl	$2147483647, 508(%esp)
	movl	$2147483647, 512(%esp)
	movl	$2147483647, 516(%esp)
	movl	$2147483647, 520(%esp)
	movl	$2147483647, 524(%esp)
	movl	$2147483647, 528(%esp)
	movl	$2147483647, 532(%esp)
	movl	$2147483647, 536(%esp)
	movl	$2147483647, 540(%esp)
	movl	$6, 544(%esp)
	movl	$7, 548(%esp)
	movl	$8, 552(%esp)
	movl	$2147483647, 556(%esp)
	movl	$2147483647, 560(%esp)
	movl	$2147483647, 564(%esp)
	movl	$2147483647, 568(%esp)
	movl	$2147483647, 572(%esp)
	movl	$2147483647, 576(%esp)
	movl	$2147483647, 580(%esp)
	movl	$2147483647, 584(%esp)
	movl	$2147483647, 588(%esp)
	movl	$2147483647, 592(%esp)
	movl	$2147483647, 596(%esp)
	movl	$5, 600(%esp)
	movl	$2147483647, 604(%esp)
	movl	$8, 608(%esp)
	movl	$6, 612(%esp)
	movl	$2147483647, 616(%esp)
	movl	$2147483647, 620(%esp)
	movl	$2147483647, 624(%esp)
	movl	$2147483647, 628(%esp)
	movl	$2147483647, 632(%esp)
	movl	$2147483647, 636(%esp)
	movl	$2147483647, 640(%esp)
	movl	$2147483647, 644(%esp)
	movl	$2147483647, 648(%esp)
	movl	$2147483647, 652(%esp)
	movl	$2147483647, 656(%esp)
	movl	$2147483647, 660(%esp)
	movl	$2147483647, 664(%esp)
	movl	$2147483647, 668(%esp)
	movl	$2147483647, 672(%esp)
	movl	$8, 676(%esp)
	movl	$2147483647, 680(%esp)
	movl	$2147483647, 684(%esp)
	movl	$2147483647, 688(%esp)
	movl	$2147483647, 692(%esp)
	movl	$2147483647, 696(%esp)
	movl	$2147483647, 700(%esp)
	movl	$2147483647, 704(%esp)
	movl	$2147483647, 708(%esp)
	movl	$2147483647, 712(%esp)
	movl	$2147483647, 716(%esp)
	movl	$2147483647, 720(%esp)
	movl	$2147483647, 724(%esp)
	movl	$2147483647, 728(%esp)
	movl	$2147483647, 732(%esp)
	movl	$9, 736(%esp)
	movl	$2147483647, 740(%esp)
	movl	$2147483647, 744(%esp)
	movl	$2147483647, 748(%esp)
	movl	$2147483647, 752(%esp)
	movl	$2147483647, 756(%esp)
	movl	$2147483647, 760(%esp)
	movl	$2147483647, 764(%esp)
	movl	$2147483647, 768(%esp)
	movl	$2147483647, 772(%esp)
	movl	$2147483647, 776(%esp)
	movl	$2147483647, 780(%esp)
	movl	$2147483647, 784(%esp)
	movl	$2147483647, 788(%esp)
	movl	$2147483647, 792(%esp)
	movl	$8, 796(%esp)
	movl	$2147483647, 800(%esp)
	movl	$2147483647, 804(%esp)
	movl	$2147483647, 808(%esp)
	movl	$2147483647, 812(%esp)
	movl	$2147483647, 816(%esp)
	movl	$2147483647, 820(%esp)
	movl	$2147483647, 824(%esp)
	movl	$2147483647, 828(%esp)
	movl	$2147483647, 832(%esp)
	movl	$2147483647, 836(%esp)
	movl	$2147483647, 840(%esp)
	movl	$2147483647, 844(%esp)
	movl	$2147483647, 848(%esp)
	movl	$2147483647, 852(%esp)
	movl	$7, 856(%esp)
	movl	$2147483647, 860(%esp)
	movl	$2147483647, 864(%esp)
	movl	$2147483647, 868(%esp)
	movl	$2147483647, 872(%esp)
	movl	$2147483647, 876(%esp)
	movl	$2147483647, 880(%esp)
	movl	$2147483647, 884(%esp)
	movl	$2147483647, 888(%esp)
	movl	$2147483647, 892(%esp)
	movl	$2147483647, 896(%esp)
	movl	$2147483647, 900(%esp)
	movl	$2147483647, 904(%esp)
	movl	$2147483647, 908(%esp)
	movl	$2147483647, 912(%esp)
	movl	$2147483647, 916(%esp)
	movl	$14, _n
	movl	$0, 2604(%esp)
	jmp	L41
L44:
	movl	$0, 2600(%esp)
	jmp	L42
L43:
	movl	2604(%esp), %edx
	movl	%edx, %eax
	sall	$4, %eax
	subl	%edx, %eax
	movl	2600(%esp), %edx
	addl	%edx, %eax
	movl	20(%esp,%eax,4), %ecx
	movl	2604(%esp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	2600(%esp), %edx
	addl	%edx, %eax
	movl	%ecx, 1000(%esp,%eax,4)
	addl	$1, 2600(%esp)
L42:
	cmpl	$14, 2600(%esp)
	jle	L43
	addl	$1, 2604(%esp)
L41:
	cmpl	$14, 2604(%esp)
	jle	L44
	movl	$10, (%esp)
	call	_putchar
	leal	920(%esp), %eax
	movl	%eax, 12(%esp)
	movl	$14, 8(%esp)
	movl	$5, 4(%esp)
	leal	1000(%esp), %eax
	movl	%eax, (%esp)
	call	_Bgraph
	movl	$0, %eax
	movl	-4(%ebp), %edi
	leave
	.cfi_restore 5
	.cfi_restore 7
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE20:
	.section .rdata,"dr"
	.align 4
LC7:
	.long	1048576000
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
	.def	_printf;	.scl	2;	.type	32;	.endef
	.def	_scanf;	.scl	2;	.type	32;	.endef
	.def	_puts;	.scl	2;	.type	32;	.endef
	.def	_putchar;	.scl	2;	.type	32;	.endef

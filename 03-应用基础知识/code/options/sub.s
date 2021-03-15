	.file	"sub.c"
	.text
	.section .rdata,"dr"
.LC0:
	.ascii "sub fun!\0"
	.text
	.globl	sub_fun
	.def	sub_fun;	.scl	2;	.type	32;	.endef
	.seh_proc	sub_fun
sub_fun:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	leaq	.LC0(%rip), %rcx
	call	puts
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	puts;	.scl	2;	.type	32;	.endef

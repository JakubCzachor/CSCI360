func:
	pushq	%rbp
	moveq	%rsp, %rbp
	doing arritmetic

	popq	%rbp
	ret
main:
	pushq	%rbp
	moveq	%rsp, %rbp
	doing arritmetic

	calling function func();
	doing arritmetic

	popq	%rbp
	ret

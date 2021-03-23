func:
	pushq	%rbp
	moveq	%rsp, %rbp
	declare variables here
	doing arritmetic

	popq	%rbp
	ret
main:
	pushq	%rbp
	moveq	%rsp, %rbp
	declare variables here
	doing arritmetic

	declare variables here
	declare variables here
	calling function func();
	doing arritmetic

	popq	%rbp
	ret

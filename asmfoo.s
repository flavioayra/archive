//
// h4 bullshits 
//
	.section .data

string:
	.ascii "mistah lova lova,hummmmmmmmmm\n"

string_len:
	.long	. - string

	.section .text
	.globl _start
_start:
	pushl 	%ebp
	movl	%esp, %ebp

	// mov o esp 8 bytes pra frente pra guardar $string e $stringlen
	// antes (na stack)
	addl	$8, %esp
	
	// bota string e string_len na stack e chama print_shit
	movl	$string, (%ebp)
	movl	$string_len, 4(%ebp)
	call 	print_shit

	// exit(0)
	xorl	%eax, %eax
	incl	%eax
	xorl	%ebx, %ebx
	int	$0x80
	
print_shit:	.type @function
	// syscal write(fd, buff, buff_len)
	movl	$0x4, %eax
	
	// ebx = 1
	xorl	%ebx, %ebx
	incl	%ebx
	
	// ecx = string
	movl	(%ebp), %ecx

	// edx = string_len
	movl	4(%ebp), %edx
	
	// passa pro kernel
	int 	$0x80
	
	// retorna
	ret

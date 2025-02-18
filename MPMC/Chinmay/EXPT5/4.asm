section .data
	msg db ' ',10
	msgLen equ $-msg
	msg1 db 'Number 1: '
	msg1Len equ $-msg1
	msg2 db 'Number 2: '
	msg2Len equ $-msg2
	msg3 db 'Sum: '
	msg3Len equ $-msg3
	msg4 db 'Difference: '
	msg4Len equ $-msg4
	msg5 db 'Product: '
	msg5Len equ $-msg5
	msg6 db 'Quotient: '
	msg6Len equ $-msg6
	msg7 db 'Remainder: '
	msg7Len equ $-msg7
	menu db 'Menu:', 10, '1. Add', 10, '2. Subtract', 10, '3. Multiply', 10, '4. Divide', 10, '5. Exit', 10, 'Select an option: ', 0
    menuLen equ $ - menu
    nl db 10
    nll equ $-nl
	
%macro writesystem 2
mov eax,4
mov ebx,1
mov ecx, %1
mov edx, %2
int 80h
%endmacro

%macro readsystem 2
mov eax,3
mov ebx,2
mov ecx,%1
mov edx,%2
int 80h
%endmacro

%macro addition 2
mov eax, [num1]
sub eax, '0'
mov ebx, [num2]
sub ebx, '0'
add eax, ebx
add eax, '0'
mov [sum], eax
%endmacro

%macro subtraction 2
mov eax, [num1]
sub eax, '0'
mov ebx, [num2]
sub ebx, '0'
sub eax, ebx
add eax, '0'
mov [diff], eax
%endmacro

%macro multiplication 2
mov eax, [num1]
sub eax, '0'
mov ebx, [num2]
sub ebx, '0'
mul ebx
add eax, '0'
mov [prod], al
%endmacro

%macro division 2
mov al, [num1]
sub al, '0'
mov bl, [num2]
sub bl, '0'
div bl
add al, '0'
mov [quot], al
add ah, '0'
mov [rem], ah
%endmacro

section .bss
	num1 RESB 5
	num2 RESB 5
	sum RESB 5
	diff RESB 5
	prod RESB 5
	quot RESB 5
	rem RESB 5
	option RESB 5
section .text
global _start
_start:
writesystem nl,nll
writesystem msg1,msg1Len
readsystem num1,5
writesystem msg2,msg2Len
readsystem num2,5
	writesystem menu, menuLen
    readsystem option, 5
    
    cmp byte [option], '1'
    je add_numbers
    cmp byte [option], '2'
    je subtract_numbers
    cmp byte [option], '3'
    je multiply_numbers
    cmp byte [option], '4'
    je divide_numbers
    cmp byte [option], '5'
    je exit_program
    
    add_numbers:
    		addition num1,num2
    		writesystem sum,5
    		jmp _start
    	subtract_numbers:
    		subtraction num1,num2
    		writesystem diff,5
			jmp _start
    	multiply_numbers:
    		multiplication num1,num2
    		writesystem prod,5
			jmp _start
    	divide_numbers:
		division num1,num2
		writesystem quot,5
		writesystem nl,nll
		writesystem rem,5
		jmp _start
exit_program:
mov eax, 1
mov ebx, 0
int 80h 

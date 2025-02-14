section .data
    msg1 db "Enter first number: ", 0
    msg2 db "Enter second number: ", 0
    msg3 db "Enter third number: ", 0
    msg_smallest db "First number is smallest", 10
    msg_second db "Second number is smallest", 10
    msg_third db "Third number is smallest", 10
    msg_equal db "All numbers are equal", 10
    
      msg1l equ $-msg1
    msg2l equ $-msg2
    msg3l equ $-msg3
    msg_smallestl equ $-msg_smallest
    msg_secondl equ $-msg_second
    msg_thirdl equ $-msg_third
    msg_equall equ $-msg_equal

%macro print 2
    mov eax, 4
    mov ebx, 1
    mov ecx, %1
    mov edx, %2
    int 0x80
%endmacro

%macro input 2
    mov eax, 3
    mov ebx, 2
    mov ecx, %1
    mov edx, %2
    int 0x80
%endmacro

%macro exit 0
    mov eax, 1
    mov ebx, 0
    int 0x80
%endmacro

section .bss
    num1 resb 2
    num2 resb 2
    num3 resb 2

section .text
    global _start

_start:
    print msg1,msg1l
    input num1, 2
    
    print msg2,msg2l
    input num2, 2
    
    print msg3,msg3l
    input num3, 2
    
    mov al, [num1]
    mov bl, [num2]
    mov cl, [num3]
    sub al, '0'    
    sub bl, '0'
    sub cl, '0'
    
    
    cmp al, bl
    jne check_lesser
    cmp bl, cl
    jne check_lesser
    print msg_equal,msg_equall
    jmp exit_prog

check_lesser:
    
    cmp al, bl
    jg check_second
    cmp al, cl
    jg check_third
    print msg_smallest,msg_smallestl
    jmp exit_prog

check_second:
    
    cmp bl, cl
    jg third_smallest
    print msg_second,msg_secondl
    jmp exit_prog

check_third:
    cmp cl, bl
    jg second_smallest
    print msg_third,msg_thirdl
    jmp exit_prog

second_smallest:
    print msg_second,msg_secondl
    jmp exit_prog

third_smallest:
    print msg_third,msg_thirdl
    
exit_prog:
    exit

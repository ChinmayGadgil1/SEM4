section .data
    msg1 db "Enter first number: ", 0
    msg2 db "Enter second number: ", 0
    msg3 db "Enter third number: ", 0
    msg_greatest db "First number is greatest", 10
    msg_second db "Second number is greatest", 10
    msg_third db "Third number is greatest", 10
    msg_equal db "All numbers are equal", 10
    
      msg1l equ $-msg1
    msg2l equ $-msg2
    msg3l equ $-msg3
    msg_greatestl equ $-msg_greatest
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
    jne check_greatest
    cmp bl, cl
    jne check_greatest
    print msg_equal,msg_equall
    jmp exit_prog

check_greatest:
    
    cmp al, bl
    jl check_second
    cmp al, cl
    jl check_third
    print msg_greatest,msg_greatestl
    jmp exit_prog

check_second:
    
    cmp bl, cl
    jl third_greatest
    print msg_second,msg_secondl
    jmp exit_prog

check_third:
    cmp cl, bl
    jl second_greatest
    print msg_third,msg_thirdl
    jmp exit_prog

second_greatest:
    print msg_second,msg_secondl
    jmp exit_prog

third_greatest:
    print msg_third,msg_thirdl
    
exit_prog:
    exit

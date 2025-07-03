section .data

msg1 db "Enter number 1: "
ms1len equ $-msg1
msg2 db "Enter number 2: "
ms2len equ $-msg2
msg3 db "Enter number 3: "
ms3len equ $-msg3
case1 db "All are equal",10
case1len equ $-case1
case2 db "Smallest number is:"
case2len equ $-case2

%macro write 2
mov eax,4
mov ebx,1
mov ecx,%1
mov edx,%2
int 80h
%endmacro

%macro read 2
mov eax,3
mov ebx,0
mov ecx,%1
mov edx,%2
int 80h
%endmacro

section .bss
num1 resb 4
num2 resb 4
num3 resb 4
ans resb 4

section .text
global _start

_start:

write msg1,ms1len
read num1,4
write msg2,ms2len
read num2,4
write msg3,ms3len
read num3,4

mov al,[num1]
mov bl,[num2]
sub al,'0'
sub bl,'0'

cmp al,bl
jne case_2

mov al,[num3]
sub al,'0'
cmp al,bl
je case_1

case_1:
    write case1,case1len
    jmp exit
case_2:
    cmp al,bl
    jl cmp_third

    mov al,bl

    cmp_third:
    mov bl,[num3]
    sub bl,'0'
    cmp al,bl
    jl result

    mov al,bl
    result:
    add al,'0'
    mov [ans],al
    write case2,case2len
    write ans,4

    exit:

    mov eax,1
    mov ebx,0
    int 80h






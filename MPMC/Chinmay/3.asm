section .data
message db "Enter n:",10
msglen equ $-message


section .bss
n resb 2
num1 resb 10
num2 resb 10
sum resb 10
buff resb 1

%macro write 2
    mov eax, 4
    mov ebx, 1
    mov ecx, %1
    mov edx, %2
    int 80h
%endmacro

%macro read 2
    mov eax, 3
    mov ebx, 0
    mov ecx, %1
    mov edx, %2
    int 80h
%endmacro

section .text
global _start

_start:
    write message,msglen 
    read n,2
    read num1,100
    read num2,100
    movzx ecx,byte [n]
    sub ecx,'0'
    mov esi,ecx
    dec esi
    call add

    write sum,100

    mov eax,1
    mov ebx,0
    int 80h

add:
    mov al,[num1+esi]
    mov bl,[num2+esi]
    adc al,bl
    aaa
    pushf
    add al,'0'
    popf
    mov [sum+esi],al
    dec esi
    loop add
    ret




    




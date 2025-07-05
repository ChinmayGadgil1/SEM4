section .data
msg db "enter n:",10
msgl equ $-msg
inp db "Enter number:",0
inpl equ $-inp

section .bss
n resb 1
num1 resb 5
num2 resb 5
buff resb 2
sum resb 5

%macro write 2
    mov eax, 4            ; sys_write
    mov ebx, 1            ; stdout
    mov ecx, %1
    mov edx, %2
    int 80h
%endmacro

%macro read 2
    mov eax, 3            ; sys_read
    mov ebx, 0            ; stdin
    mov ecx, %1
    mov edx, %2
    int 80h
%endmacro

section .text
global _start

_start:

write msg,msgl
read buff,2

movzx eax,byte[buff]
sub al,'0'
mov byte[n],al

write inp,inpl
read num1,5
write inp,inpl
read num2,5

movzx ecx, byte[n]
mov esi,ecx
dec esi

add:
    mov al,[num1+esi]
    mov bl,[num2+esi]
    sub al,'0'
    sub bl,'0'
    sbb al,bl
    aaa
    add al,'0'
    mov byte[sum+esi],al 
    dec esi
    loop add

write sum,5

mov eax,1
mov ebx,0
int 80h







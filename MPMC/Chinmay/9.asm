section .data
msg db "Enter size:",0
msgl equ $-msg


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

section .bss
buff resb 2
n resb 1
index resb 1
even resb 1
odd resb 1


section .text
global _start
_start:

read buff,2
mov al, byte[buff]
sub al,'0'
mov byte[n],al

mov byte[index],0
mov byte[even],0
mov byte[odd],0
input:
    movzx eax,byte[n]
    cmp al,byte[index]
    jle Exit

    read buff,2
    mov al,byte[buff]
    sub al,'0'
    mov bl,2

    div bl

    cmp ah,0
    je even_count

    inc byte[odd]
    inc byte[index]
    jmp input

    even_count:
    inc byte[even]
    inc byte[index]
    jmp input

Exit:

add byte[even],'0'
add byte[odd],'0'

write even,1
write odd,1

mov eax,1
mov ebx,0
int 80h


section .data
msg db "Enter a num:",0
msgl equ $-msg
ans db "Factorial:",0
ansl equ $-ans

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
n resb 2
fact resb 4
buff resb 4

section .text
global _start
_start:
    write msg,msgl
    read n,2

    movzx eax, byte[n]
    sub al,'0'
    mov byte[n],al

    movzx ecx,byte[n]
    dec ecx
    mov byte[fact],al
    factorial:
        cmp ecx,0
        jle next

        mov eax, [fact]
        mul ecx
        mov word[fact],ax
        
        dec ecx
        jmp factorial

    next:
    mov esi,3
    mov word[buff],0
    mov ax,[fact]
    convert:
        cmp esi,0
        jle next2
        mov bx,10
        xor dx,dx
        div bx
        add dl,'0'
        mov [buff+esi],dl
        dec esi
        jmp convert
    next2:
    write ans,ansl
    write buff,4

    exit:
    mov eax,1
    mov ebx,0
    int 80h
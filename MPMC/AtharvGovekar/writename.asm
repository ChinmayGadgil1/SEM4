SECTION .DATA
name db ‘ATHARV’, 10
namelen equ $ - name

SECTION .TEXT
GLOBAL _start

_start:
    ; Print the name
    mov eax, 4
    mov ebx, 1
    mov ecx, name
    mov edx, namelen
    int 80h

    ; Exit the program
    mov eax, 1
    xor ebx, ebx
    int 80h

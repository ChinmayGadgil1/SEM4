SECTION .DATA
word db 'Assembly', 10
wordlen equ $ - word

SECTION .TEXT
GLOBAL _start

_start:
    ; Print the word
    mov eax, 4
    mov ebx, 1
    mov ecx, word
    mov edx, wordlen
    int 80h

    ; Exit the program
    mov eax, 1
    xor ebx, ebx
    int 80h

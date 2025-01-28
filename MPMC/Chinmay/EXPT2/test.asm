section .data
    string db 'Hello World', 0
    len equ $ - string
    old db 'Hello'
    new db 'Hi   '
    newline db 10, 0

section .text
    global _start

_start:
    mov eax, 4              
    mov ebx, 1              
    mov ecx, string         
    mov edx, len            
    int 0x80

    mov eax, 4              
    mov ebx, 1              
    mov ecx, newline        
    mov edx, 1              
    int 0x80

    mov eax, 1              
    xor ebx, ebx            
    int 0x80

SECTION .BSS
number resb 10          

SECTION .TEXT
GLOBAL _start

_start:
    
    mov eax, 3           
    mov ebx, 0           
    mov ecx, number      
    mov edx, 10          
    int 80h

    
    mov eax, 4           
    mov ebx, 1           
    mov ecx, number      
    mov edx, 10          
    int 80h

    ; Exit the program
    mov eax, 1
    xor ebx, ebx
    int 80h

section .data
    prompt db 'Enter your name: '
    plen equ $ - prompt
    msg db 'Hello, '
    mlen equ $ - msg
    
section .bss
    name resb 50        ; Reserve 50 bytes for name input
    
section .text
    global _start

_start:
    ; Display prompt
    mov eax, 4          
    mov ebx, 1          
    mov ecx, prompt     
    mov edx, plen       
    int 0x80

    ; Read name from user
    mov eax, 3          
    mov ebx, 0          
    mov ecx, name       
    mov edx, 50         
    int 0x80

    ; Display greeting
    mov eax, 4          
    mov ebx, 1          
    mov ecx, msg        
    mov edx, mlen       
    int 0x80

    ; Display entered name
    mov eax, 4          
    mov ebx, 1          
    mov ecx, name       
    mov edx, 50         
    int 0x80

    ; Exit program
    mov eax, 1          
    xor ebx, ebx        
    int 0x80

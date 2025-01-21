SECTION .DATA
stars db '*', 10   
starslen equ $ - stars  

SECTION .TEXT
GLOBAL _start

_start:
    mov ecx, 9         ; 

print_loop:
    mov eax, 4         
    mov ebx, 1         
    mov edx, starslen  
    mov esi, stars    
    int 80h            

    dec ecx            
    jnz print_loop     

    mov eax, 1         
    xor ebx, ebx       
    int 80h            

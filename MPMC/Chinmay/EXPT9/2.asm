section .data
    msg db "Enter number of elements: "
    msglen equ $-msg                      
    msg2 db "Enter elements: "
    msg2len equ $-msg2                    
    msg3 db "Enter element to search: "
    msg3len equ $-msg3                    
    msg4 db "Found at index: "
    msg4len equ $-msg4                  
    msg5 db "Not found"
    msg5len equ $-msg5                  
    newline db 10
    space db ' '

%macro write 2
    mov eax,4
    mov ebx,1
    mov ecx,%1
    mov edx,%2
    int 80h                              
%endmacro
    
%macro read 2
    mov eax,3
    mov ebx,2
    mov ecx,%1
    mov edx,%2
    int 80h                              
    mov eax,3
    mov ebx,2
    mov ecx,trash
    mov edx,1
    int 80h                               
%endmacro
    
input:
    mov ecx,0
repeat_input:                          
    cmp ecx,5
    jge next_input
    mov esi,eax
    add esi,ecx
    pushad
    read esi,1
    popad
    inc ecx
    jmp repeat_input
next_input:
    ret

binary_search:
    and edi,000fh                      
    mov [lb],byte 0                   
    mov [ub],byte 4                     
repeat_search:
    mov cl,[lb]
    mov dl,[ub]
    cmp cl,dl
    jg next_search                     
    pushad
    mov al,[lb]
    add al,[ub]
    cbw
    mov bl,2
    div bl                              
    mov [mid],al
    popad
    mov edx,[mid]
    and edx,000fh
    mov esi,dword [eax+edx]
    and esi,000fh
    cmp edi,esi
    je matched
    jl lower_part
upper_part:
    mov bl,[mid]
    add bl,1
    mov [lb],bl                         
    jmp repeat_search
lower_part:
    mov bl,[mid]
    sub bl,1
    mov [ub],bl                       
    jmp repeat_search
matched:
    add edx,'0'
    mov [index],edx                     
    pushad
    write msg4,msg4len                 
    write index,1                       
    popad
    ret
next_search:
    write msg5,msg5len                 
    ret
    
section .bss
    num resb 4
    arr resb 5
    index resb 4
    lb resb 1
    ub resb 1
    mid resb 1
    trash resb 1

section .text
global _start

_start:
    write msg2,msg2len                 
    mov eax,arr
    call input                          
    write msg3,msg3len                 
    read num,1                         
    mov eax,arr
    mov edx,5                          
    mov edi,[num]
    call binary_search                  
    write newline,1
    mov eax,1
    mov ebx,0
    int 80h                  

section .data
    msg3 db "The sorted array is: "    
    msg3len equ $-msg3                 
    newline db 10                      
    space db ' '                       
    arr db 6,4,3,5,1,2                
    arr_len equ $-arr                  

section .bss
    temp resb 1                       
    buffer resb 2                     

%macro write 2                            
    mov eax, 4
    mov ebx, 1
    mov ecx, %1
    mov edx, %2
    int 80h                           
%endmacro

section .text
global _start


display:
    xor esi, esi                     

display_loop:
    cmp esi, arr_len                  
    jge display_end                  
    
    mov al, [arr + esi]               
    add al, '0'                       
    mov [buffer], al                  
    
   
    write buffer, 1                   
    write space, 1                    
    
    inc esi                          
    jmp display_loop                  

display_end:
    write newline, 1               
    ret


selection_sort:
    xor esi, esi                     

outer_loop:
    cmp esi, arr_len-1              
    jge sort_end                     
    
    mov ebx, esi                    
    mov edi, esi                     
    inc edi                          

inner_loop:
    cmp edi, arr_len                 
    jge do_swap                      
    
    mov al, [arr + edi]              
    mov dl, [arr + ebx]             
    cmp al, dl                      
    jge next_element                 
    mov ebx, edi                     

next_element:
    inc edi                          
    jmp inner_loop                   
    
do_swap:
    cmp ebx, esi                     
    je no_swap                       
    mov al, [arr + esi]              
    mov dl, [arr + ebx]            
    mov [arr + esi], dl              
    mov [arr + ebx], al              
    
no_swap:
    inc esi                         
    jmp outer_loop                   
    
sort_end:
    ret

_start:
  
    write msg3, msg3len             
    
    call selection_sort            
    call display                     
    
    mov eax, 1
    xor ebx, ebx
    int 80h

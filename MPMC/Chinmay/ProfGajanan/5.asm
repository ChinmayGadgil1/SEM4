
section .data
    menu_msg    db  10, "String Reverser Menu:", 10
                db  "1. Enter a string", 10
                db  "2. Reverse the string", 10
                db  "3. Exit", 10
                db  "Enter your choice: ", 0
    menu_len    equ $ - menu_msg
    
    prompt      db  "Enter a string: ", 0
    prompt_len  equ $ - prompt
    
    result_msg  db  "Reversed string: ", 0
    result_len  equ $ - result_msg
    
    no_string   db  "Please enter a string first!", 10, 0
    no_str_len  equ $ - no_string
    
    newline     db  10
    invalid     db  "Invalid choice. Try again.", 10, 0
    invalid_len equ $ - invalid
    
section .bss
    buffer      resb    1024    
    buflen      equ     1024   
    choice      resb    2       
    str_len     resd    1      
    has_string  resb    1      
    
section .text
    global _start
    
_start:
    mov byte [has_string], 0
    
menu:
    ; Display menu
    mov     eax, 4             
    mov     ebx, 1             
    mov     ecx, menu_msg     
    mov     edx, menu_len       
    int     0x80                
    
    ; Read choice
    mov     eax, 3             
    mov     ebx, 0            
    mov     ecx, choice         
    mov     edx, 2           
    int     0x80                
    
    ; Process choice
    cmp     byte [choice], '1'  
    je      enter_string
    cmp     byte [choice], '2'  
    je      reverse_string
    cmp     byte [choice], '3' 
    je      exit_program
    
    ; Invalid choice
    mov     eax, 4              
    mov     ebx, 1              
    mov     ecx, invalid        
    mov     edx, invalid_len    
    int     0x80                
    jmp     menu
    
enter_string:
    ; Prompt for string
    mov     eax, 4              
    mov     ebx, 1              
    mov     ecx, prompt         
    mov     edx, prompt_len     
    int     0x80               
    
    ; Read string
    mov     eax, 3             
    mov     ebx, 0             
    mov     ecx, buffer         
    mov     edx, buflen        
    int     0x80                
    
    dec     eax                 
    mov     [str_len], eax      
    mov     byte [has_string], 1
    jmp     menu
    
reverse_string:
    cmp     byte [has_string], 0
    jne     do_reverse
    
    ; No string entered yet
    mov     eax, 4            
    mov     ebx, 1              
    mov     ecx, no_string     
    mov     edx, no_str_len     
    int     0x80              
    jmp     menu
    
do_reverse:
    mov     eax, 4              
    mov     ebx, 1              
    mov     ecx, result_msg     
    mov     edx, result_len     
    int     0x80               
    
    mov     ecx, [str_len]      
    dec     ecx                 
    
reverse_loop:
    cmp     ecx, 0
    jl      end_reverse
    
    mov     eax, 4              
    mov     ebx, 1           
    lea     edx, [buffer+ecx]  
    push    ecx                 
    mov     ecx, edx            
    mov     edx, 1              
    int     0x80                
    pop     ecx                 
    
    dec     ecx
    jmp     reverse_loop
    
end_reverse:
    mov     eax, 4             
    mov     ebx, 1             
    mov     ecx, newline        
    mov     edx, 1             
    int     0x80               
    jmp     menu
    
exit_program:
    mov     eax, 1              
    xor     ebx, ebx            
    int     0x80                
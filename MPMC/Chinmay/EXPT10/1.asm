section .data
    msg2 db "Enter the elements in the array: "
    msg2len equ $-msg2
    msg3 db "The sorted array is: "
    msg3len equ $-msg3
    msg4 db "Pass "
    msg4len equ $-msg4
    msg5 db ": "
    msg5len equ $-msg5
    newline db 10
    space db ' '
    n db 5       ; Fixed size of 5

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
    write msg2,msg2len      
    mov [i], byte 0       ; Initialize counter to 0 (numeric)
loop1:
    movzx esi, byte [i]   ; Use movzx for proper zero extension
    cmp esi, 5            ; Compare with 5 directly
    jge end1              
    lea esi, [arr + esi]  ; Calculate array address
    read esi, 1           
    inc byte [i]          ; Increment counter
    jmp loop1              
end1:
    ret                  

display:
    mov [i], byte 0       ; Initialize counter to 0 (numeric)
loop2:
    movzx esi, byte [i]   ; Use movzx for proper zero extension
    cmp esi, 5            ; Compare with 5 directly
    jge end2              
    lea esi, [arr + esi]  ; Calculate array address
    write esi, 1          
    write space, 1        
    inc byte [i]          
    jmp loop2              
end2:
    write newline, 1      
    ret                   

bubble_sort:
    mov byte [pass_num], '1'  ; Initialize pass number to '1'
    mov al, 0                 ; Outer loop counter
outer_loop:
    cmp al, 4                 ; n-1 iterations
    jge sort_end
    
    ; Display current pass number and array
    pushad
    write msg4, msg4len
    mov cl, [pass_num]
    mov [temp], cl
    write temp, 1
    write msg5, msg5len
    call display
    popad
    
    ; Inner loop for comparisons
    mov cl, 0                 ; Inner loop counter
inner_loop:
    mov dl, 4                 ; n-1
    sub dl, al               
    cmp cl, dl
    jge inner_loop_end
    
    ; Compare adjacent elements
    movzx esi, cl
    mov bl, [arr + esi]      ; First element
    mov bh, [arr + esi + 1]  ; Next element
    cmp bl, bh
    jle no_swap
    
    ; Swap elements
    mov [arr + esi], bh
    mov [arr + esi + 1], bl
    
no_swap:
    inc cl
    jmp inner_loop
    
inner_loop_end:
    inc al
    inc byte [pass_num]      ; Increment pass number
    jmp outer_loop
    
sort_end:
    ; Display final pass
    write msg4, msg4len
    mov cl, [pass_num]
    mov [temp], cl
    write temp, 1
    write msg5, msg5len
    call display
    ret

section .bss
    arr resb 5              ; Array of size 5
    i resb 1               ; Single byte counter
    pass_num resb 1        ; Pass number for display
    temp resb 1            ; Temporary storage
    trash resb 1          

section .text
global _start

_start:
    call input               
    write newline, 1         
    call bubble_sort         
    write newline, 1         
    write msg3, msg3len      
    call display            
    mov eax, 1              
    mov ebx, 0              
    int 80h
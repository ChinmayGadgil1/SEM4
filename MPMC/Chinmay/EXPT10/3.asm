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

section .bss
    arr resb 5              ; Array of size 5
    i resb 1               ; Single byte counter
    pass_num resb 1        ; Pass number for display
    temp resb 1            ; Temporary storage
    trash resb 1          
    min_idx resb 1        ; Index of minimum element

section .text
global _start

input:
    write msg2,msg2len      
    mov [i], byte 0       
loop1:
    movzx esi, byte [i]   
    cmp esi, 5            
    jge end1              
    lea esi, [arr + esi]  
    read esi, 1           
    inc byte [i]          
    jmp loop1              
end1:
    ret                  

display:
    mov [i], byte 0       
loop2:
    movzx esi, byte [i]   
    cmp esi, 5            
    jge end2              
    lea esi, [arr + esi]  
    write esi, 1          
    write space, 1        
    inc byte [i]          
    jmp loop2              
end2:
    write newline, 1      
    ret                   

selection_sort:
    mov byte [pass_num], '1'  ; Initialize pass number
    mov al, 0                 ; Outer loop counter (i)
outer_loop:
    cmp al, 4                 ; n-1 iterations
    jge sort_end
    
    ; Display current pass
    pushad
    write msg4, msg4len
    mov cl, [pass_num]
    mov [temp], cl
    write temp, 1
    write msg5, msg5len
    call display
    popad
    
    mov [min_idx], al        ; min_idx = i
    mov cl, al               ; Inner loop counter (j)
    inc cl                   ; j = i + 1

find_min:
    cmp cl, 5                ; Compare with array size
    jge swap_min
    
    ; Compare arr[j] with arr[min_idx]
    movzx esi, cl
    movzx edi, byte [min_idx]
    mov bl, [arr + esi]      ; arr[j]
    mov bh, [arr + edi]      ; arr[min_idx]
    cmp bl, bh
    jge no_update_min
    
    ; Update min_idx
    mov [min_idx], cl

no_update_min:
    inc cl
    jmp find_min

swap_min:
    ; Swap arr[i] with arr[min_idx]
    movzx esi, al            ; i
    movzx edi, byte [min_idx]
    mov bl, [arr + esi]      ; temp = arr[i]
    mov bh, [arr + edi]      ; arr[min_idx]
    mov [arr + esi], bh      ; arr[i] = arr[min_idx]
    mov [arr + edi], bl      ; arr[min_idx] = temp
    
    inc al
    inc byte [pass_num]
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

_start:
    call input               
    write newline, 1         
    call selection_sort      
    write newline, 1         
    write msg3, msg3len      
    call display            
    mov eax, 1              
    mov ebx, 0              
    int 80h
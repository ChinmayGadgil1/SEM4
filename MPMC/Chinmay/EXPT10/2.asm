section .data
    msg db "Enter number of elements: "
    msglen equ $-msg
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
    n db '5'

%macro write 2
    mov eax,4
    mov ebx,1
    mov ecx,%1
    mov edx,%2
    int 80h
%endmacro
    
%macro read 2
    mov eax,3
    mov ebx,0
    mov ecx,%1
    mov edx,%2
    int 80h
    mov eax,3
    mov ebx,0
    mov ecx,trash
    mov edx,1
    int 80h
%endmacro
    
input:
    write msg2,msg2len
    mov byte[i], 0        ; Initialize counter as numeric 0
loop1:
    movzx esi, byte[i]
    cmp esi, 5            ; Compare with numeric 5
    jge end1
    lea esi, [arr + esi]  ; Calculate array address
    read esi, 1
    inc byte[i]
    jmp loop1    
end1:
    ret

display:
    mov byte[i], 0        ; Initialize counter as numeric 0
loop2:
    movzx esi, byte[i]
    cmp esi, 5            ; Compare with numeric 5
    jge end2
    lea esi, [arr + esi]  ; Calculate array address
    write esi, 1
    write space, 1
    inc byte[i]
    jmp loop2    
end2:
    write newline, 1    
    ret

insertion_sort:
    mov byte[j], '1'      ; Initialize pass counter to '1'
    mov eax, 1            ; Start from second element
loop3:
    cmp al, 5             ; Compare with array size
    jge end3
    
    ; Display current pass
    pushad
    write msg4, msg4len
    mov dl, [j]
    mov [temp], dl        ; Store current pass number
    write temp, 1
    write msg5, msg5len
    call display
    popad
    
    ; Store key
    mov dl, [arr + eax]   ; Key = arr[eax]
    mov ecx, eax
    dec ecx               ; j = i-1
    
loop4:
    cmp cl, 0
    jl update
    mov dh, [arr + ecx]   ; Get arr[j]
    cmp dh, dl            ; Compare with key
    jle update
    
    ; Move element
    mov [arr + ecx + 1], dh
    dec ecx
    jmp loop4
    
update:
    mov [arr + ecx + 1], dl
    inc eax               ; Move to next element
    inc byte[j]           ; Increment pass counter
    jmp loop3
    
end3:
    ; Display final pass
    write msg4, msg4len
    mov dl, [j]
    mov [temp], dl
    write temp, 1
    write msg5, msg5len
    call display
    ret

section .bss
    arr resb 5            ; Array of 5 elements
    i resb 1              ; Counter for input/display
    j resb 1              ; Pass counter
    temp resb 1           ; Temporary storage
    trash resb 1

section .text
global _start

_start:
    call input
    write newline, 1
    call insertion_sort
    write newline, 1
    write msg3, msg3len
    call display
    mov eax, 1
    mov ebx, 0
    int 80h
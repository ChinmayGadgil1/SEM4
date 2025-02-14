section .data
    msg1 db "Enter first string: ", 0
    msg2 db "Enter second string: ", 0
    equal_msg db "Strings are equal", 10
    not_equal_msg db "Strings are not equal", 10
    
     msg1l equ $-msg1
    msg2l equ $-msg2
    not_equal_msgl equ $-not_equal_msg
    equal_msgl equ $-equal_msg
   
%macro print 2
    mov eax, 4
    mov ebx, 1
    mov ecx, %1
    mov edx, %2
    int 0x80
%endmacro

%macro input 2
    mov eax, 3
    mov ebx, 2
    mov ecx, %1
    mov edx, %2
    int 0x80
%endmacro

%macro exit 0
    mov eax, 1
    mov ebx, 0
    int 0x80
%endmacro

section .bss
    str1 resb 50
    str2 resb 50

section .text
    global _start

_start:
    print msg1,msg1l
    input str1, 50
    
    print msg2, msg2l
    input str2, 50

compare_strings:
    mov esi, str1
    mov edi, str2
    mov ecx, 50

compare_loop:
    mov al, [esi]
    mov bl, [edi]
    
    cmp al, bl
    jne not_equal
    
    cmp al, 0xa
    je equal
    
    inc esi
    inc edi
    loop compare_loop

equal:
    print equal_msg, equal_msgl
    jmp exit_prog

not_equal:
    print not_equal_msg, not_equal_msgl
    
exit_prog:
    exit

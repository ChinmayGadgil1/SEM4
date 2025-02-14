section .data
    msg1 db "Enter a string: ", 0
    msg2 db "Enter word to find: ", 0
    msg3 db "Enter word to replace with: ", 0
    nl db 0xa
    msg4 db "Modified string: ", 0

section .bss
    str1 resb 100
    word1 resb 20
    word2 resb 20
    str2 resb 100

section .text
    global _start

_start:
    mov eax, 4
    mov ebx, 1
    mov ecx, msg1
    mov edx, 15
    int 0x80

    mov eax, 3
    mov ebx, 0
    mov ecx, str1
    mov edx, 100
    int 0x80

    mov eax, 4
    mov ebx, 1
    mov ecx, msg2
    mov edx, 17
    int 0x80

    mov eax, 3
    mov ebx, 0
    mov ecx, word1
    mov edx, 20
    int 0x80

    mov eax, 4
    mov ebx, 1
    mov ecx, msg3
    mov edx, 23
    int 0x80

    mov eax, 3
    mov ebx, 0
    mov ecx, word2
    mov edx, 20
    int 0x80

    mov esi, str1
    mov edi, str2
    mov ecx, 100

loop1:
    mov al, [esi]
    cmp al, 0xa
    je end
    cmp al, 0
    je end
    
    mov [edi], al
    inc esi
    inc edi
    loop loop1

end:
    mov eax, 4
    mov ebx, 1
    mov ecx, msg4
    mov edx, 16
    int 0x80

    mov eax, 4
    mov ebx, 1
    mov ecx, str2
    mov edx, 100
    int 0x80

    mov eax, 1
    mov ebx, 0
    int 0x80

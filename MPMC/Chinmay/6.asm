section .data
msg db "Enter size: ",0
msglen equ $-msg
inp db "Enter array:",10
inpl equ $-inp
case1 db "Found at index: ",0
case1l equ $-case1
case2 db "Not found",0
case2l equ $-case2

section .bss
array resb 20
index resb 1
buff resb 2
n resb 1
elem resb 1

section .text
global _start

%macro write 2
    mov eax, 4            ; sys_write
    mov ebx, 1            ; stdout
    mov ecx, %1
    mov edx, %2
    int 80h
%endmacro

%macro read 2
    mov eax, 3            ; sys_read
    mov ebx, 0            ; stdin
    mov ecx, %1
    mov edx, %2
    int 80h
%endmacro

_start:
    write msg,msglen
    read buff,2

    movzx eax,byte[buff]
    sub al,'0'
    mov [n],al

    movzx eax,byte[n]
    mov byte [index],0

    input:
        movzx ebx,byte[n]
        movzx eax,byte[index]
        cmp eax,ebx
        jge ip_done

        read buff,2
        movzx ebx, byte[index]
        movzx eax,byte[buff] 
        sub al,'0'
        mov [array + ebx],al
        inc byte[index]
        jmp input
    ip_done:
    mov byte[index],0
    display:
        movzx ebx,byte[n]
        movzx eax,byte[index]
        cmp eax,ebx
        jge next

        movzx ebx, byte[index]
        movzx eax, byte[array+ebx]
        add al,'0'
        mov byte[buff],al
        write buff,1
        inc byte[index]
        jmp display
    
    next:
        read buff,2
        movzx eax, byte[buff]
        sub al,'0'
        mov [elem],al

        mov byte[index],0
        linear_seach:
            movzx eax, byte[index]
            movzx ebx, byte[n]
            cmp eax,ebx
            jge not_found

            movzx ebx,byte[array+eax]
            cmp bl,byte[elem]
            je found

            inc byte[index]
            jmp linear_seach
        not_found:
            write case2,case2l
            jmp Exit
        found:
            write case1,case1l
            movzx eax,byte[index]
            add al,'0'
            mov byte[buff],al
            write buff,1
    Exit:        
    mov eax,1
    mov ebx,0
    int 80h
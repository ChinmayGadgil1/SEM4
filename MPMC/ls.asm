%macro write 2
mov eax, 4 
mov ebx, 1 
mov ecx, %1 
mov edx, %2 
int 80h 
%endmacro

%macro read 2
mov eax, 3 
mov ebx, 2 
mov ecx, %1 
mov edx, %2 
int 80h 

%endmacro
section .data
msg1 db 'Enter number of elements : '
msg1len equ $-msg1
msg2 db 'Enter elements in array : '
msg2len equ $-msg2
msg3 db 'Enter number to be searched: '
msg3len equ $-msg3
msg4 db 'Number found at index: '
msg4len equ $-msg4
msg5 db 'Number not found'
msg5len equ $-msg5
newline db '',10 
n1 equ $-newline

input:
mov byte[i], 0
mov esi, arr 
l_input:
read element, 2 
mov ebx, [element]
sub ebx, '0' 
mov [esi], ebx 
inc esi 
inc byte[i]
mov al, [i] 
mov bl, [num]
sub bl, '0'
CMP al, bl 
JL l_input 
mov byte[i], 0
mov esi, arr
ret


linear_search:
mov ecx, [num] 
sub ecx, '0' 
mov esi, 0 
label:
movzx edi, byte[arr+esi] 
mov [temp], edi 
mov al, [temp]
mov bl, [searche]
sub bl, '0'
cmp al, bl
je l1 
jmp end
l1:
write msg4, msg4len 
add esi, '0' 
mov [index], esi
write index, 2 
write newline, n1
mov eax, 1
mov ebx, 0
int 80h 
end:
inc esi 
loop label 
ret


section .bss
arr resb 10
searche resb 10
i resb 1
index resb 2
element resb 2
num resb 10
temp resb 5

section .text
global _start
_start:
write msg1, msg1len 
read num, 10 
write msg2, msg2len 
call input 
write msg3, msg3len 
read searche, 10 
call linear_search 
write msg5, msg5len 
write newline, n1
mov eax, 1 
mov ebx, 0
int 80h 

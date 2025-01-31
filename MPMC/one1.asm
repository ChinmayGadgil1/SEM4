section .data
msg1 db 'Enter the elements of the array:', 10
msg1len equ $-msg1
msg2 db 'Enter the number of elements in the
array: '
msg2len equ $-msg2
msg3 db 'The sum is:'
msg3len equ $-msg3
newline db ' ',10
newlinelen equ $-newline
tab db ' '
tablen equ $-tab
;array declaration and initialization
array dw 0,0,0,0,0,0,0,0,0
arraylen equ 9
section .bss
num resb 9
element resb 9
i resb 9
sum resb 9
section .text
global _start
_start:
mov eax,4
mov ebx, 1
mov ecx,msg2
mov edx,msg2len
int 80h
mov eax,3
mov ebx,2
mov ecx,num
mov edx,9
int 80h
mov eax,4
mov ebx,1
mov ecx,msg1
mov edx,msg1len
int 80h
mov eax, [num]
mov [i], eax
mov esi, array
mov eax, num
inputelement:
mov eax, 3
mov ebx,2
mov ecx, element
mov edx,2
int 80h
mov ebx, [element]
mov [esi], ebx
dec byte[num]
inc esi
cmp byte[num], '0'
jne inputelement
mov eax,'0'
mov [sum],eax
mov esi, array
mov eax,i
SUM:
mov eax,[esi]
mov [element],eax
mov al,[element]
sub al,'0'
mov bl,[sum]
sub bl,'0'
add al,bl
add al,'0'
mov [sum],al
dec byte[i]
inc esi
cmp byte[i],'0'
jne SUM
mov eax,4
mov ebx,1
mov ecx,msg3
mov edx,msg3len
int 80h
mov eax,4
mov ebx,1
mov ecx,sum
mov edx,9
int 80h
mov eax,4
mov ebx,1
mov ecx,newline
mov edx,newlinelen
int 80h
mov eax,1
mov ebx,0
int 80h
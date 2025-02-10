section .data
msg1 db 'Enter the elements of the array:', 10
msg1len equ $-msg1
msg2 db 'Enter the number of elements in the array: '
msg2len equ $-msg2
msg3 db 'The sum is:'
msg3len equ $-msg3
newline db ' ',10
newlinelen equ $-newline
tab db ' '
tablen equ $-tab
array dw 0,0,0,0,0,0,0,0,0
arraylen equ 9
section .bss
num resb 9
element resb 9
i resb 9
sum resb 9

%macro writesystem 2
mov eax,4
mov ebx, 1
mov ecx,%1
mov edx,%2
int 80h
%endmacro

%macro readsystem 2
mov eax,3
mov ebx,2
mov ecx,%1
mov edx,%2
int 80h
%endmacro

section .text
global _start
_start:
writesystem msg2,msg2len
readsystem num,9
writesystem msg1,msg1len

mov eax, [num]
mov [i], eax
mov esi, array
mov eax, num
inputelement:
readsystem element,2
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

writesystem msg3,msg3len
writesystem sum,9
writesystem newline,newlinelen

mov eax,1
mov ebx,0
int 80h

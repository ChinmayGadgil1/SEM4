%macro write 2
mov eax, 4 ; syscall number for sys_write
mov ebx, 1 ; file descriptor 1 for stdout
mov ecx, %1 ; message to write
mov edx, %2 ; message length
int 80h ; interrupt to invoke syscall
%endmacro

; Macro to simplify reading input from stdin
%macro read 2
mov eax, 3 ; syscall number for sys_read
mov ebx, 2 ; file descriptor 0 for stdin, changed to 2 for buffer (?)
mov ecx, %1 ; buffer to read input into
mov edx, %2 ; number of bytes to read
int 80h ; interrupt to invoke syscall
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
newline db '',10 ; New line character to format output
n1 equ $-newline
; Input routine to read integers from user
input:
mov byte[i], 0
mov esi, arr ; ESI points to the start of the array
l_input:
read element, 2 ; Read 2 bytes of data
mov ebx, [element]
sub ebx, '0' ; Convert ASCII character to integer
mov [esi], ebx ; Store integer in array
inc esi ; Move to next element in array
inc byte[i]
mov al, [i] ; Load current count
mov bl, [num]
sub bl, '0'
CMP al, bl ; Compare count with number of elements to read
JL l_input ; Loop until all elements are read
mov byte[i], 0
mov esi, arr
ret
; Linear search algorithm
linear_search:
mov ecx, [num] ; Load number of elements into ECX
sub ecx, '0' ; Convert from ASCII to integer
mov esi, 0 ; Index for array
label:
movzx edi, byte[arr+esi] ; Load element into EDI
mov [temp], edi ; Store it temporarily
mov al, [temp] ; Move element to AL for comparison
mov bl, [searche]
sub bl, '0'
cmp al, bl
je l1 ; If found, jump to label l1
jmp end
l1:
write msg4, msg4len ; Output found message
add esi, '0' ; Convert index to ASCII
mov [index], esi
write index, 2 ; Write index to stdout
write newline, n1
mov eax, 1
mov ebx, 0
int 80h ; Exit program
end:
inc esi ; Increment index
loop label ; Loop through all elements
ret
; Uninitialized data section
section .bss
arr resb 10
searche resb 10
i resb 1
index resb 2
element resb 2
num resb 10
temp resb 5
; Start of the text (code) section
section .text
global _start
_start:
write msg1, msg1len ; Message to the user to enter number of elements
read num, 10 ; Read the number of elements
write msg2, msg2len ; Ask for elements in the array
call input ; Read elements into array
write msg3, msg3len ; Ask for number to search
read searche, 10 ; Read the search key
call linear_search ; Perform linear search
write msg5, msg5len ; If not found, write not found message
write newline, n1
mov eax, 1 ; Syscall for exit
mov ebx, 0
int 80h ; Execute syscall 

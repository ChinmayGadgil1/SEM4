section .data
msg db ' ',10
msgLen equ $-msg
msg1 db 'Number 1 (2 digits): '
msg1Len equ $-msg1
msg2 db 'Number 2 (2 digits): '
msg2Len equ $-msg2
msg3 db 'Sum: '
msg3Len equ $-msg3

%macro writesystem 2
mov eax,4
mov ebx,1
mov ecx, %1
mov edx, %2
int 80h
%endmacro
%macro readsystem 2
mov eax,3
mov ebx,2
mov ecx,%1
mov edx,%2
int 80h
%endmacro

%macro addition 0
    mov al, [num1]
    sub al, '0'
    mov ah, [num1+1]
    sub ah, '0'
    
    ; First digit is tens place, second is units
    mov bl, 10
    mul bl  ; AL = AL * BL (tens digit * 10)
    add al, ah  ; Add units digit
    
    ; Store first BCD number
    mov [bcd1], al
    
    ; Convert second number to BCD
    mov al, [num2]
    sub al, '0'
    mov ah, [num2+1]
    sub ah, '0'
    
    mov bl, 10
    mul bl
    add al, ah
    
    ; Add the two BCD numbers
    add al, [bcd1]
    
    ; Convert BCD result back to ASCII
    mov ah, 0
    mov bl, 10
    div bl  ; AL = quotient (tens), AH = remainder (units)
    
    ; Convert back to ASCII
    add al, '0'
    add ah, '0'
    
    ; Store in result
    mov [sum], al    ; Tens digit
    mov [sum+1], ah  ; Units digit
%endmacro

section .bss
num1 RESB 5  ; Space for 2 digits + enter + null
num2 RESB 5
sum RESB 5
bcd1 RESB 1

section .text
global _start
_start:
    writesystem msg1, msg1Len
    readsystem num1, 5
    writesystem msg2, msg2Len
    readsystem num2, 5
    
    addition
    
    writesystem msg3, msg3Len
    writesystem sum, 2  ; Display 2 digits
    writesystem msg, msgLen

    mov eax, 1
    mov ebx, 0
    int 80h 

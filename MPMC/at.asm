section .data
    msg_input1 db "Enter first number: ", 0
    msg_input2 db "Enter second number: ", 0
    msg_input3 db "Enter third number: ", 0
    msg_result db "Smallest number is: ", 0

    msg_input1_len equ $-msg_input1
    msg_input2_len equ $-msg_input2
    msg_input3_len equ $-msg_input3
    msg_result_len equ $-msg_result

section .bss
    num1 resb 4
    num2 resb 4
    num3 resb 4
    buffer resb 64  

section .text
    global _start

%macro print 2
    mov eax, 4
    mov ebx, 1
    mov ecx, %1
    mov edx, %2
    int 80h
%endmacro

%macro read 2
    mov eax, 3
    mov ebx, 0
    mov ecx, %1
    mov edx, %2
    int 80h
%endmacro

%macro exit 0
    mov eax, 1
    xor ebx, ebx
    int 80h
%endmacro

_start:
   
    print msg_input1, msg_input1_len
    read num1, 4
    
   
    print msg_input2, msg_input2_len
    read num2, 4
    
   
    print msg_input3, msg_input3_len
    read num3, 4
    
   
    mov eax, [num1]
    mov ebx, [num2]
    mov ecx, [num3]
    
   
    cmp eax, ebx
    jle check_third
    mov eax, ebx

check_third:
    cmp eax, ecx
    jle print_result
    mov eax, ecx

print_result:
    print msg_result, msg_result_len
    print eax, 4

end_program:
    exit

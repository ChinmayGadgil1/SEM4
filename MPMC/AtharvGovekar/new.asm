SECTION .data
s1 db'Mechanical Engineering',10
s1len equ $-s1

SECTION .TEXT
 GLOBAL _start
_start:
   mov eax,4
   mov ebx,1
   mov ecx, s1
   mov edx, s1len
   int 80h

   mov eax, 4
   mov ebx, 1
   mov [s1], dword 'Computer'
   mov ecx, s1
   mov edx, s1len
   int 80h 

 mov eax,1
 mov ebx,0
 int 80h
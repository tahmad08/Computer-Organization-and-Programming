.orig x3000

halt

fibonacci
ADD R6, R6, -4 		;place stack pointer to build up first portion of the stack (a)
STR R7, R6, 2 		;save old return address
STR R5, R6, 1 		;save old frame pointer
ADD R5, R6, 0 		;set current frame pointer
ADD R6, R6, -5 		;place stack pointer to save all of the registers on the stack (b)
STR R0, R6, 4 		;save R0
STR R1, R6, 3 		;save R1
STR R2, R6, 2 		;save R2
STR R3, R6, 1 		;save R3
STR R4, R6, 0 		;save R4


LDR R0, R5, 4 		;R0 <= n


ADD R2, R0, -1
BRnz BASE


ADD R6, R6, -1 		;R6 will now point to one above R4
ADD R1, R0, -1 		;getting n-1
STR R1, R6, 0 		;store (n-1) at first parameter
JSR fibonacci 		;fib(n-1)


LDR R1, R6, 0 		;when the subroutine ends, R6 will point to the return value
ADD R6, R6, 1 		;go back to the params
ADD R2, R0, -2 		;getting n-2
STR R2, R6, 0 		;store (n-2) at first parameter
JSR fibonacci 		;fib(n-2)


LDR R2, R6, 0 		;when the subroutine ends, R6 will point to the return value
ADD R6, R6, 2 		;we want r6 to point to the top of the register stack
ADD R3, R1, R2 		;have r3 hold the values of fib(n-1) + fib(n-2)
STR R3, R5, 3 		;store the return value!
BR STACK_BREAKDOWN

BASE
STR R0, R5, 3 		;place the return value in the return value place of the stack
BR STACK_BREAKDOWN

STACK_BREAKDOWN

LDR R4, R5, -5 		;restore R4
LDR R3, R5, -4 		;restore R3
LDR R2, R5, -3 		;restore R2
LDR R1, R5, -2 		;restore R1
LDR R0, R5, -1 		;restore R0
ADD R6, R5, 0 		;bring R6 back down to R5
LDR R5, R6, 1 		;restore old frame pointer
LDR R7, R6, 2 		;restore return address
ADD R6, R6, 3 		;have R6 point to the return value
RET

STACK .fill xF000
.end

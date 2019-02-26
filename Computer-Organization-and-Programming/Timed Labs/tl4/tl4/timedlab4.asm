
;;====================================================
;; CS 2110 - Fall 2018
;; Timed Lab 4
;; converge.asm
;;====================================================
;; Name: Tahirah Ahmad
;;====================================================

.orig x4000
  .fill 8
.end

.orig x3000

;; Don't try to run this code directly, since it only contains
;; subroutines that need to be invoked using the LC-3 calling
;; convention. Use Debug > Setup Test or Simulate Subroutine
;; Call in complx instead.
;;
;; Do not remove this line or you will break...
;; 'Simulate Subroutine Call'

halt

converge
  ADD R6, R6, -4
  STR R7, R6, 2           ;store RA
  STR R5, R6, 1           ;store old FP
  ADD R5, R6, 0           ;set current frame pointer
  ADD R6, R6, -5    ;move r6 TO STORE REGS
  STR R0, R6, 4           ;store R0 on the stack
  STR R1, R6, 3           ;store R1 on the stack
  STR R2, R6, 2           ;store R2 on the stack
  STR R3, R6, 1           ;store R3 on the stack
  STR R4, R6, 0           ;store R4 on the stack

  LD R0, DIV_ADDR   ;LOAD IN THE ADDRESS OF DIVIDE
  
  LDR R4, R5, 4     ;<-LOAD IN n TO R4
; LDR R4, R4, 0

  AND R3, R3, 0   ; R3 = 0
  ADD R3, R3, -1    ; R3 = -1
  ADD R3, R3, R4    ; ADD R4 + -1
  BRZ BASE    ;IF ITS 0, THEN N==1, RETURN 0;
  
  
  ADD R6, R6, -1    ;ROOM FOR #2
  AND R3, R3, 0
  ADD R3, R3, #2    ; R3 = 2
  STR R3, R6, 0   ;STORED THE NUMBER 2

  ADD R6, R6, -1    ;MAKE ROOM FOR PARAMS FOR DIV 
  STR R4, R6, 0   ;STORE N
  
  JSRR R0     ;CALL DIVIDE
        ;ON RETURN, R6 POINTING TO RET VAL. STORE IN R0
        ;THEN IN lv DIV
  LDR R1, R6, 0
  ADD R6, R6, 3   ;MOVE BACK TO PLACE
  
        ;now do mod = n%2 == n & 1
  LDR R4, R5, 4   ;LOAD IN N
  ;LDR R4, R4, 0
  AND R3, R3, 0   
  ADD R3, R3, 1   ;R3 = 1
  
  AND R2, R3, R4    ;MOD ANSWER
  BRZ IFCASE

  ;;ELSE HAPPENS HERE
  LDR R4, R5, 4   ;LOAD IN N
  ;LDR R4, R4, 0
  ADD R3, R4, R4    ;R4*2
  ADD R3, R3, R4    ;(R3=R4*2) + R4 = R4*3
        ;R3 = 3N
  ADD R3, R3, 1   ;3N + 1
  ADD R6, R6, -1    ;ROOM FOR PARAM
  STR R3, R6, 0   ;STORE IN R6
  JSR converge  

  LDR R2, R6, 0   ;STORE ANSWER IN R2
  ADD R6, R6, 2
  ADD R2, R2, 1   ;ADD 1
  STR R2, R5, 3   ;STORE RET VAL
  BR BREAKDOWN    ;LEAVE

  IFCASE
        ;STORE PARAMS
  ADD R6, R6, -1
  STR R1, R6, 0   ;R0 HOLDS DIV. STORE IN R6
  JSR converge    ;JUMP
  
  LDR R1, R6, 0   ;STORE ANSWER IN R1
  ADD R1, R1, 1   ;ADD 1
  STR R1, R5, 3   ;STORE RET VAL
  ADD R6, R6, 2
  BR BREAKDOWN    ;LEAVE
  

  BASE
  AND R1, R1, 0   ;STORE 0 IN R0
  STR R1, R5, 3     ;place the return value in the return value place of the stack
  BR BREAKDOWN

BREAKDOWN
  LDR R4, R5, -5 ;restore R4
  LDR R3, R5, -4 ;restore R3
  LDR R2, R5, -3 ;restore R2
  LDR R1, R5, -2 ;restore R1
  LDR R0, R5, -1 ;restore R0
  ADD R6, R5, 0 ;bring R6 back down to R5
  LDR R5, R6, 1 ;restore old frame pointer
  LDR R7, R6, 2 ;restore return address
  ADD R6, R6, 3 ;have R6 point to the return value
  RET


STACK    .fill xF000
DIV_ADDR .fill x6000 ;; Call the divide subroutine at
                     ;; this address!

.end

;;====================================================
;;   divide(n, d): Takes a numerator (n) and
;;                 denominator (d), returning n / d.
;;====================================================
.orig x6000
divide  ;; DO NOT call JSR with this label! Use DIV_ADDR instead!
  .fill x1DBD
  .fill x7F81
  .fill x7B80
  .fill x1BBF
  .fill x1DBB
  .fill x7140
  .fill x737F
  .fill x757E
  .fill x777D
  .fill x797C
  .fill x6144
  .fill x6345
  .fill x54A0
  .fill x1620
  .fill x987F
  .fill x1921
  .fill x1903
  .fill x0805
  .fill x14A1
  .fill x987F
  .fill x1921
  .fill x16C4
  .fill x0FF7
  .fill x7543
  .fill x6140
  .fill x637F
  .fill x657E
  .fill x677D
  .fill x697C
  .fill x1D61
  .fill x6B80
  .fill x1DA1
  .fill x6F80
  .fill x1DA1
  .fill xC1C0
.end
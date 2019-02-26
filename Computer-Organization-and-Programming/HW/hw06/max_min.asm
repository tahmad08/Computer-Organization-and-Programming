;;====================================
;; CS 2110 - Fall 2018
;; Homework 6
;;====================================
;; Name: Tahirah Ahmad
;;====================================

.orig x3000

LD R0, HEAD_ADDR        ;loading the value of HEAD_ADDR to R0

BRNP ELSE               ;branch into ELSE the head_addr is NOT null
                        ;otherwise, the if-then part is executed below
                        
                        ;this is the if part
LD R1, MAX_INT          ;R1 is a pointer to max_int
LD R2, MIN_INT          ;R2 is a pointer to min_int
ST R1, ANSWER_MIN       ;store the max_int in min
ST R2, ANSWER_MAX       ;store the min_int in max
BRNZP EXIT              ;exit immediately after

ELSE                    ;otherwise i should do the else statement here
AND R1, R1, #0          ;WILL HOLD DATA ADDRESS
AND R2, R2, #0          ;HOLDS DATA (same as r3)
AND R3, R3, #0          ;HOLDS DATA BUT CHANGES TO NEG (same as R2)
AND R4, R4, #0          ;HOLDS MIN
AND R5, R5, #0          ;HOLDS MAX
AND R6, R6, #0          ;HOLDS ARITHM FOR MAX/MIN AND CURR NUMBER

LD R1, HEAD_ADDR        ;LOADS X4000
LDR R3, R1, #1          ;NOW HOLDING X4001 CONTENTS

                        ;INITIALLY LOAD THE FIRST NODES DATA INTO MIN AND MAX
ST R3, ANSWER_MIN       ;STORES FIRST NODE DATA INTO MIN
ST R3, ANSWER_MAX       ;STORES FIRST NODE DATA INTO MAX

WHILEY                   ;START OF WHILE LOOP
LDR R0, R0, #0           ;loads next address
BRNZ EXIT                ;IF NEXT ADDR IS NEG OR ZERO, LEAVE

LDR R2, R0, #1           ;getting the current nodes data
LDR R3, R0, #1           ; same as above

LD R4, ANSWER_MIN        ;LOAD CURRENT MIN INTO R4
NOT R3, R3
ADD R3, R3, #1           ;CONVERT THE CURR DATA TO NEGATIVE

ADD R6, R4, R3           ;-CURR + MIN = POS#, MEANS NEW MIN
BRP NEWMIN               ;BREAK TO NEW MIN PLACE

LD R5, ANSWER_MAX        ;LOAD MAX IN
ADD R6, R5, R3           ;-CURR + MAX = NEG#, MEANS NEW MAX
BRN NEWMAX
BRNZP WHILEY             ;OTHERWISE RETURN TO LOOP START

NEWMIN
ST R2, ANSWER_MIN
BRNZP WHILEY

NEWMAX
ST R2, ANSWER_MAX

BRNZP WHILEY


 

EXIT
HALT


HEAD_ADDR  .fill x4000


MAX_INT    .fill x7FFF
MIN_INT    .fill x8000

ANSWER_MAX .blkw 1
ANSWER_MIN .blkw 1



.end

.orig x4000
  .fill x4002         ;; Node 1 located at x4000, pointing to x4002 where Node 2 is. 
  .fill 4
  .fill x4004         ;; Node 2 located at x4002
  .fill 5
  .fill x4006         ;; Node 3 located at x4004
  .fill 25
  .fill x4008         ;; Node 4 located at x4006
  .fill 1
  .fill x0000         ;; Node 5 located at x4008, points to 0 indicating the end. 
  .fill 10
.end

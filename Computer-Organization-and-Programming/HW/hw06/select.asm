;;====================================
;; CS 2110 - Fall 2018
;; Homework 6
;;====================================
;; Name:Tahirah Ahmad
;;====================================

.orig x3000

;what is this?? who knows!!

AND R4, R4, 0

LD R0, ARRAY_ADDR             ;R0 HOLDS ADDRESS X4000

LD R1, ARRAY_LEN              ;LENGTH FOR I

AND R3, R3, 0                 ;CLEAR
AND R7, R7, 0
ADD R2, R1, 0                 ;R2 IS MEANT TO BE (I--)
                              ;R2 WILL DECREMENT FOR EACH I LOOP.

ILOOP
ADD R2, R2, #-1               ;DECREMENT I--
BRN EXIT                      ;ZERO IS END OF LOOP
ADD R3, R2, #0                ;START OF J LOOP(BEHIND J IS SORTED)  
ST R2, IHOLD
  
JLOOP
ADD R3, R3, #-1               ;DECREMENT J--
BRN ILOOP
ST R3, JHOLD
                              ;CALC ADDRESS OF J LOOP PLACE
                              ;FIRST FLIP CURRENT J VAL
NOT R3, R3
ADD R3, R3, 0
ADD R4, R3, R1

ADD R5, R4, R0
                              ;R5 CONTAINS ADDRESS WE ARE LOOKING AT IN J
                              ;STORE ADDRESS IN J FILL FOR NOW
ST R5, J
LDR R6, R5, #0
                              ;R6 HAS NUMBER AT ARR[J]
ST R6, JNUM                   ;HOLDS J NUMBER

                              ;NOW GET NUMBER FOR ARR[I]
NOT R2, R2
ADD R2, R2, 0
ADD R4, R2, R1
ADD R5, R4, R0
ST R5, I

LDR R7, R5, 0                 ;HOLDS I NUMBER
ST R7, INUM

                              ;CHECK FOR A SWAP
NOT R6, R6
ADD R6, R6, 1
ADD R4, R7, R6
BRP SWAP

ADD R6, R6, #-1
NOT R6, R6
BR UPDATEJ

SWAP
ADD R6, R6, #-1
NOT R6, R6
STI R6, I
STI R7, J
BR UPDATEJ


UPDATEJ
ADD R2, R2, 0
NOT R2, R2
ADD R3, R3, #0
NOT R3, R3
BR JLOOP    ;GO TO NEXT J LOOP WHEN THIS J LOOP FIN

EXIT
HALT
IHOLD .blkw 1
JHOLD .blkw 1
JCOUNT .blkw 1
JNUM .blkw 1
INUM .blkw 1

ARRAY_ADDR .fill x4000
ARRAY_LEN  .fill 10
I .fill 0
J .fill 0

.end

.orig x4000
  .fill 7
  .fill 18
  .fill 0
  .fill 5
  .fill 9
  .fill 25
  .fill 1
  .fill 2
  .fill 10
  .fill 6
.end
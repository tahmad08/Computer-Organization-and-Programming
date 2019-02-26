
;;====================================================
;; CS 2110 - Fall 2018
;; Timed Lab 3
;; timedlab3.asm
;;====================================================
;; Name: Tahirah Ahmad
;;====================================================

.orig x3000

LD R0, STR_ADDR		;HOLDS THE ADDRESS
LDR R1, R0, 0		;HOLDS THE CURR LETTER
BRZ EXIT
AND R2, R2, 0		;CHECKER
LD R5, CONST57		;HOLDS THE NUMBER -57
LD R7, CONST48		;HOLDS NUMBER -48
LD R6, SPACE		;HOLDS ASCII FOR SPACE


LOOP

LDR R1, R0, 0		;LOAD IN LETTER
BRZ EXIT			;IF ITS ZERO, AT END, SO LEAVE

ADD R2, R1, R7		;SUBTRACT 48 TO SEE IF ITS A NUMBER OR NOT
BRN REPLACE			;NEGATIVE MEANS ITS A NUMBER

ADD R2, R1, R5		;SUBTRACT 57 TO SEE IF ITS A NUMBER OR NOT
BRP REPLACE			;POSITIVE MEANS ITS A NUMBER

ADD R0, R0, 1		;INCREMENT THROUGH STRING
BR LOOP

REPLACE
STR R6, R0, 0		;replace with a space
					;STR goes to addr in R0, adds const(0 here) + puts what's in R6 in that addr in memory
ADD R0, R0, 1		;increment address
BR LOOP


EXIT
HALT

CONST57	.FILL #-57
CONST48 .FILL #-48
SPACE	.FILL #32

STR_ADDR .fill x5000
.end

.orig x5000
  .stringz "asdfasdfasdf"
.end



















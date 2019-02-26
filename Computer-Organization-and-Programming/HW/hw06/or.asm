;;====================================
;; CS 2110 - Fall 2018
;; Homework 6
;;====================================
;; Name: Tahirah Ahmad
;;====================================

.orig x3000

AND R0, R0, #0	; clear 
LD  R0, A		; load in A to R0

AND R1, R1, #0	; clear 
LD  R1, B		; load b

NOT R0, R0		; Flip A (~A)
NOT R1, R1		; flip B (~B)

AND R3, R3, #0  ;clear
AND R3, R0, R1	;and a and b
NOT R3, R3		; ~(A&B)
ST  R3, ANSWER	;
HALT			; stop running
		
A      .fill x1010
B      .fill x0404

ANSWER .blkw 1

.end

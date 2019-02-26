;;====================================
;; CS 2110 - Fall 2018
;; Homework 6
;;====================================
;; Name: Tahirah Ahmad
;;====================================

.orig x3000

;R0 BE THE COUNTER/checker
;R1 BE THE CURRENT ARRAY PLACE
;R2 BE THE SUM
;R3 HELPS CHECK IF WE ARE IN ARRAY STILL
;R4 LOADS WHATS AT THE R1 ADDRESS

AND R0, R0, 0
AND R2, R2, 0
LD R1, ARRAY_ADDR     ;
ST R1, CURR           ;JUST SHOWS ME THE CURR ADDRESS
LD R0, ARRAY_LEN      ;DECREMENTS AS R1 INCRMENETS, STOPS AT 0/N

LOOP

ST R1, CURR           ;just to show me where i am in array addr
LDR R4, R1, 0         ;LOAD ARR[I] INTO R4
BRZP NOTNEG           ;IF NOT NEG, SKIP TO OTHER OPS

ADD R2, R2, R4        ;ADD THE NEG NUMBER TO THE SUM HOLDER, R2
ST R2, SUM            ;JUST SHOWS ME WHAT CURR SUM IS

NOTNEG                ;IF NOT A NEG NUMBER
ST R4, I              ;JUST SHOWS ME WHERE I AM IN ARRAY
ADD R1, R1, #1        ;INCREMENT THE ARRAY PTR

                      ;CHECK IF R0 IS STILL LESS THAN THE LENGTH
ADD R0, R0, #-1       ;DECREMENT CHECKER
BRNZ EXIT             ;IF CHECKER IS ALL THE WAY DOWN
                      ;THEN WE'VE TRAVERSED AND WE END

BRNZP LOOP            ;ELSE, LOOP

EXIT
ST R2, ANSWER         ;STORE FINAL ANSWER

HALT


ARRAY_ADDR .fill x4000
ARRAY_LEN  .fill 10

ANSWER     .blkw 1
SUM    .BLKW 1
CURR     .BLKW 1
I    .BLKW 1

.end

.orig x4000
  .fill 7
  .fill -18
  .fill 0
  .fill 5
  .fill -9
  .fill 25
  .fill 1
  .fill -2
  .fill 10
  .fill -6
.end
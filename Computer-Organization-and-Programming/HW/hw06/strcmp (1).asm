;;====================================
;; CS 2110 - Fall 2018
;; Homework 6
;;====================================
;; Name:
;;====================================

.orig x3000

    AND R1, R1, 0
    AND R2, R2, 0
    AND R7, R7, 0

    LD R5, STR_ADDR_1
    LD R6, STR_ADDR_2

    LOOP 
      LDR R1, R5, 0           ;R1 HOLDS THE LETTER IN STR1
      LDR R2, R6, 0           ;R2 HOLDS LETTER IN STR2
      AND R7, R7, 0
      ADD R7, R1, R2          ;CHECK IF THE LETTERS ARE AT END

      BRz END_LOOP            ;IF ZERO, END

      NOT R2, R2              ;FLIP R2, 
      ADD R2, R2, 1
      ADD R1, R1, R2          ;STORE RESULT OF R1-R2 IN R1

      ADD R1, R1, 0
      BRnz SKIP              ;IF NEG OR ZERO GO TO SKIP
        AND R1, R1, 0
        ADD R1, R1, 1
        BRnzp END_LOOP
      SKIP NOP
      ADD R1, R1, 0
      BRzp SKIP2
        AND R1, R1, 0
        ADD R1, R1, -1
        BRnzp END_LOOP
      SKIP2 NOP
      ADD R5, R5, 1
      ADD R6, R6, 1
      BR LOOP
    END_LOOP

  ST R1, ANSWER



HALT

STR_ADDR_1 .fill x4000
STR_ADDR_2 .fill x4050

ANSWER     .blkw 1

.end

.orig x4000
  .stringz "This is a test"
.end

.orig x4050
  .stringz "This is a rest"
.end
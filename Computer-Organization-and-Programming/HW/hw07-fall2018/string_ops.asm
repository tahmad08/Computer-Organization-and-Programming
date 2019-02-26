;;====================================
;; CS 2110 - Fall 2018
;; Homework 7
;; string_ops.asm
;;====================================
;; Name: Tahirah Ahmad
;;====================================

; Little reminder from your pals: don't run this directly by pressing
; ``Run'' in complx, since (look below) there's nothing put at address
; x3000. Instead, load it and use ``Debug'' -> ``Simulate Subroutine
; Call'' and choose the ``strlen'' label.

.orig x3000

halt

strlen
    ADD R6, R6, -3          ;initialize space for everything
    STR R7, R6, 1           ;store RA
    STR R5, R6, 0           ;store old FP
    ADD R6, R6, -4          ;initialize space for registers
    ADD R5, R6, 3           ;place new FP
    STR R0, R6, 3           ;store R0 on the stack
    STR R1, R6, 2           ;store R1 on the stack
    STR R2, R6, 1           ;store R2 on the stack
    STR R3, R6, 0           ;store R3 on the stack

    LDR R0, R5, 4           ;load the address of string into R0
    AND R1, R1, 0           ;reset R1 to 0, it'll be the length

LOOPSTRING
    ADD R2, R0, R1          ;R2 -> address of current character
    LDR R2, R2, 0           ;R2 -> value of current character

    BRZ ENDSTRING           ;if value of character is 0, reached the end

    ADD R1, R1, 1           ;increment string length
    BR LOOPSTRING

ENDSTRING
    STR R1, R5, 3           ;store strlen at the return value spot


TEARDOWN
    LDR R3, R6, 0           ;reload R3
    LDR R2, R6, 1           ;reload R2
    LDR R1, R6, 2           ;reload R1
    LDR R0, R6, 3           ;reload R0

    ADD R6, R6, 4           ;add the stack pointer
    LDR R5, R6, 0           ;reload old FP
    LDR R7, R6, 1           ;reload return address
    ADD R6, R6, 2           ;put the stack pointer at the rv
    RET

;;--------------------------------------------------      

count_occurrence
    ADD R6, R6, -4          ;initialize space for everything
    STR R7, R6, 2           ;store RA
    STR R5, R6, 1           ;store old FP
    ADD R5, R6, 0           ;set current frame pointer
    ADD R6, R6, -5          ;initialize space for registers
    STR R0, R6, 4           ;store R0 on the stack
    STR R1, R6, 3           ;store R1 on the stack
    STR R2, R6, 2           ;store R2 on the stack
    STR R3, R6, 1           ;store R3 on the stack
    STR R4, R6, 0           ;store R4 on the stacK

                            ;prep for strlen by moving R6 "accordingly" and then by setting params 
    
    LDR R1, R5, 4           ;PARAM AT R5+5, LOAD INTO R0
    ADD R6, R6, -1          ;MAKE ROOM FOR THE ARG FOR STRLEN

    STR R1, R6, 0           ;R0 HAD ADDR OF STRING PARAM, NOW PUT IT WHERE R6 IS       
    JSR strlen              ;JUMP
                            ;NOW R6 SHOULD BE POINTING TO THE ANSWER STRLEN
        
    LDR R0, R6, 0           ;STORE THE STRLEN FROM R6 INTO R0
                            ;NOW RETURN R6 TO WHERE IT SHOULD BE POINTING
    ADD R6, R6, 2           ; 

                            ;NOW I SHOULD BE ABLE TO DO MY COUNT STUFF
    LDR R1, R5, 5           ;LOAD IN THE CHAR TO R1
    ;;LDR R1, R1, 0
    LDR R2, R5, 4           ;LOAD IN THE STRING LOCATION

    AND R4, R4, 0           ;WILL BE THE COUNTER

LOOPY
    ADD R0, R0, 0           ;CHECK STR LENGTH
    BRNZ ENDLOOP

    LDR R3, R2, 0           ;LOAD IN THE CURRENT CHARACTER

                            ;COMPARE THEM
    NOT R3, R3,
    ADD R3, R3, 1           ;MAKE CURR CHAR NEGATIVE
    ADD R3, R3, R1           ;ADD THEM

    BRZ INCREMENT

    ;;IF NO INCREMENT, JUST INCREASE ADDRESS AND LOOP
    ADD R2, R2, 1
    ADD R0, R0, -1
    BR LOOPY


    INCREMENT 
    ADD R4, R4, 1           ;INCREASE COUNT
    ADD R2, R2, 1
    ADD R0, R0, -1          ;DECREMENT STR LENGTH
    BR LOOPY

    ENDLOOP
    STR R4, R5, 3           ;STORE THE ANSER (COUNT) IN RET VAL

TEARDOWN2
    LDR R4, R5, -5              ;restore R4
    LDR R3, R5, -4              ;restore R3
    LDR R2, R5, -3              ;restore R2
    LDR R1, R5, -2              ;restore R1
    LDR R0, R5, -1              ;restore R0
    ADD R6, R5, 0               ;bring R6 back down to R5
    LDR R5, R6, 1               ;restore old frame pointer
    LDR R7, R6, 2               ;restore return address
    ADD R6, R6, 3               ;have R6 point to the return value
    RET



; Needed by Simulate Subroutine Call in complx
STACK .fill xF000
.end


; You should not have to LD from any label, take the
; address off the stack instead :)

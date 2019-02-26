;;====================================
;; CS 2110 - Fall 2018
;; Homework 7
;; buildheap.asm
;;====================================
;; Name: Tahirah Ahmad
;;====================================

; Little reminder from your pals: don't run this directly by pressing
; ``Run'' in complx, since (look below) there's nothing put at address
; x3000. Instead, load it and use ``Debug'' -> ``Simulate Subroutine
; Call'' and choose the ``strlen'' label.

.orig x3000

halt

heapify
	ADD R6, R6, -4
	STR R7, R6, 2           	;store RA
	STR R5, R6, 1           	;store old FP
	ADD R5, R6, 0           	;set current frame pointer
	ADD R6, R6, -5				;move r6 TO STORE REGS
	STR R0, R6, 4           	;store R0 on the stack
	STR R1, R6, 3           	;store R1 on the stack
	STR R2, R6, 2           	;store R2 on the stack
	STR R3, R6, 1           	;store R3 on the stack
	STR R4, R6, 0           	;store R4 on the stack
	
	ADD R6, R6, -1				;ROOM FOR LOC VAR LARGEST
	LDR R0, R5, 6
	STR R0, R6, 0				;VAR I
	
	ADD R6, R6, -1				;ROOM FOR LV LEFTCHILD
	LDR R0, R5, 6
	ADD R0, R0, R0				;2I
	ADD R0, R0, 1				;2I + 1
	STR R0, R6, 0				;VAR LEFT

	ADD R6, R6, -1				;ROOM FOR LV RIGHTCHILD
	LDR R0, R5, 6
	ADD R0, R0, R0				;2I
	ADD R0, R0, 2				;2I + 2
	STR R0, R6, 0				;VAR RIGHT
	
								;;----IF LEFTCHILD < N---
CHECKLEFT
	LDR R0, R6, #1				;LOAD IN LEFT TO R0
	LDR R1, R5, 5				;LOAD IN THE LENGTH
	NOT R1, R1,
	ADD R1, R1, 1				;MAKE LENGTH NEG FOR CHECK
	ADD R1, R1, R0
	BRZP CHECKRIGHT				;IF -LEN + LEFT = P, THEN OOB AND GO TO RIGHT
	
								;;IF ARR[LEFT]>ARR[LARGEST], LARGEST=LEFT.
	
	LDR R2, R6, 2				;R6+2 IS WHERE LARGEST IS
	LDR R1, R5, 4				;LOAD IN ARR ADR
	ADD R0, R1, R0				;GO TO LEFT ADDR
	LDR R0, R0, 0				;NOW HAS LEFT VAL
	ADD R2, R1, R2				;LOAD IN LARGEST ADDR
	LDR R1, R2, 0				;LOAD IN THE LARGEST VAL
								;;R1 = LARGESTV, R0 = LEFTV
								;;NOW COMPARE
	NOT R1, R1,
	ADD R1, R1, 1
	ADD R1, R0, R1				;;-LARGEST+LEFT
	BRNZ CHECKRIGHT				;;IF LARGEST > LEFT, SKIP TO CHECKRIGHT
								;;ELSE, LARGEST = LEFT
	LDR R2, R6, 1				;;LOADED IN LEFT AGAIN
	STR R2, R6, 2				;;REPLACED LARGEST WITH LEFT

	BR CHECKRIGHT				;;NOW GO TO RIGHT
	
CHECKRIGHT
	LDR R0, R6, #0				;LOAD IN RIGHT TO R0 (INDEX VAL)
	LDR R1, R5, 5				;LOAD IN THE LENGTH
	NOT R1, R1,
	ADD R1, R1, 1				;MAKE LENGTH NEG FOR CHECK
	ADD R1, R1, R0
	BRZP CHECKI					;IF -LEN + RIGHT = P, THEN OOB AND GO TO CHECKI
	
	;;IF ARR[RIGHT]>ARR[LARGEST], LARGEST=RIGHT. ;RIGHT INDEX IN R0 STILL
	
	LDR R2, R6, 2				;R6+2 IS WHERE LARGEST INDEX
	LDR R1, R5, 4				;LOAD IN ARR ADR 
	ADD R0, R1, R0				;GO TO RIGHT ADDR
	LDR R0, R0, 0				;NOW HAS RIGHT VAL
	ADD R2, R1, R2				;LOAD IN LARGEST ADDR
	LDR R1, R2, 0				;LOAD IN THE LARGEST VAL
								;;R1 = LARGESTV, R0 = RIGHTV
								;;NOW COMPARE
	NOT R1, R1,
	ADD R1, R1, 1
	ADD R1, R0, R1				;;-LARGEST+LEFT
	BRNZ CHECKI					;;IF LARGEST>RIGHT, SKIP TO CHECKI
								;;ELSE, LARGEST = RIGHT
	LDR R2, R6, 0				;;LOADED IN RIGHT AGAIN
	STR R2, R6, 2				;;REPLACED LARGEST WITH LEFT

	BR CHECKI					;;NOW GO TO RIGHT
CHECKI
								;;LOAD IN LARGEST AND I, COMPARE
	LDR R0, R5, 6				;;CURRENT I INDEX
	LDR R1, R6, 2				;;CURRENT "LARGEST" INDEX
	
								;;CHECK IF I==LARGEST
	NOT R0, R0, 
	ADD R0, R0, 1
	ADD R0, R0, R1				;;-I+LARGEST
	BRZ EXIT					;; IF ZER0, NO NEED TO HEAPIFY. FIN WITH STACK
								;;LOAD IN ADDRESS OF ARR
	LDR R0, R5, 6				;;RESET R0 TO I INDEX
	LDR R2, R5, 4				;;R2=ADDR
	ADD R0, R0, R2				;;I ADDRESS
	LDR R3, R0, 0				;;I VAL TO R3

	ADD R1, R1, R2				;;LARGEST ADDR
	LDR R4, R1, 0				;;LARGEST VAL
		
								;;SWAP
	STR R4, R0, 0				;R4=LARGEST VAL. GO TO IADDR AND PUT LARGEST VAL THERE
	STR R3, R1, 0				;R3 = IVAL, GO TO LARGESTADDR AND PUT IVAL THERE
	
				;;RECURSIVE CALL
				;1ST STORE PARAMS at top of stack
	
	ADD R6, R6,-1				;ROOM FOR PARAM I
	LDR R0, R6, 3				;GET I
	STR R0, R6, 0				;STORE I

	ADD R6, R6,-1				;ROOM FOR PARAM LEN
	LDR R0, R5, 5				;GET LEN
	STR R0, R6, 0				;STORE LEN

	ADD R6, R6,-1				;ROOM FOR PARAM ARR
	LDR R0, R5, 4				;GET ARR
	STR R0, R6, 0				;STORE ARR
	
					;;PARAMS SET
	JSR heapify 				;call heapify
	
								;;on return, r6 is at ret val. reset it
	LDR R0, R6, 0
	ADD R6, R6, 4

EXIT
	STR R0, R5, 3				;this func returns void so storing val is unneeded 
								;but for convention, i'm doing it
	BR BREAKDOWN
	

BREAKDOWN
	LDR R4, R5, -5 				;restore R4
	LDR R3, R5, -4 				;restore R3
	LDR R2, R5, -3 				;restore R2
	LDR R1, R5, -2 				;restore R1
	LDR R0, R5, -1 				;restore R0
	ADD R6, R5, 0 				;bring R6 back down to R5
	LDR R5, R6, 1 				;restore old frame pointer
	LDR R7, R6, 2 				;restore return address
	ADD R6, R6, 3 				;have R6 point to the return value
	RET

buildheap

	ADD R6, R6, -4
	STR R7, R6, 2           	;store RA
	STR R5, R6, 1           	;store old FP
	ADD R5, R6, 0           	;set current frame pointer
	ADD R6, R6, -5				;move r6 TO STORE REGS
	STR R0, R6, 4           	;store R0 on the stack
	STR R1, R6, 3           	;store R1 on the stack
	STR R2, R6, 2           	;store R2 on the stack
	STR R3, R6, 1           	;store R3 on the stack
	STR R4, R6, 0           	;store R4 on the stack

	LDR R0, R5, 4				;R0 = ARR
	LDR R1, R5, 5				;R1 = N
	LDR R3, R5, 5				;N COUNTER
	LDR R2, R5, 5
	
	
LOOPY
	ADD R2, R2, 0				;END LOOP WHEN N IS -1
	BRN BREAKDOWN_BREAKDOWN
	
	ADD R6, R6, -1				;PARAM I
	STR R2, R6, 0
	
	ADD R6, R6, -1				;PARAM LEN N
	LDR R1, R5, 5
	STR R1, R6, 0

	ADD R6, R6, -1				;PARAM ARR
	LDR R0, R5, 4
	STR R0, R6, 0

	JSR heapify
	
	ADD R6, R6, 4				;RETURN R6 TO START
	ADD R2, R2, -1				;DEC I
	BR LOOPY
	
BREAKDOWN_BREAKDOWN
	LDR R4, R5, -5 				;restore R4
	LDR R3, R5, -4 				;restore R3
	LDR R2, R5, -3 				;restore R2
	LDR R1, R5, -2 				;restore R1
	LDR R0, R5, -1 				;restore R0
	ADD R6, R5, 0 				;bring R6 back down to R5
	LDR R5, R6, 1 				;restore old frame pointer
	LDR R7, R6, 2 				;restore return address
	ADD R6, R6, 3 				;have R6 point to the return value
	RET

; Needed by Simulate Subroutine Call in complx
STACK .fill xF000
.end

; You should not have to LD from any label, take the
; address off the stack instead :)

		.orig	x3000
		LD		R6, STACK
		LD		R0, N

		ADD		R6, R6, -1
		STR		R0, R6, 0

		JSR		FACT

		LDR		R0, R6, 0

		ADD		R6, R6, 2
		HALT
		

N		.fill	7
STACK	.fill	x4000



FACT		ADD	R6, R6, -4; Allocate space rv,ra,fp,lv1
		STR	R7, R6, 2	; Save Ret Addr
		STR	R5, R6, 1	; Save Old FP
		ADD	R5, R6, 0	; Copy SP to FP
		ADD	R6, R6, -2; Make room for saved regs
		STR 	R0, R5, -1	
		STR 	R1, R5, -2	

;if (n <= 0) {
		LDR	R0, R5, 4	; n <= 0
		BRP	IFELSE1
;	answer = 1;
		AND	R0, R0, 0	
		ADD	R0, R0, 1	
		STR	R0, R5, 0
;} else {	
		BR	ENDIF1
;	answer = n * fact(n-1);
; rewrite: R0 = fact(n-1);answer = mult(n, R0);
IFELSE1	LDR	R0, R5, 4	; Push n-1
		ADD	R0, R0, -1
		ADD	R6, R6, -1
		STR	R0, R6, 0
		JSR	FACT		; fact(n-1)
		LDR	R0, R6, 0	; R0 = rv
		ADD	R6, R6, 2	; Pop rv and arg1
; 	answer = mult(n, R0)
		ADD	R6, R6, -1; Push R0
		STR	R0, R6, 0
		ADD 	R6, R6, -1; Push n
		LDR	R0, R5, 4
		STR	R0, R6, 0
		JSR 	MULT		; mult(n, R0)
		LDR 	R0, R6, 0	; answer = rv
		STR	R0, R5, 0	;
		ADD	R6, R6, 3 ; Pop rv and arg1-2
ENDIF1	NOP
; }
		



		LDR	R0, R5, 0 ; Put answer in a reg
		STR	R0, R5, 3	; Put answer in RV space
		LDR	R0, R5, -1; Restore R0
		LDR	R1, R5, -2; Restore R1
		ADD	R6, R5, 0	; Restore SP
		LDR	R5, R6, 1	; Restore FP
		LDR	R7, R6, 2	; Restore RA
		ADD	R6, R6, 3	; Pop ra,fp,lv1
		RET




MULT		ADD	R6, R6, -4; Allocate space rv,ra,fp,lv1
		STR	R7, R6, 2	; Save Ret Addr
		STR	R5, R6, 1	; Save Old FP
		ADD	R5, R6, 0	; Copy SP to FP
		ADD	R6, R6, -3; Make room for saved regs
		STR 	R0, R5, -1	
		STR 	R1, R5, -2	
		STR 	R2, R5, -3	

; R0 = 0
		AND	R0, R0, 0
; R1 = arg1
		LDR	R1, R5, 4
; R2 = arg2
		LDR	R2, R5, 5
; while (R1 > 0) {
WHILE2		ADD	R1, R1, 0
		BRNZ	ENDWHILE2
;	R0 += R2
		ADD	R0, R0, R2
;	R1 -= 1
		ADD	R1, R1, -1
; }
		BR	WHILE2
; answer = R0
ENDWHILE2	STR	R0, R5, 0


		LDR	R0, R5, 0 ; Put answer in a reg
		STR	R0, R5, 3	; Put answer in RV space
		LDR	R0, R5, -1; Restore R0
		LDR	R1, R5, -2; Restore R1
		LDR	R2, R5, -3
		ADD	R6, R5, 0	; Restore SP
		LDR	R5, R6, 1	; Restore FP
		LDR	R7, R6, 2	; Restore RA
		ADD	R6, R6, 3	; Pop ra,fp,lv1
		RET


		.end

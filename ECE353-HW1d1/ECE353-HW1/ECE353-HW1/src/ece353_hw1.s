; Filename:     ece353_hw1.s 
; Author:       ece353 staff 
; Description:  

    export hw1
    export TRANSACTIONS_TOTAL
    export TRANSACTIONS
    export PERSON1
    
;**********************************************
; SRAM
;**********************************************
    AREA    SRAM, READWRITE

TRANSACTIONS SPACE 1000*8
TRANSACTIONS_TOTAL SPACE 12
	align
        
;**********************************************
; Constant Variables (FLASH) Segment
;**********************************************
    AREA    FLASH, CODE, READONLY
PERSON1     DCB     "AMR HASSABALLAH"
            DCB     0
    align

;**********************************************
; Code (FLASH) Segment
; main assembly program
;**********************************************
hw1   PROC
    
    PUSH {R0-R12, LR}
    ; DO NOT MODIFY ANTHING ABOVE THIS LINE!!!
    ; DO NOT MODIFY REGISTERS R13-R15!!!
    
	; loading address and constants
	
	LDR R0, =(TRANSACTIONS)
	MOV R11, #0  ; R11 will be our transaction counter 
	MOV R4, #0
	MOV R2, #0  ; ussed at the end of DEPOSIT/WITHDRAWL
	
	; Validating Transactions
	
WHILE_START

	; sequence of transactions end if counter reaches 1000
	ADD R11, R11, #1
	CMP R11, #1000
	LDREQ R3, =(WHILE_DONE)
	BXEQ R3
	
	LDRB R1, [R0]; R1 holds the content stored at address in R0
	
	; sequence of transactions end if first byte is 0
	CMP R1, #0;
	LDREQ R3, =(WHILE_DONE)
	BXEQ R3

	CMP R1, #0x30
	BEQ ERROR
	;;Checking if first byte a + or a - ;;

	CMP R1, #0x2B;
	CMPNE R1, #0x2D;
	BNE ERROR

	;;Checking if second byte is a number ;;
	; must be between and including 0x30 and 0x39

							; pointing to next character
	LDRB R1, [R0, #1]       ; Updating R1 with new content

	CMP R1, #0x30
	BLT ERROR
	CMPGT R1, #0x39
	BGT ERROR

	; 3rd and 4th byte 

							; pointing to next character
	LDRB R1, [R0, #2]       ; Updating R1 with new content

	CMP R1, #0x30
	BLT ERROR
	CMPGT R1, #0x39
	BGT ERROR

							; pointing to next character
	LDRB R1, [R0, #3]        ; Updating R1 with new content

	CMP R1, #0x30
	BLT ERROR
	CMPGT R1, #0x39
	BGT ERROR

	;; Check if 5th byte decimal 0x2E

						  ; pointing to next character
	LDRB R1, [R0, #4]     ; Updating R1 with new content

	CMP R1, #0x2E
	BNE ERROR

	;; 6th/7th bytes

						  ; pointing to next character
	LDRB R1, [R0, #5]     ; Updating R1 with new content

	CMP R1, #0x30
	BLT ERROR
	CMPGT R1, #0x39
	BGT ERROR


						  ; pointing to next character
	LDRB R1, [R0, #6]     ; Updating R1 with new content

	CMP R1, #0x30
	BLT ERROR
	CMPGT R1, #0x39
	BGT ERROR

	;; TESTING LAST BIT IS NULL THEN SENDING DEPOSIT/WITHDRAWL

							; pointing to next character
	LDRB R1, [R0, #7]       ; Updating R1 with new content

	CMP R1, #0x00
	BNE ERROR

	;; implementing deposits and withdrawls ;;
	; done after making sure non of the transactions have an error
	
	LDRB R1, [R0]; moving back to +/- byte
	
	CMP R1, #0x2B;
	BEQ DEPOSIT
	CMP R1, #0x2D;
	BEQ WITHDRAWL

ERROR

 ;; moving calc error into transactions at the event of an error

	LDR R0, =(TRANSACTIONS_TOTAL)
	
	MOV R1, #0x43; C
	STRB R1,[R0]
	
	MOV R1,	#0x41; A
	STRB R1, [R0, #1]
	
	MOV R1, #0x4C; L
	STRB R1, [R0, #2]
	
	MOV R1, #0x43; C
	STRB R1, [R0, #3]
	
	MOV R1, #0x20; Space
	STRB R1, [R0, #4]
	
	MOV R1, #0x45; E
	STRB R1, [R0, #5]
	
	MOV R1, #0x52; R
	STRB R1, [R0, #6]
	
	MOV R1, #0x52; R
	STRB R1, [R0, #7]
	
	MOV R1, #0x4F; O
	STRB R1, [R0, #8]
	
	MOV R1, #0x52; R
	STRB R1, [R0, #9]
	
	MOV R1, #0x00; END WITH NULL
	STRB R1, [R0, #10]
	STRB R1, [R0, #11]
	
	
	B RETURN

DEPOSIT 			; implementing a deposit 

; breaking down each transaction from hex to decimal

	
	LDRB R8,[R0,#6]   		; putting content at least sig fig at adress into R8
	SUB R8, R8, #0x30
	MOV R1, R8 			; R1 will hold the tratransaction R8 is a place holder
							; R8 is a place holder
	
	
	LDRB R8, [R0, #5]		; second last sig fig	
	SUB R8, R8, #0x30
	MOV R7, #10
	MUL R8, R8, R7 			; moving value to 2nd least sig fig position
	ADD R1, R1, R8 			; now R1 hold last and second last byte
	
	
	LDRB R8, [R0, #3]		; 3rd last sig fig -skipping the decimal
	SUB R8, R8, #0x30
	MOV R7, #100
	MUL R8, R8, R7 			; moving value to 3rd least sig fig position
	ADD R1, R1, R8 			; now R1 holds last 3 sig figs
	
	LDRB R8, [R0, #2]       ; 4th last sig fig 
	SUB R8, R8, #0x30
	MOV R7, #1000
	MUL R8, R8, R7			; moving value to 4th least sig fig position
	ADD R1, R1, R8			; now R1 holds last 4 sig figs
	
	LDRB R8, [R0, #1]		; Most sig fig
	SUB R8, R8, #0x30
	MOV R7, #10000
	MUL R8, R8, R7			; moving value to most sig fig position
	ADD R1, R1, R8			; now R1 hold the whole transaction
	
	ADD R2, R2, R1			; R2 will hold our total posative values in decimal
	
	ADD R0, R0, #8; 		; Pointing to next transaction before next while iteration
	B WHILE_START
	
WITHDRAWL 			; implementing withdrawl

	LDRB R8,[R0,#6]   		; putting content at least sig fig at adress into R8
	SUB R8, R8, #0x30
	MOV R1, R8 			; R1 will hold the tratransaction R8 is a place holder
							; R8 is a place holder
	
	
	LDRB R8, [R0, #5]		; second last sig fig	
	SUB R8, R8, #0x30
	MOV R7, #10
	MUL R8, R8, R7 			; moving value to 2nd least sig fig position
	ADD R1, R1, R8 			; now R1 hold last and second last byte
	
	
	LDRB R8, [R0, #3]		; 3rd last sig fig -skipping the decimal
	SUB R8, R8, #0x30
	MOV R7, #100
	MUL R8, R8, R7 			; moving value to 3rd least sig fig position
	ADD R1, R1, R8 			; now R1 holds last 3 sig figs
	
	LDRB R8, [R0, #2]       ; 4th last sig fig 
	SUB R8, R8, #0x30
	MOV R7, #1000
	MUL R8, R8, R7			; moving value to 4th least sig fig position
	ADD R1, R1, R8			; now R1 holds last 4 sig figs
	
	LDRB R8, [R0, #1]		; Most sig fig
	SUB R8, R8, #0x30
	MOV R7, #10000
	MUL R8, R8, R7			; moving value to most sig fig position
	ADD R1, R1, R8			; now R1 hold the whole transaction
	
	ADD R4, R4, R1			; R4 will hold our total  negatives in decimal 
	
	ADD R0, R0, #8; 		; Pointing to next transaction before next while iteration
	B WHILE_START			; Starting next iteration


WHILE_DONE

; now R2 has our posative values and R4 has out negatives 
; need to check total is not negative to avoid twos comp notation

	SUB R5, R2, R4
	
; R5 is total if total is negative we need to take its absolute value
	CMP R5, #0
	EORLT R5, R5, #0xFFFFFFFF ; twos comp
	ADDLT R5, R5, #1			

;; now R5 has our total and its time to go from HEX to ASCII
;; will use R8 as place holder and R7 as our divisor to extract 
	
	; check if total is + or -

	MOVLT R8, #0x2D
	MOVGE R8, #0x2B
	
	; put appropriate sign at appropriate destination
	LDR R0, =(TRANSACTIONS_TOTAL)
	STRB R8, [R0];
	
	; inserting $ ascii charecter
	MOV R8, #0x24
	STRB R8, [R0, #1]
	
	; extracting most sig fig
	MOV32 R7, #1000000
	UDIV R8, R5, R7 		; R8 now holds the most sig fig
	MOV R6, R8
	ADD R6, R6, #0x30
	STRB R6, [R0, #2]		; updating TRANS TOTAL
	MUL R8, R8, R7
	SUB R5, R5, R8		
	
	
	
			
	 			; most sig fig removed from R2
	
	; extracting second most sig fig
	MOV32 R7, #100000
	UDIV R8, R5, R7 		; R8 now holds the most sig fig
	MOV R6, R8
	ADD R6, R6, #0x30
	STRB R6, [R0, #3]		; updating TRANS TOTAL
	MUL R8, R8, R7
	SUB R5, R5, R8		
	
	;inserting comma character
	MOV R8, #0x2C
	STRB R8, [R0, #4]
	
	; extracting third most sig fig
	MOV32 R7, #10000
	UDIV R8, R5, R7 		; R8 now holds the next sig fig
	MOV R6, R8
	ADD R6, R6, #0x30
	STRB R6, [R0, #5]		; updating TRANS TOTAL
	MUL R8, R8, R7
	SUB R5, R5, R8		
	
	; extracting 4th SF
	MOV32 R7, #1000
	UDIV R8, R5, R7 		; R8 now holds the next sig fig
	MOV R6, R8
	ADD R6, R6, #0x30
	STRB R6, [R0, #6]		; updating TRANS TOTAL
	MUL R8, R8, R7
	SUB R5, R5, R8		
	
	; extracting 5th SF
	MOV32 R7, #100
	UDIV R8, R5, R7 		; R8 now holds the next sig fig
	MOV R6, R8
	ADD R6, R6, #0x30
	STRB R6, [R0, #7]		; updating TRANS TOTAL
	MUL R8, R8, R7
	SUB R5, R5, R8		
	
	; inserting dot char
	MOV R8, #0x2E
	STRB R8, [R0, #8]
	
	; extracting 6th most sig fig
	MOV32 R7, #10
	UDIV R8, R5, R7 		; R8 now holds the next sig fig
	MOV R6, R8
	ADD R6, R6, #0x30
	STRB R6, [R0, #9]		; updating TRANS TOTAL
	MUL R8, R8, R7
	SUB R5, R5, R8		
	
	ADD R5, R5, #0x30		; going from int to ascii
	STRB R5, [R0, #10]		; updating last sig fig
	
	MOV R7, #0x00
	STRB R7, [R0, #11]      ; updating last byte with NULL
	

	
    ; DO NOT MODIFY ANTHING BELOW THIS LINE!!!        
RETURN
    POP {R0-R12, PC}
    
    ENDP
    align
        

    END
        
        

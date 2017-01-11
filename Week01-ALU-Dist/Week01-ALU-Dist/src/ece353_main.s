; Filename:     main.s 
; Author:       ece353 staff 
; Description:  

    export __main

;**********************************************
; SRAM
;**********************************************
    AREA    SRAM, READWRITE
    align
        
;**********************************************
; Constant Variables (FLASH) Segment
;**********************************************
    AREA    FLASH, CODE, READONLY
    align

;**********************************************
; Code (FLASH) Segment
; main assembly program
;**********************************************
__main   PROC
    
    ; DO NOT MODIFY ANTHING ABOVE THIS LINE!!! 
   
    
    ; (1)
    ; Initialize R1 to be 20 (decimal)
    MOV R1, #20
    ; (2)
    ; Add 15 to R1 using an immediate
    ADD R1, R1, #15
    ; (3)
    ; Multiply R1 by 3
	MOV R3, #3
	MUL R1, R1, R3
	
    ; (4)
    ; Clear (set to 0) bits 4:0 of R1
    ; All other bits should not be affected
	BIC R1, R1, #0x1F
    ; (5)
    ; Set bits 31:25 and 21:16 of R1 to be a 1
    ; All other bits should not be affected
    MOVT R4, #0xFE3F
	ORR R1, R1, R4
    ; (6)
    ; Invert ONLY bits 3-9 of R1
	MOV R2, #0x3F1 
	EOR R1, R1,R2
    ; (7) 
    ; Move the contents of R1 to R0
    MOV R0, R1
    ; (8) 
    ; Total the bytes in R0 and place the results in R2
    ; R2 = R0[31:24] + R0[23:16] + R0[15:8] + R0[7:0]
    ; Treat each byte an an unsigned 8-bit number
    MOV32 R5, #0xFFFFFF00
	BIC R6, R1, R5
	
	MOV R5, #0xFFFF00FF
    BIC R7, R1, R5
	LSR R7, R7, #2
	
	MOV R5, #0xFF00FFFF
	BIC R8, R1, R5
	LSR R8, R8, #4
	
	MOV R5, #0xFFFFFF
	BIC R9, R1, R5
	LSR R9, R9, #6
	
	ADD R2, R6, R7
	ADD R2, R2, R8
	ADD R2, R2, R9
	
    ; DO NOT MODIFY ANTHING BELOW THIS LINE!!!
        
INFINITE_LOOP
    B   INFINITE_LOOP
    ENDP
    align
        

    END
        
        

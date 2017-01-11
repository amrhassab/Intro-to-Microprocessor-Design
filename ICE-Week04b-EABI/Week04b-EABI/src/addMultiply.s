; Filename:     addMultiply.s 
; Author:       ece353 staff 
; Description:  

    export addMultiply

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
; Four arrays of 8-bit signed numbers are 
; passed via the ; first four paramters.
; The 5th paramter indicates the length of the
; arrays. For each entry in the array, the
; following operation takes place.
;
; Array3[i] = (Array0[i] + Array1[i]) * Array2[i]
;
; Parameter 0       Array Address 0
; Parameter 1       Array Address 1
; Parameter 2       Array Address 2
; Parameter 3       Array Address 3
; Parameter 4       Array Size 
;
; Returns
;   if ALL parameters are valid, return 0
;   else return -1.
;
;  An address is valid if it is non zero
;  The size is valid if it is greater than zero
;**********************************************
addMultiply PROC
    ; Save required registers
	PUSH{R4-R8};
	
    ; Validate Parameters
	LDR R4, [ SP, #20]
	
	CMP R0, #0
	BEQ ERROR
	CMP R1, #0
	BEQ ERROR
	CMP R2, #0
	BEQ ERROR
	CMP R3, #0
	BEQ ERROR
	
	CMP R4, #0
	BLT ERROR
	
	
	
	
    
    ; For each index in the arrays, compute  
    ; Array3[i] = (Array0[i] + Array1[i]) * Array2[i]
	
FOR_START
	
	LDRB R5, [ R0 ], #1
	LDRB R6, [ R1 ], #1
	LDRB R7, [ R2 ], #1
	ADD R8, R5, R6
	MUL R8, R8, R7
	STRB R8, [R3], #1
	SUB R4, R4, #1
	CMP R4, #0
	BNE FOR_START 
	
	
	
  
    ; Restore registers saved to the stack
    POP{R4-R8}
    ; Return from the loop
	MOV R0, #0
	
	BX LR
	
ERROR
	MOVEQ R0, #-1
	
	BX LR

    ENDP


        
    align
        

    END            
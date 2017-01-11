    export insertion_sort
    AREA    FLASH, CODE, READONLY
    ALIGN
    
;******************************************************************************
; Description
; Uses Insertion Sort to sort an array of unsigned 32-bit numbers. Valid
; sizes are 0-1024
; Parameters
; R0 - Array Address
; R1 - Size of the array. 
;
; Returns
;   0 if parameters are valid.  -1 if any of the parameters are invalid. 
;******************************************************************************
insertion_sort             PROC
	
	; maintaining EABI standards
	PUSH { R4 - R8 }
	
	
	
	; checking paramaters ;
	
	; making sure address not < min value specified
	MOV32 R2, #0x20000000
	CMP R0, R2
	BLT PAR_ERROR
	
	; making sure address not > than max value specified
	MOV32 R2, #0x20007FFC
	CMP R0, R2
	BGT PAR_ERROR
	
	; making sure array size is not < 0
	CMP R1, #0
	BLT PAR_ERROR
	
	; making sure array size is not > 1024
	CMP R1, #1024
	BGT PAR_ERROR
	
	; sorting the array
	
    ; R2 represents the number we are at, we start comparison at the 2nd num
    MOV R2, R0
	ADD R2, R2, #4	
	MOV R8, #1              ; c for loop index
		
START_FOR
 
   CMP R8, R1 
   BEQ END_FOR
   MOV R3, R2                 ;address of A[d]
   MOV R7,R8                  ;d while loop index
   
START_WHILE

   LDR R5, [R3]              ; load into R5 what is at address D
   LDR R4, [R3, #-4]	     ; load into R4 what is at address D - 1;
   
   CMP R7, #0               ; while (d > 0 &&
   BEQ END_WHILE
   CMP R5, R4                 ; a[d] < a[d-1])
   BHS END_WHILE

   
   STR R4, [R3]
   STR R5, [R3, #-4]         ; putting back the values into the array
   
   SUB R3, R3, #4
   
   SUB R7 ,R7 ,#1             ; D--
   CMP R7, #0
   BEQ END_WHILE
   B START_WHILE

END_WHILE

 
    ADD R2, R2, #4
	ADD R8, R8, #1
    B START_FOR
    
END_FOR
	
    MOV R0, #0	
    B SUCCESS
	
	; program branches to here if any parameter is invalid
PAR_ERROR

    MOV R0, #-1; return -1 if error
   

SUCCESS

    POP {R4-R8}

    ENDP
    END     

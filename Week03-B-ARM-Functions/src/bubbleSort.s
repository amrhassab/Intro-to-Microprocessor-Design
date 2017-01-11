	
	export bubble_sort
        
    AREA    FLASH, CODE, READONLY
    ALIGN
        

;******************************************************************************
; Description
;     Given the address in R7, it will read the unsigned byte at R7 and R7 + 1.
;     If [R7] > [R7 + 1], swap the values
;
;     Modify only registers R8 or greater.
;
; Parameters
;   R7 - Array Address
;
; Returns
;   Nothing
;******************************************************************************
swap_values PROC
     ;---------------------------------------
     ; START ADD CODE
     ;---------------------------------------
    
     LDRB R8, [R7]; load content at address R7 in to R8 then point to next address
	 LDRB R9, [R7, #1]; R9 now holds content in next address
	 
	 
	 
	 CMP R9, R8
	 STRBLT R9,[R7]
	 STRBLT R8,[R7, #1]
     
     
     BX LR
     
     ;---------------------------------------
     ; END ADD CODE
     ;---------------------------------------
    ENDP


    
;******************************************************************************
; Description
;   Uses Bubble Sort to sort an array of unsigned 8-bit numbers.
;
;   Modify only registers R0-R7
;
; Parameters
;   R0 - Array Address
;   R1 - Array Size
;
; Returns
;   Nothing
;******************************************************************************
bubble_sort PROC

    ; Save registers
     PUSH   {R0-R12, LR}
     
     ;---------------------------------------
     ; START ADD CODE
     ;---------------------------------------
   SUB R1, R1, #1  
OUT_WHILE_START
	
	CMP R1, #0
	BLE OUT_WHILE_END
	MOV R7, R0 ; moving address into R7

IN_WHILE_START
	
	SUB R11, R7, R0
	CMP R11, R1 ; 
	BGT IN_WHILE_END
	BEQ IN_WHILE_END
	

	
	
	
	LDR R10, =(swap_values)
	BLX R10 
	ADD R7,R7, #1
	
	
	
	
	B IN_WHILE_START

IN_WHILE_END

	SUB R1, R1, #1  
	B OUT_WHILE_START
   
OUT_WHILE_END     
     
     ; NOTE: The return from the function is already
     ; provided below
     
     ;---------------------------------------
     ; END ADD CODE
     ;---------------------------------------
     
    
    ; Restore Registers
    POP     {R0-R12, LR}
    
    ; Return from the function
    BX      LR
    
    ENDP
         
    END     


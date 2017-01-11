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
	
;ASCII_ARRAY DCB 'E' 

;**********************************************
; Code (FLASH) Segment
; main assembly program
;**********************************************
__main   PROC
        MOV R0, 'e'
    ; DO NOT MODIFY ANTHING BELOW THIS LINE!!!    
        
INFINITE_LOOP
    B INFINITE_LOOP
    
    ENDP
    align
        

    END            
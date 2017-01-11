; Filename:     main.s 
; Author:       Amr Hassaballah 
; Description:  Day 1 week 2

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
    
    ; Initialization of R0 and R1
    MOV     R0, #15
    MOV     R1, #100
    
    ; Using only conditional instructions (no branches)
    ; Implement the if statemens below.
    
    
    
    ; (1) If R0 == 15, then R2 = 100 , else R2 = 1
	CMP R0, #15
	MOVEQ R2, #100
	MOVNE R2, #1
	
    ; (2) If R0 != 15, then R3 = 200 , else R3 = 2
    
	MOVNE R3, #200
	MOVEQ R3, #2
	
    ; (3) If R0 < 15, then  R4 = 300 , else R4 = 3
	
	MOVMI R4, #300
	MOVGT R4, #3 
	 

    ; (4) If R0 <= 15, then R5 = 400 , else R5 = 4
    
	MOVLE R5, #400
	MOVGT R5, #4
	
    ; (5) If R0 > 15,  then R6 =500 , else R6 = 5
	
	MOVGT R6, #500
	MOVLE R6, #5
    
    ; (6) If R0 >= 15, then R7 = 600 , else R7 = 6
    
	MOVGE R7, #600
	MOVLT R7, #6
    


    MOV     R0, #0x2
    
    ; (7) Implement the following switch statement using only conditional instructions
    
    ; Hint: Start by setting R1 to the default value and then checking all of the
    ; other cases.
    
    ; switch(R0)
    MOV R1, #0xFFFFFFFF
	; {
    ;      case 0:
    CMP R0, #0
	MOVEQ R1, #0
	;      {
    ;           R1 = 0;
    ;           break;
    ;      }
    ;      case 1:
    CMP R0, #1
	MOVEQ R1, #10
	;      {
    ;           R1 = 10;
    ;           break;
    ;      }
    ;      case 2:
    CMP R0, #2
	MOVEQ R1, #20
	;      {
    ;           R1 = 20;
    ;           break;
    ;      }
    ;      case 3:
    CMP R0, #3
	MOVEQ R1, #30
	;      {
    ;           R1 = 30;
	;           break;
    ;      }
    ;      default:
    ;      {
	;           R1 = 0xFFFFFFFF;
    ;           break;
    ;      }
    ;  }
    


    ; Initialization of R0 and R1
    MOV     R0, #15
    MOV     R1, #100
    
    ; (8) If R0 >= 15 OR R1 < 150, then R8 = 700 , else R8 = 7
	MOV R8, #7
	CMP R0, #15
	MOVGE R8, #700
	CMP R1, #150
	MOVNE R8, #700
    
    
    ; (9) If R0 >= 15 AND R1 < 150, then R9 = 800, else R9 = 8
	MOV R9, #8
	CMP R0, #15
	CMPGE R1, #150
	MOVLT R9, #8
	
	
    MOV32   R0, #0xFFF000FF
    ; (10) If bit 2 OR bit 21, then R1 =900 , else R1 <- 9
    MOV R1, #9
	MOV32 R10, #0x00200004
	TST R0, R10
	MOVNE R1, #900
    
    
    ; DO NOT MODIFY ANTHING BELOW THIS LINE!!!	
        
INFINITE_LOOP
    B INFINITE_LOOP
    
    ENDP
    align
        

    END            
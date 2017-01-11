//*****************************************************************************
// main.c
// Author: jkrachey@wisc.edu
//*****************************************************************************
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "TM4C123.h"

#define PF2 (1<<2) // BTN_RIGHT
#define PF3 (1<<3) // BTN_LEFT

volatile bool AlertSysTick = false;

void DisableInterrupts(void)
{
  __asm {
         CPSID  I
  }
}
void EnableInterrupts(void)
{
  __asm {
    CPSIE  I
  }
}

extern void serialDebugInit(void);
extern void gpio_init(void);


//*****************************************************************************
//*****************************************************************************
int main(void)
{
	int countr = 0;
	int countl = 0;
	int data = 0;
  serialDebugInit();
  gpio_init();
  SysTick_Config( 250000 );
	
	
	
  printf("\n\r");
  printf("********************************************\n\r");
  printf("ECE353 - SysTick Interrupt In Class Exercise\n\r");
  printf("*********************************************\n\r");

  // Reach infinite loop
  while(1)
  {
		if (AlertSysTick == true){
			AlertSysTick = false;
			data = GPIOF->DATA;
			
			// if right button is pressed
			if ( (data & PF2) == 0 ){
			
				countr++;
				
		  }else{
				   countr = 0;
			}
			if (countr == 4 ) {
			    printf("right button pressed \n");
			}
			
			
			if ( (data & PF3) == 0 ) {
		
			  countl++;
		    
		   } else {
				 
				 countl=0;
			 }
			 
			 if (countl == 4 ) {
			
			    printf( "left button pressed \n " );
			
		    }
		}
	}
}	
		
		// if left button pressed


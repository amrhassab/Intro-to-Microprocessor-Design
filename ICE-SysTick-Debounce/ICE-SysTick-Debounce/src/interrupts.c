#include "interrupts.h"

extern volatile bool AlertSysTick;

void SysTick_Handler(void){
	
	uint32_t val;
	
 // set the timer to true
	AlertSysTick = true;

	// clears systick interrupt
	
	val = SysTick->VAL;
	
}

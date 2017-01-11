#include "timer0.h"



//*****************************************************************************
// Configure Timer 0 to be two 16-bit, periodic, count down timers.
// Do not set the values for TAILR or TBILR and DO NOT enable the timer.
//*****************************************************************************
void configure_timer0(void){
	
	// turn on clock for the timer0
	SYSCTL->RCGCTIMER |= SYSCTL_RCGCTIMER_R0;
	
	//wait for the timer to turn on 
	while((SYSCTL->PRTIMER & SYSCTL_PRTIMER_R0) == 0) {};
	
	// turn off the timer before configuration
	TIMER0->CTL &= ~(TIMER_CTL_TBEN | TIMER_CTL_TAEN);
	
	// Set the timer to be in 16-bit mode (CFG)
	TIMER0->CFG = TIMER_CFG_16_BIT;
	
		// clear any status bits indicating that the time has expired 
	TIMER0->ICR |= TIMER_ICR_TATOCINT | TIMER_ICR_TBTOCINT;
	
		//Set the Timer A Mode Register to be in periodic mode and count down (TAMR)
	TIMER0->TAMR = TIMER_TAMR_TAMR_PERIOD; 
	TIMER0->TBMR = TIMER_TBMR_TBMR_PERIOD; 
	

		

}

//*****************************************************************************
// Turns on Timer0A and Turns Off Timer0B.  The TAILR is set to load_value
//*****************************************************************************
void start_timer0A(uint16_t load_value){
	
	
	
	stop_timer0B();
	// Set the number of clock cycles in the Timer A Interval Load Register (TAILR)
	TIMER0->TAILR = load_value;
	//enabling timeout interrupts		
	TIMER0->IMR =  TIMER_IMR_TATOIM;
	//enabling timer intterupts using NVIC
	NVIC_EnableIRQ(TIMER0A_IRQn);
	NVIC_SetPriority (TIMER0A_IRQn,2);
	// Enable the A timer (CTL)
	TIMER0->CTL |= TIMER_CTL_TAEN;
	
	
}

//*****************************************************************************
// Turns off Timer0A.  This function does not alter the load value.
//*****************************************************************************
void stop_timer0A(void){
	// Disable the A timer (CTL)
	TIMER0->CTL &= ~(TIMER_CTL_TAEN);
}

//*****************************************************************************
// Turns on Timer0B and Turns Off Timer0A.  The TBILR is set to load_value
//*****************************************************************************
void start_timer0B(uint16_t load_value){
	
	
	stop_timer0A();
	// Set the number of clock cycles in the Timer B Interval Load Register (TAILR)
	TIMER0->TBILR = load_value;
	// clear any status bits indicating that the time has expired 
	//enabling timeout interrupts		
	TIMER0->IMR =  TIMER_IMR_TBTOIM;
	//enabling timer intterupts using NVIC
	NVIC_EnableIRQ(TIMER0B_IRQn);
	NVIC_SetPriority (TIMER0B_IRQn,2);
	// Enable the B timer (CTL)
	TIMER0->CTL |= TIMER_CTL_TBEN;
	
	
	
}

//*****************************************************************************
// Turns off Timer0B.  This function does not alter the load value.
//*****************************************************************************
void stop_timer0B(void){
	// Disable both the B timer (CTL)
	TIMER0->CTL &= ~(TIMER_CTL_TBEN);	
}

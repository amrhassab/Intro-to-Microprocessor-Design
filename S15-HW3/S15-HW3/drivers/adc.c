#include "adc.h"


//*****************************************************************************
// Initializes ADC0 to use Sample Sequencer #2, triggered by software, no IRQs
// 
// SS2 should so the following channels are converted in this order
//
//  0 - X direction of PS2 Joystick
//  1 - Y Direction of PS2 Joystick
//  2 - Volume Potentiometer
//*****************************************************************************
void configure_adc0(void){
	
   // turn on the clock
   SYSCTL->RCGCADC |= SYSCTL_RCGCADC_R0;

   // wait for ADC0 to become ready	
	 while( (SYSCTL->PRADC & SYSCTL_PRADC_R0) == 0) {}
		 
		 
		 
		 
	 
	 ADC0->ACTSS &= ~ADC_ACTSS_ASEN2; // disable Ss2
		 
	 // set the event multiplexer to trigger conversion on a software trigger
	 // for samplke sequencer #2
	 ADC0->EMUX &= ~ADC_EMUX_EM2_ALWAYS;
		 	 
	 ADC0->SSCTL2 = ADC_SSCTL2_END2|ADC_SSCTL2_IE2;
		 
	 
}	
	

//******************************************************************************
// Returns the values for the PS2 joystic and potentiometer
//*****************************************************************************
bool get_adc_values( uint32_t adc_base, uint16_t *ps2_x, uint16_t *ps2_y, uint16_t *pot){

  ADC0_Type  *myADC;

  if( adc_base == 0){
    return false;
  }
   
	
   myADC = (ADC0_Type *)adc_base;
	
	 myADC->SSMUX2 = 0x201; // set channel
	
   
	
	 myADC->ACTSS |= ADC_ACTSS_ASEN2;  // Enable SS2
	 myADC->PSSI =   ADC_PSSI_SS2;     // Start SS2
	
	 while( (myADC->RIS & ADC_RIS_INR2)  == 0){}
		
	 *ps2_x = myADC->SSFIFO2 & 0xFFF;    // Read 12-bit data
	
   
		
	 *ps2_y = myADC->SSFIFO2 & 0xFFF;    // Read 12-bit data

   
	
	 *pot = myADC->SSFIFO2 & 0xFFF;    // Read 12-bit data
   
	 myADC->ISC  = ADC_ISC_IN2;          // Ack the conversion	
  
	 
		
	 return true;
}



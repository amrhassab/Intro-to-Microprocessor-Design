//*****************************************************************************
// main.c
// Author: jkrachey@wisc.edu
//*****************************************************************************
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "TM4C123.h"
#include "gpioPort.h"
#include "adc.h"
#include "timer0.h"
#include "boardUtil.h"


volatile bool Alert_1ms = false;
volatile bool Alert_Timer0A = false;
volatile bool Alert_Timer0B = false;
		
extern void serialDebugInit(void);
char  teamNumber[] = "16";
char person1[] = "Amr Hassaballah";
char person2[] = "Abdullah Akhtar" ;

//*****************************************************************************
//*****************************************************************************
int 
main(void)
{

  // variable declarations
	
	uint16_t x_data, y_data, pot_data, up_button_data;
	uint32_t i, ticks_period, ticks_high, ticks_low, DAC_pin, counter_up_button;
	bool initial, toggle;
	
	toggle = false;
	initial = true;
	counter_up_button = 0; // used to debounce up button

  serialDebugInit();
  
	
  printf("\n\r");
  printf("***************************************\n\r");
  printf("ECE353 Spring 2015  - HW3 \n\r");
  printf("\tTeam %s\n\r", teamNumber);
  printf("\t%s\n\r", person1);
  printf("\t%s\n\r", person2);
  printf("****************************************\n\r");
  
	
  /***** peripheral requirements *****/
	  
  /* a. Digital GPIO PINS */
		
	// configure the UP direction button as digitaol input
  gpio_enable_port(GPIOF_BASE);
	gpio_config_enable_input(GPIOF_BASE, PUSH_BUTTON_UP_PIN);
	gpio_config_digital_enable(GPIOF_BASE, PUSH_BUTTON_UP_PIN);
  gpio_config_enable_pullup(GPIOF_BASE, PUSH_BUTTON_UP_PIN);
	
	// configure DAC5-0 as digital outputs
	gpio_enable_port(GPIOB_BASE);
	gpio_config_enable_output(GPIOB_BASE, DAC_GPIO_0|DAC_GPIO_1|DAC_GPIO_2|DAC_GPIO_3
	|DAC_GPIO_4|DAC_GPIO_5);
	gpio_config_digital_enable(GPIOB_BASE, DAC_GPIO_0|DAC_GPIO_1|DAC_GPIO_2|DAC_GPIO_3
	|DAC_GPIO_4|DAC_GPIO_5);
	
	
	/* b. analog GPIO pins */
		
	// configure pins conected to ps2 stick and pot. to Analog in
  gpio_enable_port(GPIOE_BASE);
	gpio_config_enable_input(GPIOE_BASE, ADC_GPIO_X_PIN | ADC_GPIO_Y_PIN 
	| ADC_GPIO_POT_PIN);
	gpio_config_analog_enable(GPIOE_BASE,ADC_GPIO_X_PIN | ADC_GPIO_Y_PIN 
	| ADC_GPIO_POT_PIN );
	gpio_config_alternate_function(GPIOE_BASE, ADC_GPIO_X_PIN | ADC_GPIO_Y_PIN 
	| ADC_GPIO_POT_PIN);
	
	
	/* c. ADC0 */
	configure_adc0();
	
	
	/* d. Timer0  */
	
	configure_timer0();
	
	
	
	/* e. SysTick */
	
	// configuring systick to generate interrupt every 1ms
	SysTick_Config(50000);
	
	
	/* f. Interrupts */
	
	
  while(1)
  {
		//printf("here\n");
		/* end of part 3-c needs to be done first */
		
		// when sysTick generates an interrupt		
		if( Alert_1ms == true ) {
			// ADC sequence should be initiated
			Alert_1ms = false; // resetting boolean
		
			get_adc_values( ADC0_BASE, &x_data, &y_data, &pot_data);
			
			
			/* d. UP Button */
			up_button_data = GPIOF->DATA; // collecting sample from UP_BUTTON
		
			// count up when up button is pressed to debounce for 16ms
			if ((up_button_data & PUSH_BUTTON_UP_PIN) == 0)
				counter_up_button++;
			else
				counter_up_button = 0;
			
			// up button debounced for 16ms so we can mute the sound
			if (counter_up_button == 16 && toggle == false) {
				GPIOB->DATA = 0;
				stop_timer0A();
				stop_timer0B();
				toggle = true;
				
			// up button is pressed after being muted so replay the sound (in initial if-block)
			} else if (counter_up_button == 16 && toggle == true) {
				initial = true;
				toggle = false;
			}
		}
				
		/****  Functional Description  *****/
	
		/* a. PS2 Joystick */
		
		// determining frequency //
		
		if ( y_data < 0x333){ 
			// y < 20% freq. = 1.0 khz
			ticks_period = 50000;
			
		} else if ( y_data >= 0x333 && y_data < 0x4cc ){
			// 20% <= y < 30%  freq = 1.5 khz
			ticks_period = 33333;		
			
		} else if ( y_data >= 0x4cc && y_data < 0x666 ){
			//  30% <= y < 40%  freq = 2.0 khz
			ticks_period = 25000;
			
		} else if ( y_data >= 0x666 && y_data < 0x7ff ){
			// 40% <= y < 50%  freq = 2.5 khz
			ticks_period = 20000;
			
		} else if ( y_data >= 0x7ff && y_data < 0x999 ){
			// 50% <= y < 60%  freq = 3.0 khz
			ticks_period = 16667;
			
		} else if ( y_data >= 0x999 && y_data < 0xb32 ){
			// 60% <= y < 70%  freq = 3.5 khz
			ticks_period = 14286;
			
		} else if ( y_data >= 0xb32 && y_data < 0xccc ){
			// 70% <= y < 800%  freq = 4.0 khz
			ticks_period = 12500;
			
		} else {
			// y >=  80%  freq = 4.5 khz
			ticks_period = 11111;
		}
		
		// determining duty cycle //
			
		if ( x_data < 0x333){ 
			// x < 20%  duty = 25%
			ticks_high = ticks_period * .25;
		} else if ( x_data >= 0x333 && x_data < 0xccc ){
			// 20% <= x < 80%  duty  = 33%
			ticks_high = ticks_period * .33;		
		} else {
			// x >=  80%  duty = 50%
			ticks_high = ticks_period * .5;	
		}
		
		// ticks that the signal is low for --> for Timer0B
		ticks_low = ticks_period - ticks_high;
	
    
		/* b. Rotary Potentiometer */
    
		// determing volume */
			
		if ( pot_data < 0x266){ 
			// pot. < 15%  DAC_0			
			DAC_pin = DAC_GPIO_0;
				
		} else if ( pot_data >= 0x266 && pot_data < 0x4cc ){
			// 15% <= pot. < 30% DAC_1 	
			DAC_pin = DAC_GPIO_1;			
		
		} else if ( pot_data >= 0x4cc && pot_data < 0x732 ){
			// 30% <= pot. < 45% DAC_2
			DAC_pin = DAC_GPIO_2;
		
		} else if ( pot_data >= 0x732 && pot_data < 0x999 ){
			// 45% <= pot. < 60% DAC_3 
			DAC_pin = DAC_GPIO_3;	
		
		} else if ( pot_data >= 0x999 && pot_data < 0xbff ){
			// 60% <= pot. < 75% DAC_4 
			DAC_pin = DAC_GPIO_4;
		
		} else {
			// pot. >= 75% DAC_5
			DAC_pin = DAC_GPIO_5;				
		}
   
	
		/* c. timers */
	
		// initiates the the timer cycle for the first time and every time
		// the sound is toggled back on.
		if (initial == true) {
			// enable A once
			initial = false;
			//printf(" intitial and up button loop, ticks_high: %d ", ticks_high);
			start_timer0A(ticks_high); 	
			GPIOB->DATA = DAC_pin;
		}
	
		// when timer A generates an interrupt.
		if ( Alert_Timer0A == true ) {
		// disable A enable B
			Alert_Timer0A = false; // resetting boolean
			start_timer0B(ticks_low);
			//printf(" timer A interrupt loop ");
			GPIOB->DATA = 0;
		}
		
		// when timer B generates an interupt
		if (Alert_Timer0B == true) {
		// disable B enable A
			Alert_Timer0B = false; // resetting boolean
			start_timer0A(ticks_high);
			//printf(" timer b interrupt loop ");
			GPIOB->DATA = DAC_pin;
		}
	}	
}


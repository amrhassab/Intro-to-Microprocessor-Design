//*****************************************************************************
// main.c
// Author: jkrachey@wisc.edu
//*****************************************************************************
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "TM4C123.h"
#include "gpioPort.h"
#include "adc.h"

extern void serialDebugInit(void);

// ADD CODE
// Define the base addresses for the GPIO port and
// the ADC attached to the PS2 joystick.
#define   PS2_GPIO_BASE    GPIOE_BASE
#define   PS2_ADC_BASE     ADC0_BASE

// ADD CODE
// Define the Bitmask for each pin below
#define   PS2_X_DIR_PIN      (1 << 2)
#define   PS2_Y_DIR_PIN      (1 << 3)

// ADD CODE
// Set the analog channel for each direction
#define   PS2_X_ADC_CHANNEL  1
#define   PS2_Y_ADC_CHANNEL  0

//*****************************************************************************
//*****************************************************************************
void print_ps2(void)
{
  uint32_t x_data, y_data;
  uint32_t i;
  while(1)
  {

    x_data = getADCValue(PS2_ADC_BASE,PS2_X_ADC_CHANNEL);
    y_data = getADCValue(PS2_ADC_BASE,PS2_Y_ADC_CHANNEL);
    printf("X Dir value : 0x%03x        Y Dir value : 0x%03x\r",x_data, y_data);
    for(i=0;i<1000000; i++){}
    
  }
}


//*****************************************************************************
//*****************************************************************************
int 
main(void)
{
  serialDebugInit();

  printf("\n\r***************************************\n\r");
  printf("ECE353 - Analog Input In Class Exercise\n\r");
  printf("****************************************\n\r");
  
  // ADD CODE
  // Configure the 2 pins connected to the X and Y direction on the PS2 controller to
  // be analog inputs
  //   i. Enable the gpio port used for the PS2
  //  ii. Set the PS2 pins as inputs
  // iii. Configure the 2 pins as analog pins
  // iv.  Configure the 2 pins as their alternate function
	gpio_enable_port(PS2_GPIO_BASE);
	
	gpio_config_enable_input(PS2_GPIO_BASE, PS2_X_DIR_PIN | PS2_Y_DIR_PIN);
	
	gpio_config_analog_enable(PS2_GPIO_BASE, PS2_X_DIR_PIN | PS2_Y_DIR_PIN);
	
	gpioc_config_alternate_function(PS2_GPIO_BASE, PS2_X_DIR_PIN | PS2_Y_DIR_PIN);
	

  // ADD code
  // Initialize the ADC used by the PS2 controller
	initializeADC(ADC0_BASE);
	
  // Get User Input
  print_ps2();
  
  // Reach infinite loop
  while(1){};
}

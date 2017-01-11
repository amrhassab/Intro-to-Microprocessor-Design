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
#include "uart.h"

#define PA0 (1<<0)
#define PA1 (1<<1)
//*****************************************************************************
// Configure PA0 and PA1 to be UART pins
//*****************************************************************************
void uart0_config_gpio(void)
{
  
	gpio_enable_port(GPIOA_BASE);
	gpio_config_digital_enable(GPIOA_BASE, PA0|PA1 );
	gpio_config_alternate_function(GPIOA_BASE, PA0|PA1); // says we want alternate func
	gpio_config_port_control(GPIOA_BASE, GPIO_PCTL_PA0_U0RX|GPIO_PCTL_PA1_U0TX);// says WHICH alternate func we want

}



//*****************************************************************************
//*****************************************************************************
int 
main(void)
{
  char greeting[] = "\n\r\n\rEnter an 4-digit number: ";
  char response[] = "\n\rYou entered:";
  char exit_msg[] = "\n\r\n\rGoodbye.";
  char rx_char;
  char rx_string[5] = {0,0,0,0,0};
  uint8_t rx_count = 0;  
  
  // Configure the GPIO pins
	uart0_config_gpio();
  
  // Configure the UART
  uart_init_115K(UART0_BASE);
  
	// Print greeting string above
	
  uartTxPoll(UART0_BASE, greeting);

  // Get User Input
	for (rx_count=0; rx_count<5; rx_count++){
	  rx_string[rx_count] = uartRxPoll(UART0_BASE, true);
		// transmit character back to user as soon as it is recieved
		uartTxPollChar(UART0_BASE, rx_string[rx_count]);
	}

  // Print the response string
	uartTxPoll(UART0_BASE, response);
  // Print rx_string
	uartTxPoll(UART0_BASE, rx_string);
  
  // Print exit_msg
  uartTxPoll(UART0_BASE, exit_msg);
  
  while(1)
  {
     // Infinite Loop
  }
}

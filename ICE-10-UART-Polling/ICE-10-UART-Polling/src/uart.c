#include "uart.h"

/****************************************************************************
 * Verify that the uart base address is valid
 ****************************************************************************/
bool verifyUartBase(uint32_t base)
{
   switch(base)
   {
     case UART0_BASE:
     case UART1_BASE:
     case UART2_BASE:
     case UART3_BASE:
     case UART4_BASE:
     case UART5_BASE:
     case UART6_BASE:
     case UART7_BASE:
     {
       return true;
     }
     default:
     {
       return false;
     }
   }
}

/****************************************************************************
 * This routine transmits a single character out the UART / COM port.
 * Only the lower 8 bits of the 'data' variable are transmitted.
 ****************************************************************************/
void uartTxPollChar(uint32_t base, char data)
{
  UART0_Type *myUart =((UART0_Type *) base);

  if( verifyUartBase(base) == false)
  {
    return;
  }

  if ( data != 0)
  {
    while( ((myUart->FR)&(UART_FR_TXFF)) != 0 );
    myUart->DR = data;
  }
  return;
}

/****************************************************************************
 * This routine transmits a character string out the UART / COM port.
 * Only the lower 8 bits of the 'data' variable are transmitted.
 ****************************************************************************/
void uartTxPoll(uint32_t base, char *data)
{
  UART0_Type *myUart =((UART0_Type *) base);

  if( verifyUartBase(base) == false)
  {
    return;
  }

  if ( data != 0)
  {
    while(*data != '\0')
    {
      while( ((myUart->FR)&(UART_FR_TXFF)) != 0 );
      myUart->DR = *data;
      data++;
    }
  }
  return;
}

/****************************************************************************
 * This routine returns a character received from the UART/COM port.
 * If blocking is enabled, this routine should not return until data
 * is available. If blocking is disabled and no data is available,
 * this function should return 0.
 ****************************************************************************/
char uartRxPoll(uint32_t base, bool block)
{
  UART0_Type *myUart =((UART0_Type *) base);

  if( verifyUartBase(base) == false)
  {
    return 0;
  }

  if( (block == false) && !(myUart->FR & UART_FR_RXFE))
  {
       return myUart->DR;
  }
  else if((block == false) && (myUart->FR & UART_FR_RXFE))
  {
    return 0;
  }

  while(myUart->FR & UART_FR_RXFE && block)
  {
    // Wait
  }

   return myUart->DR;
}

//************************************************************************
// Configure UART0 to be 115200, 8N1.  Data will be sent/recieved using
// polling (Do Not enable interrupts)
//************************************************************************


bool uart_init_115K(uint32_t base_addr)
{
    UART0_Type *myUart;
	  uint32_t rcgc_mask = 0;
    uint32_t pr_mask = 0;
	  
  
    if( verifyUartBase(base_addr) == false)
    {
      return false;
    }

		
		
		 switch( base_addr )
   {
     case UART0_BASE:
     {
       // ADD CODE
      
			 rcgc_mask = SYSCTL_RCGCUART_R0;
       pr_mask = SYSCTL_PRUART_R0;
       break;
     }
     case UART1_BASE:
     {
       // ADD CODE
       
			 rcgc_mask = SYSCTL_RCGCUART_R1;
       pr_mask = SYSCTL_PRUART_R1;
       break;
     }
     case UART2_BASE:
     {
       // ADD CODE
      
			 rcgc_mask = SYSCTL_RCGCUART_R2;
       pr_mask = SYSCTL_PRUART_R2;
       break;
     }
     case UART3_BASE:
     {
       // ADD CODE
       
			 rcgc_mask = SYSCTL_RCGCUART_R3;
       pr_mask = SYSCTL_PRUART_R3;
       break;
     }
     case UART4_BASE:
     {
       // ADD CODE
       
       rcgc_mask = SYSCTL_RCGCUART_R4;
       pr_mask = SYSCTL_PRUART_R4;
       break;
     }
     case UART5_BASE:
     {
       // ADD CODE
       
			 rcgc_mask = SYSCTL_RCGCUART_R5;
       pr_mask = SYSCTL_PRUART_R5;
       break;
     }
		 case UART6_BASE:
		 {
       rcgc_mask = SYSCTL_RCGCUART_R6;
       pr_mask = SYSCTL_PRUART_R6;
     }

     case UART7_BASE:
		 {
      rcgc_mask = SYSCTL_RCGCUART_R7;
      pr_mask = SYSCTL_PRUART_R7;
     }			 
     default:
     {
       return false;
     }
   }
		
		
    myUart = (UART0_Type*) base_addr;
		
		//enable clock
		SYSCTL->RCGCUART |= rcgc_mask;
		
		// wait for uart peripheral to be ready.
		while ((SYSCTL->PRUART & pr_mask) == 0) {};
			
		
		
    // disable Uart
		myUart->CTL &= ~UART_CTL_UARTEN;
		myUart->IBRD = 27;
		myUart->FBRD = 8;
		
		myUart->LCRH = UART_LCRH_WLEN_8;
		myUart->CTL |= UART_CTL_UARTEN|UART_CTL_RXE|UART_CTL_TXE;
		
		
			
			
    return true;

}

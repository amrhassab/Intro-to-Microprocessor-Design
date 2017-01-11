#include "interrupts.h"

extern PC_Buffer UART0_Rx_Buffer;
extern PC_Buffer UART0_Tx_Buffer;

extern void UART0_Tx_Flow(PC_Buffer *tx_buffer);

//*****************************************************************************
// Rx Portion of the UART ISR Handler
//*****************************************************************************
__INLINE static void UART0_Rx_Flow(PC_Buffer *rx_buffer)
{
	char data;
  // Remove entries from the RX FIFO until the HW FIFO is empty.
  // Data should be placed in the rx_buffer.  
  while ( (UART0->FR & UART_FR_RXFE) == 0 )
	{
		data = UART0->DR;
		pc_buffer_add(rx_buffer, data);
	}
	
	
	
  // Clear the RX interrupts so it can trigger again when the hardware 
  // FIFO becomes full
	
	 UART0->ICR |= UART_ICR_RXIC|UART_ICR_RTIC;

}

//*****************************************************************************
// UART0 Interrupt Service handler
//*****************************************************************************
void UART0_Handler(void)
{
    uint32_t  status;


    status = UART0->MIS;


    // execute  UART0_Rx_Flow if a Rx or Rx Timeout IRQ is active
    if (status & UART_MIS_RXMIS || status & UART_MIS_RTMIS)
		{
			UART0_Rx_Flow(&UART0_Rx_Buffer);
		}
    // Check the TX interrupts
    if ( status & UART_MIS_TXMIS )
    {
      UART0_Tx_Flow(&UART0_Tx_Buffer);
    }
    return;
}

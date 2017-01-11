#include "interrupts.h"
#include "../include/gptimer.h"
 
extern PC_Buffer UART0_Rx_Buffer;
extern PC_Buffer UART0_Tx_Buffer;
extern volatile bool  AlertTx;
extern volatile bool  AlertTimerStart;
extern volatile bool  AlertTimerStop;
extern volatile bool AlertOneSec;
extern volatile bool AlertButtons;
extern volatile uint32_t Miliseconds;


//*****************************************************************************
// Rx Portion of the UART ISR Handler
//*****************************************************************************
__INLINE static void UART0_Rx_Flow(PC_Buffer *rx_buffer)
{
  // Remove entries from the RX FIFO until they are all removed
  while( !(UART0->FR & UART_FR_RXFE ))
  {
    if( ! pc_buffer_full(rx_buffer))
    {
      // Add the character to the circular buffer
      pc_buffer_add(rx_buffer,UART0->DR);
    }
  }

  // Clear the RX interrupts so it can trigger again when the hardware 
  // FIFO becomes full
  UART0->ICR |= (UART_ICR_RXIC | UART_ICR_RTIC);
}

//*****************************************************************************
// Tx Portion of the UART ISR Handler
//*****************************************************************************
__INLINE static void UART0_Tx_Flow(PC_Buffer *tx_buffer)
{
      char c;
  
        // Check to see if we have any data in the circular queue
        if( ! pc_buffer_empty(tx_buffer))
        {
            // Move data from the circular queue to the hardware FIFO
            // until the hardware FIFO is full or the circular buffer
            // is empty.
            while( (! pc_buffer_empty(tx_buffer)) && !(UART0->FR & UART_FR_TXFF ) )
            {
              pc_buffer_remove(tx_buffer, &c);  
              UART0->DR = c;
            }
        }
        else
        {
            // Any data in the hardware FIFO will continue to be transmitted
            // but the TX empty interrupt will not be enabled since there
            // is no data in the circular buffer.

            // Disable the TX interrupts.
            UART0->IM &= ~UART_IM_TXIM;
        }
        
        // Clear the TX interrupt so it can trigger again when the hardware
        // FIFO is empty
        UART0->ICR |= UART_ICR_TXIC;
}

  
//*****************************************************************************
// UART0 Interrupt Service handler
//*****************************************************************************
void UART0_Handler(void)
{
    uint32_t  status;

    // Check to see if RXMIS or RTMIS is active
    status = UART0->MIS;

    if ( status & (UART_MIS_RXMIS | UART_MIS_RTMIS ) )
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


 /****************************************************************************
 * The SysTick Handler 
 *
 * Register Information on the SysTick timer can be found on pages 129-132 
 * of the MCU data sheet.
 *
 * Register Information on the Watchdog timer can be found on pages 749-754.
 *
 ****************************************************************************/
//void SysTick_Handler(void)
//{
//  static int count = 0;
//  
//  // Clear the SysTick Counter 
//  uint32_t val = SysTick->VAL;// Clears the SysTick Interrupt
//  
//  if(count == 5)
//  {
//    AlertTx = true;
//    count = 0;
//  }
//  else
//  {
//    count++;
//  }
//  
//}

//*****************************************************************************
// Timer0A Interrupt Handler (16 Bit Timer)
// Used to Debounce Push Buttons
//*****************************************************************************
void TIMER0A_Handler(void)
{
  AlertButtons = true;
  TIMER0->ICR |= TIMER_ICR_TATOCINT;
}

//*****************************************************************************
// Timer0B Interrupt Handler (16 Bit Timer)
// Used to count miliseconds.  The user must re-enable the timer each timer
// they want to wait.
//*****************************************************************************
void TIMER0B_Handler(void)
{
  
  Miliseconds++;
  // Clear the interrupt
  TIMER0->ICR |= TIMER_ICR_TBTOCINT;
}


//*****************************************************************************
// Timer0B Interrupt Handler
// Used to Sample ADC
//*****************************************************************************
void TIMER1A_Handler(void)
{
  AlertOneSec= true;
  TIMER1->ICR |= TIMER_ICR_TATOCINT;
}

//*****************************************************************************
// GPIO PortE Interrupt Handler
//*****************************************************************************
void GPIOE_Handler(void)
{
}

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "TM4C123.h"

extern volatile uint8_t Seconds;
extern volatile uint8_t Active_Column;
extern volatile bool Alert_Update_Column;

void SysTick_Handler(void)
{
  static uint32_t tick_count = 0;
  
  // Clear the interrupts
  uint32_t val = SysTick->VAL;
  
  // Indicate to main application to update the active column
  Alert_Update_Column = true;
  
  // Increment to the next active column.  There are only 5 columns
  // on the Matrix LED, so wrap around to 0 after we reach 4.
  Active_Column = (Active_Column + 1) % 5;
  
  // Calculate when 1 second has passed and increment the second count
  // We will count from 0-9
  tick_count = (tick_count + 1) % 1000;
  
  if ( tick_count == 0)
  {
     Seconds = (Seconds + 1) % 10;
  }
  
}

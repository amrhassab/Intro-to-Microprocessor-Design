// Copyright (c) 2014, Joe Krachey
// All rights reserved.
//
// Redistribution and use in binary form, with or without modification, 
// are permitted provided that the following conditions are met:
//
// 1. Redistributions in binary form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimer in 
//    the documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

//*****************************************************************************
// main.c
// Author: jkrachey@wisc.edu
//*****************************************************************************
#include <stdio.h>
#include <stdint.h>
#include <string.h>


#include "TM4C123.h"
#include "boardUtil.h"
#include "io_expander.h"


//*****************************************************************************
// Global Variables
//*****************************************************************************
extern const uint8_t LedNumbers[16][5];
volatile uint8_t Seconds = 0;
volatile uint8_t Active_Column = 0;
volatile bool Alert_Update_Column = false;
  
//*****************************************************************************
//*****************************************************************************
void initializeBoard(void)
{
  DisableInterrupts();
  serialDebugInit();
  i2cInit();
  ioExpanderInit(IO_EXPANDER_I2C_BASE);
  SysTick_Config(50000);
  EnableInterrupts();
}



//*****************************************************************************
//*****************************************************************************
int 
main(void)
{

  
  initializeBoard();

  printf("\n\r**************************************\n\r");
  printf("* In Class - I2C\n\r");
  printf("**************************************\n\r");

  // Infinite Loop
  while(1)
  {
    if(Alert_Update_Column)
    {
       Alert_Update_Column = false;
       ledMatrixWriteData( IO_EXPANDER_I2C_BASE, Active_Column, LedNumbers[Seconds][Active_Column]);
    }
  }
}

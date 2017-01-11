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
#include "eeprom.h"


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
  EnableInterrupts();
}

#define EEPROM_BYTES  20
//*****************************************************************************
// Test the EEPROM
//*****************************************************************************
void test_eeprom(void)
{
  
  uint8_t write_data[EEPROM_BYTES];
  uint8_t read_data[EEPROM_BYTES];
  bool passed = true;
  int i;
  
  // Write data to the EEPROM
  for(i = 0; i < EEPROM_BYTES; i++)
  {
    write_data[i] = rand();
    eeprom_byte_write(EEPROM_I2C_BASE,i,write_data[i]);
  }

  // Read data back from the EEPROM
  for(i = 0; i < EEPROM_BYTES; i++)
  {
    eeprom_byte_read(EEPROM_I2C_BASE,i,&(read_data[i]));
  }
  
  // Verify that the bytes written match the bytes read
  for(i = 0; i < EEPROM_BYTES; i++)
  {
    if( write_data[i] != read_data[i])
    {
      printf("ERROR at address 0x%04x.  write: 0x%02x read: 0x%02x\n\r", i, write_data[i], read_data[i]);
      passed = false;
    }
  }
  
  // Print if the test passed or failed.
  if ( passed == true)
  {
      printf(" ==== EEPROM Test Passed ===\n\n\r");
  }
  else
  {
      printf(" ==== EEPROM Test Failed ===\n\n\r");
  }
  
}


//*****************************************************************************
//*****************************************************************************
int 
main(void)
{

  
  initializeBoard();

  printf("\n\r");
  printf("**************************************\n\r");
  printf("* In Class - I2C\n\r");
  printf("**************************************\n\r");
  
    test_eeprom();
  
  while(1){};

}

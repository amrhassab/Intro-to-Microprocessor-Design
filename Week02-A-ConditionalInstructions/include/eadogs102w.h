#ifndef __EADOGS102W_H__
#define __EADOGS102W_H__

#include <stdint.h>
#include "spi.h"

#define NUM_PAGES   8
#define NUM_COLS    102

//*****************************************************************************
//*****************************************************************************
bool lcdInitialize( 
  uint32_t  spiBase, 
  void      *resetPinBase, 
  uint32_t  resetPinNum,
  void      *cmdPinBase,
  uint32_t  cmdPinNum
);

  //*****************************************************************************
//*****************************************************************************
  bool lcdSetPage( 
  uint32_t  spiBase, 
  void      *cmdPinBase,
  uint32_t  cmdPinNum,
  uint8_t   page
);
  
//*****************************************************************************
//*****************************************************************************
bool lcdSetColumn( 
  uint32_t  spiBase, 
  void      *cmdPinBase,
  uint32_t  cmdPinNum,
  uint8_t   column
);
  

//*****************************************************************************
//*****************************************************************************
  bool lcdWriteData( 
  uint32_t  spiBase, 
  void      *cmdPinBase,
  uint32_t  cmdPinNum,
  uint8_t   data
);
  
#endif

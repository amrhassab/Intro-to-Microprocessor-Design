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
#include "lcd.h"


bool validate_spi_gpio(void);
bool validate_cd_gpio(void);
bool validate_rst_n_gpio(void);
bool validate_spi_setup(void);

/******************************************************************************
 * Global Variables
 *****************************************************************************/

  


//*****************************************************************************
// Fill out the #defines below to configure which pins are connected to
// the LCD Screen
// 
// ADD CODE
//*****************************************************************************
#define   LCD_GPIO_BASE       GPIOA_BASE
#define   LCD_SPI_BASE        SSI0_BASE
#define   LCD_CLK_PIN         1 << 2
#define   LCD_CS_PIN          1 << 3
#define   LCD_MOSI_PIN        1 << 5

#define   LCD_CLK_PIN_PCTL    GPIO_PCTL_PA2_SSI0CLK
#define   LCD_CS_PIN_PCTL     GPIO_PCTL_PA3_SSI0FSS
#define   LCD_MOSI_PIN_PCTL   GPIO_PCTL_PA5_SSI0TX


#define   GPIO_LCD_CD_BASE    GPIOA_BASE
#define   LCD_CD_PIN          1 << 4

#define   GPIO_LCD_RST_N_BASE GPIOC_BASE
#define   LCD_RST_N_PIN       1 << 7

//*****************************************************************************
// Initialize the LCD peripheral
//*****************************************************************************
void lcd_init(void)
{
  
  // Configure SPI CLK
  gpio_enable_port(LCD_GPIO_BASE);
  gpio_config_digital_enable(LCD_GPIO_BASE, LCD_CLK_PIN);
  gpio_config_alternate_function(LCD_GPIO_BASE, LCD_CLK_PIN);
  gpio_config_port_control(LCD_GPIO_BASE, LCD_CLK_PIN_PCTL);
    
  // Configure SPI CS
  gpio_config_digital_enable(LCD_GPIO_BASE, LCD_CS_PIN);
  gpio_config_alternate_function(LCD_GPIO_BASE, LCD_CS_PIN);
  gpio_config_port_control(LCD_GPIO_BASE, LCD_CS_PIN_PCTL);

  // Configure SPI MOSI
  gpio_config_digital_enable(LCD_GPIO_BASE, LCD_MOSI_PIN);
  gpio_config_alternate_function(LCD_GPIO_BASE, LCD_MOSI_PIN);
  gpio_config_port_control(LCD_GPIO_BASE, LCD_MOSI_PIN_PCTL);
  
  // Configure CD
  gpio_enable_port(GPIO_LCD_CD_BASE);
  gpio_config_digital_enable(GPIO_LCD_CD_BASE,LCD_CD_PIN);
  gpio_config_enable_output(GPIO_LCD_CD_BASE,LCD_CD_PIN);
  
  // Configure RST_N
  gpio_enable_port(GPIO_LCD_RST_N_BASE);
  gpio_config_digital_enable(GPIO_LCD_RST_N_BASE, LCD_RST_N_PIN);
  gpio_config_enable_output(GPIO_LCD_RST_N_BASE, LCD_RST_N_PIN);
 
  // Configure the SPI interface for Mode 3, 25MHz.
  // Make sure to adjust the registers used to determine the frequency of 
  // the SPI clock.
  initialize_spi( LCD_SPI_BASE, 3);
  
}

//*****************************************************************************
// PROVIDED CODE
//*****************************************************************************  

//*****************************************************************************
// Function that prints out an image.  The image is 56 pixels by 56 pixels.
// You can try to center the image if you like, but its not necessary.
//*****************************************************************************
void test_lcd(void)
{
  int i,j;
  
  dogs102_init();

  dogs102_clear();
  
  for(i = 0; i < 8; i++)
  {
    
     dogs102_set_page(i);
    for(j=0; j<101; j++)
    {
      dogs102_set_column(j);
      dogs102_write_data(image[i*101 + j]);
    }
  }
}
//*****************************************************************************
//*****************************************************************************

void initializeBoard(void)
{
  DisableInterrupts();
  serialDebugInit();
  lcd_init();
  EnableInterrupts();
}

//*****************************************************************************
// Examines GPIO and SPI configuration
//*****************************************************************************
bool validate_hardware(void)
{
  bool spi_gpio = true;
  bool cd_gpio = true;
  bool rst_n_gpio = true;
  bool spi = true;
  
  spi_gpio = validate_spi_gpio();
  cd_gpio = validate_cd_gpio();
  rst_n_gpio = validate_rst_n_gpio();
  spi = validate_spi_setup();
  
  if( spi_gpio && cd_gpio && rst_n_gpio && spi)
  {
    return true;
  }
  else
  {
    return false;
  }
  
}

//*****************************************************************************
//*****************************************************************************
int 
main(void)
{
	
	uint8_t line;
	char c;
	uint8_t c_index;
	char string[10] = "abcdefegHI";
  initializeBoard();
	
  printf("\n\r");
  printf("**************************************\n\r");
  printf("* ECE353 - ICE: LCD\n\r");
  printf("**************************************\n\r");
  printf("\n\r");

  if( validate_hardware() )
 {
    printf("LCD SPI interface configured correctly\n\r");
    test_lcd();
  }
  else
  {
     printf("LCD SPI interface configured INCORRECTLY\n\r");
  }
  
  // Infinite Loop
	
   //dogs102_init();
   //dogs102_clear();	 
	 
	 //dogs102_write_string( string, 0);
	 
  while(1)
  {

  }
}

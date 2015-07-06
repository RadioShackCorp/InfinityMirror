/******************** (C) COPYRIGHT 2015 RadioShack ********************
 * File Name          : LEDStrip_Segments.ino
 * Author             : RadioShack
 * Version            : V1.0
 * Date               : 06/07/2015
 * Description        : Main program body
 ********************************************************************************
 * THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
 * AS A RESULT, RS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
 * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
 * CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
 * INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *******************************************************************************/

//#include <avr/pgmspace.h>

// ******** DEBUG ==== should auto config to adapt different mother board *********
//#define DATA_1 (PORTF |=  0X01)    // DATA 1    // for ATMEGA
//#define DATA_0 (PORTF &=  0XFE)    // DATA 0    // for ATMEGA
//#define STRIP_PINOUT DDRF=0xFF  // for ATMEGA
#define DATA_1 (PORTC |=  0X01)    // DATA 1    // for UNO
#define DATA_0 (PORTC &=  0XFE)    // DATA 0    // for UNO
#define STRIP_PINOUT (DDRC=0xFF)    // for UNO

 


// ***********************************************************************************************************
// *
// *                            Power Up Init.
// *
// *
// ***********************************************************************************************************
void setup() {                

  STRIP_PINOUT;        // set output pin - DEBUG: should auto detect which mother board for use

  reset_strip();
  //noInterrupts();

}



// ***********************************************************************************************************
// *
// *                            Main Loop 
// *
// *
// ***********************************************************************************************************
void loop() {

     noInterrupts();
    
    // Each line below controls one 3-LED segment of the 10-segment strip. If you trim the strip, you may use fewer lines.
    
      send_strip(0x0000ff);  // The six values represent RGB values: (0x [2-digit GREEN hexadecimal values][2-digit BLUE hexadecimal values][2-digit RED hexadecimal values])
      send_strip(0x00ff00);
      send_strip(0xff0000);  
      send_strip(0x0000ff);
      send_strip(0xff0000);  // Lower or raise RGB values to mix colors. 0x00ffff = Blue + Red = Purple
      send_strip(0x00ff00);
      send_strip(0x0000ff);
      send_strip(0x00ff00);
      send_strip(0xff0000);
      send_strip(0x0000ff);
     interrupts();

    delay(1000);
   }



/*******************************************************************************
 * Function Name  : send_strip
 * Description    : Transmit 24 pulse to LED strip
 *                  
 * Input          : 24-bit data for the strip
 *                  
 * Output         : None
 * Return         : None
 *******************************************************************************/
void send_strip(uint32_t data)
{
  int i;
  unsigned long j=0x800000;
  
 
  for (i=0;i<24;i++)
  {
    if (data & j)
    {
      DATA_1;
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");    
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      DATA_0;
    }
    else
    {
      DATA_1;
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");    
      DATA_0;
    }

    j>>=1;
  }


  
}

/*******************************************************************************
 * Function Name  : reset_strip
 * Description    : Send reset pulse to reset all color of the strip
 *                  
 * Input          : None
 *                  
 * Output         : None
 * Return         : None
 *******************************************************************************/
void	reset_strip()
{
  DATA_0;
  delayMicroseconds(20);
}

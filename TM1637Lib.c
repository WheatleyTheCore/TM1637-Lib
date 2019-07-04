

/* Include Prototypes for your library, if applicable */
/* #include "mylibrary.h" */

/*-----------------------------------------------------------------------*

	Place your 'C' library code here.
	I don't know what I'm doing please send help  
	
	im commenting literally every line of this
	because I'm confused by literally all of it 
	
	THIS IS A PORT OF 
	https://github.com/WheatleyTheCore/Processo-Expert-Nunchuk-Lib/blob/master/NunchukLib.c
	
	
 *-----------------------------------------------------------------------*/

#include "Cpu.h" //allows us access to cpu functions
#include "DIO.h"
#include "CLK.h"
#include "TM1637_lib.h"


#define TM1637_I2C_COMM1    0x40  //I think this is like the first register 
#define TM1637_I2C_COMM2    0xC0  //register 2?
#define TM1637_I2C_COMM3    0x80  //register 3 probably

/*-------------------------------------------------------------------------*
 * 
 *   So, 7 segment displays work by lighting up leds so it looks like a thing
 *   I think each bit controls one of those leds
 *   0 being off
 *   1 being on
 * 
 *-------------------------------------------------------------------------*/

uint8_t m_brightness;
uint8_t digit;

const uint8_t digitToSegment[] = {  
 // XGFEDCBA
  0b00111111,    // 0
  0b00000110,    // 1
  0b01011011,    // 2
  0b01001111,    // 3
  0b01100110,    // 4
  0b01101101,    // 5
  0b01111101,    // 6
  0b00000111,    // 7
  0b01111111,    // 8
  0b01101111,    // 9
  0b01110111,    // A
  0b01111100,    // b
  0b00111001,    // C
  0b01011110,    // d
  0b01111001,    // E
  0b01110001     // F
  };

static const uint8_t minusSegments = 0b01000000; //maybe makes a -?

void setBrightness(uint8_t brightness, int on) {
	if (!on)
		on = 1;
	m_brightness = (brightness & 0x7) | (on? 0x08 : 0x00); //this one sets the brightness of the screen(beneficial for power saving)
}

void setSegments(const uint8_t segments[], uint8_t length, uint8_t pos) {
	int k;
	
	start();
	(void)writeByte(TM1637_I2C_COMM1);
	stop();

	// Write COMM2 + first digit address
	start();
	(void)writeByte(TM1637_I2C_COMM2 + (pos & 0x03));

	// Write the data bytes
	for (k = 0; k < length; k++)
		writeByte(segments[k]);

	  	stop();

	// Write COMM3 + brightness
	start();
	(void)writeByte(TM1637_I2C_COMM3 + (m_brightness & 0x0f));
	stop();
}

void clear() {
	uint8_t Cdata[4] = {0x00, 0x00, 0x00, 0x00};//set all the bits to off
    setSegments(Cdata, 4, 0);  //send that data
}

void showNumberDec(int num, int leading_zero, uint8_t length, uint8_t pos) {
	showNumberDecEx(num, 0, leading_zero, length, pos);
}

void showNumberDecEx(int num, uint8_t dots, int leading_zero, uint8_t length, uint8_t pos) {
	showNumberBaseEx((uint8_t)(num < 0? -10 : 10), num < 0? -num : num, dots, leading_zero, length, pos);
}

void showNumberHexEx(uint16_t num, uint8_t dots, int leading_zero, uint8_t length, uint8_t pos) {
	showNumberBaseEx(16, num, dots, leading_zero, length, pos);
}

void showNumberBaseEx(int8_t base, uint16_t num, uint8_t dots, int leading_zero, uint8_t length, uint8_t pos) {
	int16_t i;
	negative = 0;
	if (base < 0) {
		base = -base;
		negative = 1;
	}


	if (num == 0 && !leading_zero) {
		// Singular case - take care separately
		for(i = 0; i < (length-1); i++) 
			digits[i] = 0;
			digits[length-1] = encodeDigit(0);
		}
		else {
		//uint8_t i = length-1;
		//if (negative) {
		//	// Negative number, show the minus sign
		//    digits[i] = minusSegments;
		//	i--;
		//}
		
		for(i = length-1; i >= 0; --i)
		{
			digit = (uint8_t)(num % base);
		
			if (digit == 0 && num == 0 && leading_zero == 0) {
				// Leading zero is blank
				digits[i] = 0;
			} else {
				digits[i] = encodeDigit(digit);
			}
			if (digit == 0 && num == 0 && negative) {
				digits[i] = minusSegments;
				negative = 0;
			}
		
			num /= base;
		}
		
		if(dots != 0)
		{
			showDots(dots, digits);
		}
	}
	setSegments(digits, length, pos);
}

void bitDelay()	{
}

void start() {
  DIO_SetDir(1);
  bitDelay();
}

void stop() {
	DIO_SetDir(1);
	bitDelay();
	CLK_SetDir(0);
	bitDelay();
	DIO_SetDir(0);
	bitDelay();
}

int writeByte(uint8_t b){
  uint8_t data;
  int16_t i;
  uint8_t ack;
  data = b;
  

  // 8 Data Bits
  for(i = 0; i < 8; i++) {
    // CLK low
	CLK_SetDir(1);
    bitDelay();

	// Set data bit
    if (data & 0x01)
      DIO_SetDir(0);
    else
    	DIO_SetDir(1);

    bitDelay();

	// CLK high
    CLK_SetDir(0);
    bitDelay();
    data = data >> 1;
  }
  // Wait for acknowledge
   // CLK to zero
   CLK_SetDir(1);
   DIO_SetDir(0);
   bitDelay();

   // CLK to high
   CLK_SetDir(0);
   bitDelay();
   ack = DIO_GetVal();
   if (ack == 0)
	   DIO_SetDir(1);


   bitDelay();
   CLK_SetDir(1);
   bitDelay();

   return ack;
 }

void showDots(uint8_t dots, uint8_t* digits){
	int16_t i;
    for(i = 0; i < 4; ++i)
    {
        digits[i] |= (dots & 0x80);
        dots <<= 1;
    }
}

uint8_t encodeDigit(uint8_t digit)
{
	return digitToSegment[digit & 0x0f];
}

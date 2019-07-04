/*
 * 7seg4dig.h
 *
 *  Created on: Jun 29, 2019
 *      Author: Alex
 */

#ifndef TM1637_lib_H_
#define TM1637_lib_H_

#define SEG_A   0b00000001
#define SEG_B   0b00000010
#define SEG_C   0b00000100
#define SEG_D   0b00001000
#define SEG_E   0b00010000
#define SEG_F   0b00100000
#define SEG_G   0b01000000
#define SEG_DP  0b10000000

void setBrightness(uint8_t brightness, int on);

void setSegments(const uint8_t segments[], uint8_t length, uint8_t pos);

void clear(void);

void showNumberDec(int num, int leading_zero, uint8_t length, uint8_t pos);

void showNumberDecEx(int num, uint8_t dots, int leading_zero, uint8_t length, uint8_t pos);

void showNumberHexEx(uint16_t num, uint8_t dots, int leading_zero, uint8_t length, uint8_t pos);

uint8_t encodeDigit(uint8_t digit);

void bitDelay(void);

void start(void);

void stop(void);

int writeByte(uint8_t b);

void showDots(uint8_t dots, uint8_t* digits);
   
void showNumberBaseEx(int8_t base, uint16_t num, uint8_t dots , int leading_zero, uint8_t length, uint8_t pos);

extern int negative;

extern uint8_t digits[4];

extern const uint8_t digitToSegment[16];

#endif /* 7SEG4DIG_H_ */

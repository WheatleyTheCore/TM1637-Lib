# TM1637-Lib
This is a library for TM1637 based 7 segment displays. It was designed for and tested using the grove 4 digit display.

This library was designed as a port of https://github.com/avishorp/TM1637.

## Setting it up
This library requires that you have three components:
- 1 ioBit called DIO (data input output)
- 1 ioBit called CLK (clock)
- the delayUS component (for some timing stuff in the library)

Other than naming them correctly, no additional setup is required.

## Wiring
So assuming that you are using the grove 4 digit display:
- Whatever pin you assign to CLK goes to CLK
- The pin you assign to DIO goes to DIO
- Power goes to 3.3V or 5V(either works)
- GND goes to ground 

## Using the Library

Use setBrightness to set the brightness and then any of the numbers prefixed with show. ShowNumberDec is recommended for 
most integer based displaying. 

Setbrightess is likely best placed outside of the for(;;) loop in main so that it is called only once, however if you want 
varying brightnesses for any reason, it still works fine inside of the infinite loop.

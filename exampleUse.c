/* ###################################################################
**     Filename    : main.c
**     Project     : TM1637_Test
**     Processor   : MC9S08QD4CPC
**     Version     : Driver 01.12
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2019-06-29, 15:09, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.12
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "CLK.h"
#include "DIO.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "TM1637_lib.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

void main(void)
{
  /* Write your local variable definition here */
  byte data[4];
  int i;
  data[0] = digitToSegment[1];
  data[1] = digitToSegment[3];
  data[2] = digitToSegment[5];
  data[3] = digitToSegment[7];
  setBrightness(0x0f, 1);
  setSegments(data, 4, 0);
  
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  for (;;) {
	  for(i = 0; i < 100; i++)
	  showNumberDec(i, 0, 4, 0);
  	  }
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/

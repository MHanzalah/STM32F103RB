/****************************************************************************/
/*!
*  @file    : main.c
*  @brief   : Main Entry
*  @author  : MHanz
*  @hardware: STM32F103RB
*  
*  --------------------------------------------------------------------------
*  @revision :
*  Ver  Author   Date               Changes
*--------------------------------------------------------------------------
*  1.0  Name     XXXX-XX-XX         Initial Release
*  
*/
/****************************************************************************/
#include <Common.h>
#include "Clock.h"
#include "BSP.h"
#include "Hal.h"

/*****************************************************************************/
/*!
*  @defgroup  main_group   Main Program
*  @brief     The Main Entry
*    @{
*
*/
/*****************************************************************************/
/*****************************************************************************/
/*!
*  @defgroup  main_define   Main Define
*  @brief     Definition in main program
*    @{
*
*/
/*****************************************************************************/
#define SYSTEMCLOCK_FREQ            1000U
#define SWITCH_PRESSED              13U

/*!********************* @} End of Main Define *******************************/
/*****************************************************************************/
/*!
*  @defgroup  main_lv   Main Local Variables
*  @brief     Local variables in main program
*    @{
*
*/
/*****************************************************************************/
static volatile BOOL       g_bSystemTick = FALSE;
static volatile BOOL       g_bSwitch     = FALSE;

/*!********************* @} End of Main Local Variables **********************/
/*****************************************************************************/
/*!
*  @defgroup  main_implementation   Main Implementation
*  @brief     Implementation of main program
*  @{
*
*/
/*****************************************************************************/
int main(void) 
{
  /* Initialize ports and peripherals */
  BSPInit();

  /* Generate interrupt each 1 ms */
  SysTick_Config( SystemCoreClock/SYSTEMCLOCK_FREQ );

  /* Prints out System Clock Speed in Debug */
  TRACE("System Clock Speed %d Hz \r\n", SystemCoreClock );

  while(1)
  {
    if( FALSE != g_bSwitch )
      LED_ON();
    else
      LED_OFF();
  }

  return 0;
}
/*!********************* @} End of Main Implementation ***********************/
/*****************************************************************************/
/*!
*  @defgroup  main_if   Main Interrupt functions
*  @brief     Interrupt Functions for main program
*    @{
*
*/
/*****************************************************************************/
/*****************************************************************************/
/*!
*  @brief  Handles System Tick Interrupts
*
*  @param  None
*
*  @return None
*/
/*****************************************************************************/
void SysTick_Handler( void )
{
    /* System Tick */
    g_bSystemTick = TRUE;

    if( FALSE != !(IN_BTN() >> SWITCH_PRESSED ) )
    {
      g_bSwitch = ~g_bSwitch;
    }
}
/*!********************* @} End of Main Interrupt Functions ******************/
/*!********************* @} End of Main Program ******************************/

/*************************** End of file *************************************/

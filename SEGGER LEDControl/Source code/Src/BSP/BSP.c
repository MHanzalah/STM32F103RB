/*****************************************************************************/
/*!
*  @file      : BSP.c
*  @brief     : Board Support Package
*  @author    : MHanz
*  @hardware  : STM32F130RB
*  
*  --------------------------------------------------------------------------
*  @revision :
*  Ver  Author   Date               Changes
*  --------------------------------------------------------------------------
*  1.0  Name     XXXX-XX-XX         Initial Release
*/
/*****************************************************************************/
#include <Common.h>
#include "Clock.h"
#include "Hal.h"
#include "BSP.h"

/*****************************************************************************/
/*!
*  @addtogroup  bsp_group   BSP Module
*  @brief       Board Support Package Module
*    @{
*
*/
/*****************************************************************************/
/*****************************************************************************/
/*!
*  @defgroup  bsp_functions   BSP Functions
*  @brief     Functions for Board Support Package module
*    @{
*
*/
/*****************************************************************************/
/*****************************************************************************/
/*!
*  @brief  Initialize Board Support Package
*
*  @param  None
*
*  @return None
*/
/*****************************************************************************/
void BSPInit( void )
{
    /* Use Internal Clock */
    Clock8MInternalInit();

    /* Update System Core Clock */
    SystemCoreClockUpdate();

    /* Hardware abstraction layer initialization */
    PortInit();
}
/*!********************* @} End of BSP Functions *****************************/
/*****************************************************************************/
/*!
*  defgroup  bsp_if   BSP Interrupt Functions
*  @brief    Interrupt functions for Board Support Package
*    @{
*
*/
/*****************************************************************************/
/*****************************************************************************/
/*!
*  @brief  Handles Hardfault cases
*
*  @param  None
*
*  @return None
*/
/*****************************************************************************/
void HardFault_Handler( void )
{
    TRACE( "Hard fault\n" );
    ASSERT( FALSE );

#ifndef _DEBUG
    NVIC_SystemReset();
#endif
}
/*!********************* @} End of BSP Interrupt Functions *******************/
/*!********************* @} End of BSP Module ********************************/
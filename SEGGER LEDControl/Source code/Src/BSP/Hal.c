 /*****************************************************************************/
/*!
*  @file      : Hal.c
*  @brief     : All ports and peripherals configuration
*  @author    : MHanz
*  @hardware  : STM32F130RB
*  
*  --------------------------------------------------------------------------
*  @revision :
*  Ver  Author   Date               Changes
*  --------------------------------------------------------------------------
*  1.0  Name     XXXX-XX-XX         Initial Release
*  
*/
/*****************************************************************************/
#include <Common.h>
#include "Hal.h"

/*****************************************************************************/
/*!
*  @addtogroup  hal_group   Hal Module
*  @brief       Hardware Abstraction Layer Module
*    @{
*
*/
/*****************************************************************************/
/*****************************************************************************/
/*!
*  @defgroup  hal_functions   Hal Functions
*  @brief     Functions for Hardware Abstraction Layer module
*    @{
*
*/
/*****************************************************************************/
/*****************************************************************************/
/*!
*  @brief  Initialize Ports and Peripherals
*
*  @param  None
*
*  @return None
*/
/*****************************************************************************/
void PortInit( void )
{
    /* IO Port A & C clock enabled */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN;

    /* Enable LED PA5 */
    GPIOA->CRL &= ~GPIO_CRL_CNF5;
    GPIOA->CRL |= GPIO_CRL_MODE5_0 | GPIO_CRL_MODE5_1;

}
/*!********************* @} End of Hal Function ******************************/
/*!********************* @} End of Hal Module ********************************/
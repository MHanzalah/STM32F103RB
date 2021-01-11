/*****************************************************************************/
/*!
*  @file      : IRQ.c
*  @brief     : Interrupt Requests Controller
*  @author    : lcgan
*  @hardware  : STM32F130RB
*  
*  --------------------------------------------------------------------------
*  @revision :
*  Ver  Author   Date               Changes
*  --------------------------------------------------------------------------
*  1.0  Name     XXXX-XX-XX         Initial Release
*  1.1  MHanz    2020-10-30         Added request controller to fit objectives
*  1.2  MHanz    2020-11-11         Format whitespaces and exceeding line
*  1.3  MHanz    2020-11-15         Doxygen formatted for documentation
*  
*/
/*****************************************************************************/
#include <Common.h>
#include "BSP.h"
#include "IRQ.h"

/*****************************************************************************/
/*!
*  @addtogroup  irq_group   IRQ Module
*  @brief       Intrerrupt Request Module
*    @{
*
*/
/*****************************************************************************/
/*****************************************************************************/
/*!
*  @defgroup  irq_globalvar   IRQ Global Variables
*  @brief     Global variables for Interrupt Request Module
*    @{
*
*/
/*****************************************************************************/
extern void EXTI2_US_ECHO_IRQHandler(uint32_t Status)__attribute__((weak));

/*!********************* @} End of IRQ Global Variables **********************/
/*****************************************************************************/
/*!
*  @defgroup  irq_functions   IRQ Functions
*  @brief     Functions for Interrupt Request module
*    @{
*
*/
/*****************************************************************************/
/*****************************************************************************/
/*!
*  @brief  Initialize NVIC Interrupts
*
*  @param  None
*
*  @return None
*/
/*****************************************************************************/
void IRQInit( void )
{
    NVIC_ClearPendingIRQ( EXTI15_10_IRQn );
    NVIC_EnableIRQ( EXTI2_IRQn );
    NVIC_EnableIRQ( EXTI4_IRQn );
    NVIC_EnableIRQ( EXTI9_5_IRQn );
    NVIC_EnableIRQ( EXTI15_10_IRQn );
}
/*****************************************************************************/
/*!
*  @brief  External Interrupt 0 (Unused)
*
*  @param  None
*
*  @return None
*/
/*****************************************************************************/
void EXTI0_IRQHandler( void )
{
    uint32_t irqStatus = EXTI->PR;

    if( 0 != (irqStatus & EXTI_PR_PR0) )
    {
        EXTI->PR = EXTI_PR_PR0;
    }
}
/*****************************************************************************/
/*!
*  @brief  External Interrupt 1 (Unused)
*
*  @param  None
*
*  @return None
*/
/*****************************************************************************/
void EXTI1_IRQHandler( void )
{
    uint32_t irqStatus = EXTI->PR;

    if( 0 != (irqStatus & EXTI_PR_PR1) )
    {
        EXTI->PR = EXTI_PR_PR1;
    }
}
/*****************************************************************************/
/*!
*  @brief  External Interrupt 2 (Used by Usonic)
*
*  @param  None
*
*  @return None
*/
/*****************************************************************************/
void EXTI2_IRQHandler( void )
{
    uint32_t irqStatus = EXTI->PR;

    if( 0 != (irqStatus & EXTI_PR_PR2) )
    {
        EXTI->PR = EXTI_PR_PR2;
        EXTI2_US_ECHO_IRQHandler( irqStatus );
    }
}
/*****************************************************************************/
/*!
*  @brief  External Interrupt 3 (Unused)
*
*  @param  None
*
*  @return None
*/
/*****************************************************************************/
void EXTI3_IRQHandler( void )
{
    uint32_t irqStatus = EXTI->PR;

    if( 0 != (irqStatus & EXTI_PR_PR3) )
    {
        EXTI->PR = EXTI_PR_PR3;
    }
}
/*****************************************************************************/
/*!
*  @brief  External Interrupt 4 (Unused)
*
*  @param  None
*
*  @return None
*/
/*****************************************************************************/
void EXTI4_IRQHandler( void )
{
    uint32_t irqStatus = EXTI->PR;

    if( 0 != (irqStatus & EXTI_PR_PR4) )
    {
        EXTI->PR = EXTI_PR_PR4;
    }
}
/*****************************************************************************/
/*!
*  @brief  External Interrupt 5 (Unused)
*          External Interrupt 6 (Unused)
*          External Interrupt 7 (Unused)
*          External Interrupt 8 (Unused)
*          External Interrupt 9 (Unused)
*
*  @param  None
*
*  @return None
*/
/*****************************************************************************/
void EXTI9_5_IRQHandler( void )
{
    uint32_t irqStatus = EXTI->PR;

    if( 0 != (irqStatus & EXTI_PR_PR5) )
    {
        EXTI->PR = EXTI_PR_PR5;
    }

    if( 0 != (irqStatus & EXTI_PR_PR6) )
    {
        EXTI->PR = EXTI_PR_PR6;
    }

    if( 0 != (irqStatus & EXTI_PR_PR7) )
    {
        EXTI->PR = EXTI_PR_PR7;
    }

    if( 0 != (irqStatus & EXTI_PR_PR8) )
    {
        EXTI->PR = EXTI_PR_PR8;
    }

    if( 0 != (irqStatus & EXTI_PR_PR9) )
    {
        EXTI->PR = EXTI_PR_PR9;
    }
}
/*****************************************************************************/
/*!
*  @brief  External Interrupt 10 (Unused)
*          External Interrupt 11 (Unused)
*          External Interrupt 12 (Unused)
*          External Interrupt 13 (Unused)
*          External Interrupt 14 (Unused)
*          External Interrupt 15 (Unused)
*
*  @param  None
*
*  @return None
*/
/*****************************************************************************/
void EXTI15_10_IRQHandler( void )
{
    uint32_t irqStatus = EXTI->PR;

    if( 0 != (irqStatus & EXTI_PR_PR10) )
    {
        EXTI->PR = EXTI_PR_PR10;
    }

    if( 0 != (irqStatus & EXTI_PR_PR11) )
    {
        EXTI->PR = EXTI_PR_PR11;
    }

    if( 0 != (irqStatus & EXTI_PR_PR12) )
    {
        EXTI->PR = EXTI_PR_PR12;
    }

    if( 0 != (irqStatus & EXTI_PR_PR13) )
    {
        EXTI->PR = EXTI_PR_PR13;
    }

    if( 0 != (irqStatus & EXTI_PR_PR14) )
    {
        EXTI->PR = EXTI_PR_PR14;
    }

    if( 0 != (irqStatus & EXTI_PR_PR15) )
    {
        EXTI->PR = EXTI_PR_PR15;
    }
}

/*!********************* @} End of IRQ Function ******************************/
/*!********************* @} End of IRQ Module ********************************/

















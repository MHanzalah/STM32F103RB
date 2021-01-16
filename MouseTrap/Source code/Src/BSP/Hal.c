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
    /* IO Port B & TIMER1 & Alternate Function Clock enabled */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN
                  | RCC_APB2ENR_IOPBEN
                  | RCC_APB2ENR_IOPDEN
                  | RCC_APB2ENR_TIM1EN
                  | RCC_APB2ENR_AFIOEN;

    /* Ultrasound Trigger - PD1 */
    GPIOD->CRL &= ~GPIO_CRL_CNF1;
    GPIOD->CRL |= GPIO_CRL_MODE1_0 | GPIO_CRL_MODE1_1;

    /*
       Ultrasound Echo - PB2 
       Set as input with pull-up/pull-down
    */
    GPIOB->CRL &= ~GPIO_CRL_MODE2;
    GPIOB->CRL &= ~GPIO_CRL_CNF2;
    GPIOB->CRL |= GPIO_CRL_CNF2_1;

    /* External Interrupt for PB2 as source input */
    AFIO->EXTICR[0] &= ~AFIO_EXTICR1_EXTI2;
    AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI2_PB;

    /*
       Interrupt Mask Register - Not masked
       Event Mask Register - Not masked
       Rising Trigger Selection Register - Enabled
       Falling Trigger Selection Register - Enabled
    */
    EXTI->EMR |= EXTI_EMR_MR2;
    EXTI->IMR |= EXTI_IMR_MR2;
    EXTI->RTSR |= EXTI_RTSR_TR2;
    EXTI->FTSR |= EXTI_FTSR_TR2;

    /* Motor Direction = PA1 */
    GPIOA->CRL &= ~GPIO_CRL_CNF1;
    GPIOA->CRL |= GPIO_CRL_MODE1_0 | GPIO_CRL_MODE1_1;

    /* Motor PWM TIM4 CH1 = PB6 */
    GPIOB->CRL |= GPIO_CRL_MODE6_0 | GPIO_CRL_MODE6_1;
    GPIOB->CRL &= ~GPIO_CRL_CNF6;
    GPIOB->CRL |= GPIO_CRL_CNF6_1;

}
/*!********************* @} End of Hal Function ******************************/
/*!********************* @} End of Hal Module ********************************/
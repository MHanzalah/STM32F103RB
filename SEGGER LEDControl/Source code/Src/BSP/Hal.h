/*****************************************************************************/
/*!
*  @file      : Hal.h
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
#ifndef __HAL_DOT_H__
#define __HAL_DOT_H__

/*****************************************************************************/
/*!
*  @defgroup  hal_group   Hal Module
*  @brief     Hardware Abstraction Layer Module
*    @{
*
*/
/*****************************************************************************/
/*****************************************************************************/
/*!
*  @defgroup  hal_define   Hal Define
*  @brief     Definition for Hardware Abstraction Layer module
*    @{
*
*/
/*****************************************************************************/
#define PA_LED                 5U
#define PC_USER_BTN            13U

/*!********************* @} End of Hal Define ********************************/
/*****************************************************************************/
/*!
*  @defgroup  hal_macro   Hal Macro
*  @brief     Macros for Hardware Abstraction module
*    @{
*
*/
/*****************************************************************************/
#define IN_BTN()               (GPIOC->IDR & BIT(PC_USER_BTN) )
#define LED_ON()               (GPIOA->BSRR = BIT(PA_LED))
#define LED_OFF()              (GPIOA->BRR = BIT(PA_LED))

/*!********************* @} End of Hal Macro *********************************/
/*****************************************************************************/
/*!
*  @defgroup  hal_fp   Hal Functions Prototype
*  @brief     Functions prototype for Hardware Abstraction Layer module
*    @{
*
*/
/*****************************************************************************/
void PortInit( void );

/*!********************* @} End of Hal Functions Prototype *******************/
/*!********************* @} End of Hal Module ********************************/
#endif /* __HAL_DOT_H__ */
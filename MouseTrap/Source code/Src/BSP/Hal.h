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
#define PD_TRIGG               1U
#define PB_ECHO                2U

/*!********************* @} End of Hal Define ********************************/
/*****************************************************************************/
/*!
*  @defgroup  hal_macro   Hal Macro
*  @brief     Macros for Hardware Abstraction module
*    @{
*
*/
/*****************************************************************************/
#define US_TRIGG_ON()            (GPIOD->BSRR = BIT(PD_TRIGG))
#define US_TRIGG_OFF()           (GPIOD->BRR = BIT(PD_TRIGG))
#define US_TRIGG_SET( x )           ((x) ? US_TRIGG_ON() : US_TRIGG_OFF())

#define US_ECHO_IN()             ((GPIOB->IDR & BIT(PB_ECHO)) ? TRUE : FALSE )

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
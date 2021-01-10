/*****************************************************************************/
/*!
*  @file      : Clock.h
*  @brief     : Configure clock
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
#ifndef __CLOCK_DOT_H__
#define __CLOCK_DOT_H__

/*****************************************************************************/
/*!
*  @defgroup  clock_group   Clock Module
*  @brief     Clock Module
*    @{
*
*/
/*****************************************************************************/
/*****************************************************************************/
/*!
*  @defgroup  clock_fp   Clock Functions Prototype
*  @brief     Functions prototype for Clock module
*    @{
*
*/
/*****************************************************************************/
void Clock8MInternalInit( void );
void ClockSetWaitStates( uint32_t nSysClock );

/*!********************* @} End of Clock Functions Prototype *****************/
/*!********************* @} End of Clock Module ******************************/
#endif /* __CLOCK_DOT_H__ */
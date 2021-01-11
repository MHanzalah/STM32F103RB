/*****************************************************************************/
/*!
*  @file      : Clock.c
*  @brief     : Configure clock
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
#include "Clock.h"

/*****************************************************************************/
/*!
*  @addtogroup  clock_group   Clock Module
*  @brief       Clock Module
*    @{
*
*/
/*****************************************************************************/
/*****************************************************************************/
/*!
*  @defgroup  clock_define   Clock Define
*  @brief     Definition for Clock
*    @{
*
*/
/*****************************************************************************/
#define RCC_HSICALIBRATION_DEFAULT          0x10U
#define CLOCK_WAITTIME                      64000000
#define SYSCLOCK_24MHZ                      24000000U
#define SYSCLOCK_48MHZ                      48000000U
#define SYSCLOCK_72MHZ                      72000000U
#define RCC_CR_HSITRIMPOS                   3U

/*!********************* @} End of Clock Define ******************************/
/*****************************************************************************/
/*!
*  @defgroup  clock_functions   Clock Functions
*  @brief     Functions for Clock Module
*    @{
*
*/
/*****************************************************************************/
/*****************************************************************************/
/*!
*  @brief  Initializes SystemCoreClock 64MHz to use internal RC 8MHz
*          (by default for Nucleo)
*
*  @param  None
*
*  @return None
*/
/*****************************************************************************/
void Clock8MInternalInit( void )
{

  /* Enable Internal 8 MHz RC Oscillator (HSI) */
  RCC->CR |= RCC_CR_HSION;

  /* Wait for HSI clock to be stable */
  while( 0 == (RCC->CR&RCC_CR_HSIRDY) );

  /* 
    Adjust HSI calibration value by trimming value 
    Default value is 16 added to HSICAL alue
  */
  RCC->CR &= ~RCC_CR_HSITRIM;
  RCC->CR |= RCC_HSICALIBRATION_DEFAULT << RCC_CR_HSITRIMPOS;

  /* Clock configure register -select HSI as system clock */
  RCC->CFGR &= ~RCC_CFGR_SW;

  /* Disable PLL clock during configuration */
  RCC->CR &= ~RCC_CR_PLLON;

  /* Wait for PLL clock to be locked */
  while( 0 != (RCC->CR&RCC_CR_PLLRDY) );

  /* Clock configure register - select PLL as system clock */
  RCC->CFGR |= RCC_CFGR_SW_PLL;

  /* Wait for clock states */
  ClockSetWaitStates( CLOCK_WAITTIME );

  /* Clear AHB Clock division factor */
  RCC->CFGR &= ~RCC_CFGR_HPRE;

  /* SYSCLOCK not divided */
  RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

  /* APB2 high-speed prescaler HCLK not divided */
  RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;

  /* APB1 Low-speed prescaler HCLK divided by 2 */
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;

  /* HSI oscillator clock/2 selected as PLL input clock */
  RCC->CFGR &= ~RCC_CFGR_PLLSRC;

  /* Enable PLL multiplication factor */
  RCC->CFGR &= ~RCC_CFGR_PLLMULL;

  /* PLL input clock x 16 */
  RCC->CFGR |= RCC_CFGR_PLLMULL16;

  /* Enable PLL */
  RCC->CR |= RCC_CR_PLLON;

  /* Wait for PLL clock to be locked */
  while( 0 == (RCC->CR&RCC_CR_PLLRDY) );
}
/*****************************************************************************/
/*!
*  @brief  Set wait states for clock
*
*  @param  nSysClock   System Clock
*
*  @return None
*/
/*****************************************************************************/
void ClockSetWaitStates( uint32_t nSysClock )
{
  FLASH->ACR &= ~FLASH_ACR_LATENCY;

  if( nSysClock <= SYSCLOCK_24MHZ )
  {
    /* zero wait state */
    FLASH->ACR |= FLASH_ACR_LATENCY_0;
  }
  else if( nSysClock <= SYSCLOCK_48MHZ )
  {
    /* One wait state */
    FLASH->ACR |= FLASH_ACR_LATENCY_1;
  }
  else if( nSysClock <= SYSCLOCK_72MHZ )
  {
    /* Two wait states */
    FLASH->ACR |= FLASH_ACR_LATENCY_2;
  }
  else
  {
    ASSERT( FALSE );
  }
}
/*!********************* @} End of Clock Functions ***************************/
/*!********************* @} End of Clock Module ******************************/
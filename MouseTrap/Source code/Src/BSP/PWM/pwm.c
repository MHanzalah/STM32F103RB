#include <Common.h>
#include "Hal.h"
#include "Timer.h"
#include "pwm.h"

void PwmEnable( PTIMER_HANDLE pHandle,
                uint32_t nChannel,
                int nDutyCyclePercent,
                BOOL bInverse )
{
  TIM_TypeDef* timer;

  ASSERT( 0 != pHandle);

  timer = (TIM_TypeDef*)pHandle->pTimer;

  timer->CCMR1 |= TIM_CCMR1_OC1M;
  timer->CCR1 &= ~TIM_CCR1_CCR1;
  timer->CCR1 = (uint32_t)(timer->ARR
              * ((double)nDutyCyclePercent ) / 100 );

  timer->CR1 |= TIM_CR1_CEN | TIM_CR1_ARPE;
  timer->BDTR |= TIM_BDTR_MOE;
}

void PwmDisable( PTIMER_HANDLE pHandle, uint32_t nChannel )
{
  TIM_TypeDef* timer;

  ASERT( 0 != pHandle);

  timer = (TIM_TypeDef*)pHandle->pTimer;

  timer->CCMR1 &= ~TIM_CCMR1_OC1M;
}


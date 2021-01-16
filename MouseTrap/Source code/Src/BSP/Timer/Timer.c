#include <Common.h>
#include "Hal.h"
#include "Timer.h"

static volatile PTIMER_HANDLE g_aTimerIrqHandle[TOTAL_TIMER] = { 0, 0, 0, 0};

static void timer_IRQHandler( PTIMER_HANDLE pHandle );

int TimerInit( PTIMER_HANDLE pHandle,
               uint8_t nTimer,
               uint32_t nFreq,
               BOOL bPwmMode,
               BOOL bIrqEn )
{
  TIM_TypeDef* timer;
  IRQn_Type    irq;
  uint32_t     clock;
  uint32_t     count     = 0U;
  uint32_t     prescale  = 0U;

  ASSERT( 0 != pHandle );
  ASSERT( 0 != nFreq );

  /* Select TIMER to initialize */
  switch( nTimer )
  {
    case TIMER1:
            timer = TIM1;
            irq   = TIM1_UP_IRQn;
    break;

    case TIMER2:
            timer = TIM2;
            irq   = TIM2_IRQn;
    break;

    case TIMER3:
            timer = TIM3;
            irq   = TIM3_IRQn;
    break;

    case TIMER4:
            timer = TIM4;
            irq   = TIM4_IRQn;
    break;

    default:
            return TIMER_ERR_INVALID;
  }

  pHandle->pTimer             = timer;
  pHandle->Irq                = irq;

  g_aTimerIrqHandle[nTimer-1] = pHandle;

  /* 
    DIR : 0 - Upcounting
    OPM : 0 - Counter doesnt stop at update event
    CKD : 0 - 1:1 ratio between timer clock and dead-time/sampling clock
    CMS : 0 - Edge-aligned mode - depends on DIR
  */
  timer->CR1 &= ~( TIM_CR1_DIR
                  | TIM_CR1_OPM
                  | TIM_CR1_CKD
                  | TIM_CR1_CMS );


  switch( RCC->CFGR & RCC_CFGR_PPRE1 )
  {
    case RCC_CFGR_PPRE1_DIV1:
            clock = SystemCoreClock;
    break;

    case RCC_CFGR_PPRE1_DIV2:
            clock = SystemCoreClock>>1U;
    break;

    case RCC_CFGR_PPRE1_DIV4:
            clock = SystemCoreClock>>2U;
    break;

    case RCC_CFGR_PPRE1_DIV8:
            clock = SystemCoreClock>>3U;
    break;

    case RCC_CFGR_PPRE1_DIV16:
            clock = SystemCoreClock>>4U;
    break;
  }

  /* Calculate auto reload counter and its prescalar */
  count = clock / ( nFreq >> 1U );

  while( count >= 0xffffU )
  {
    /* Prescale is needed since the count over 16 bits */
    count = clock / ( nFreq >> 1U);

    /* Increase prescalar */
    prescale++;

    /* Divide again */
    count /= ( prescale + 1 );
  }

  if( 0 != prescale )
  {
    /* Prescaler is applicable */
    timer->PSC = prescale;
  }

  /* Store remaining count into auto reload counter register */
  timer->ARR = count;

  /* Enable update generation interrupt in event register */
  timer->EGR |= TIM_EGR_UG;

  if( bPwmMode == TRUE )
  {
    /* OFF both compare outputs */
    timer->CCMR1 = 0;
    timer->CCMR2 = 0;
  }

  else
  {
    /* Enable Timer counting */
    timer->CR1 |= TIM_CR1_CEN | TIM_CR1_ARPE;
  }

  if( bPwmMode == FALSE )
  {
    /* Enable Timer Update Interrupt */
    timer->DIER |= TIM_DIER_UIE;

    NVIC_EnableIRQ( irq );
  }

  return TIMER_OK;
}

void TimerAddHook( PTIMER_HANDLE pHandle,
                   PTIMER_HOOK pHook,
                   TIMER_CB_UPDATE* pfUpdate )
{
  ASSERT( 0 != pHandle );
  ASSERT( 0 != pHook );
  ASSERT( 0 != pfUpdate );

  pHook->pfUpdate = pfUpdate;
  pHook->pNext = pHandle->pHeadHook;
  pHandle->pHeadHook = pHook;
}

static void timer_IRQHandler( PTIMER_HANDLE pHandle )
{
  TIM_TypeDef* timer = pHandle->pTimer;
  PTIMER_HOOK head;
  int status;

  /* Get status from status register */
  status = timer->SR;

  ASSERT( 0 != pHandle );

  if( 0 != (status & TIM_SR_UIF) )
  {
    timer->SR &= ~TIM_SR_UIF;

    if( 0 != pHandle->pHeadHook )
    {
      /* Traversing linked list */
      for( head=pHandle->pHeadHook; 0 != head; head=head->pNext )
      {
        ASSERT( 0 != head->pfUpdate );
        head->pfUpdate();
      }
    }
  }
}

void TIM1_UP_TIM10_IRQHandler( void )
{
  timer_IRQHandler( g_aTimerIrqHandle[0] );
}

void TIM2_IRQHandler( void )
{
  timer_IRQHandler( g_aTimerIrqHandle[1] );
}

void TIM3_IRQHandler( void )
{
  timer_IRQHandler( g_aTimerIrqHandle[2] );
}

void TIM4_IRQHandler( void )
{
  timer_IRQHandler( g_aTimerIrqHandle[3] );
}
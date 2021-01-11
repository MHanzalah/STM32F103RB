#ifndef __TIMER_DOT_H__
#define __TIMER_DOT_H__

#define TIMER_OK              0
#define TIMER_ERR_INVALID     1
#define TIMER1                1U
#define TIMER2                2U
#define TIMER3                3U
#define TIMER4                4U

#define TOTAL_TIMER           4U

/* Call back for TIMER */
typedef void TIMER_CB_UPDATE( void );

/* A linked list of TIMER */
typedef struct _tagTimer_Hook
{

  TIMER_CB_UPDATE*        pfUpdate;
  struct _tagTimer_Hook*  pNext;

}TIMER_HOOK, *PTIMER_HOOK;

/* A handler for TIMER */
typedef struct _tagTimer_Handle
{

  void*                   pTimer;
  int                     Irq;
  PTIMER_HOOK             pHeadHook;

}TIMER_HANDLE, *PTIMER_HANDLE;

int TimerInit(  PTIMER_HANDLE pHandle,
                uint8_t nTimer,
                uint32_t nFreq,
                BOOL bIrqEn );

void TimerAddHook(  PTIMER_HANDLE pHandle,
                    PTIMER_HOOK pHook,
                    TIMER_CB_UPDATE* pfUpdate );

#endif /* __TIMER_DOT_H__ */
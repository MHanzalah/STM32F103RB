#include <Common.h>
#include "Hal.h"
#include "Timer.h"
#include "Ultrasound.h"

static TIMER_HOOK             g_TimerHook;
static PUSONIC_HANDLE         g_pusonicIrqHandles[TOTAL_USONIC];
static double                 g_dTimerUsConst     = 0;
static int                    g_nTriggerConst     = 0;

static void usonic_cbOnTimer( void );

int USonicInit( PTIMER_HANDLE pHandle, int nTimerFreq )
{
  int cnt;

  ASSERT( 0 != pHandle );
  ASSERT( 0 != nTimerFreq );

  /* Timer too slow */
  if( nTimerFreq < US_TIMER_FREQ_MIN )
  {
    return USONIC_TIMER_FREQ_INVALID;
  }

  /* Reset handles to 0 */
  for( cnt=0; cnt<TOTAL_USONIC; cnt++ )
  {
    g_pusonicIrqHandles[cnt] = 0;
  }

  /* Timer period in us */
  g_dTimerUsConst = US_TIMER_FREQ_MAX / nTimerFreq;

  if( g_dTimerUsConst > US_TIMER_FREQ_THRES )
  {
    g_nTriggerConst = 1;
  }
  else
  {
    g_nTriggerConst = US_TIMER_FREQ_THRES / g_dTimerUsConst;
  }

  /* Add timer callback */
  TimerAddHook( pHandle, &g_TimerHook, usonic_cbOnTimer );

  return USONIC_SUCCESS;
}

int USonicAddDevice( PUSONIC_HANDLE pHandle,
                     uint8_t nIndex,
                     USONIC_CB_ON_TRIGGER* pfOnTrigger,
                     USONIC_CBI_READY* pfOnReady )
{
  ASSERT( 0 != pHandle);
  ASSERT( 0 != pfOnTrigger );
  ASSERT( 0 != pfOnReady );

  if( nIndex > TOTAL_USONIC )
  {
    /* Not in range */
    return USONIC_INVALID;
  }

  if( 0 != g_pusonicIrqHandles[nIndex])
  {
    /* Initialized and overwritten not allowed */
    return USONIC_INUSE;
  }

  /* Setting handle to default */
  pHandle->nDistance          = 0;
  pHandle->nTimeout           = 0;
  pHandle->nTimeoutConst      = (int)((double)(US_ECHO_TIMEOUT*US_FACTOR)
                              / g_dTimerUsConst);

  pHandle->nTimerTick         = 0;
  pHandle->nTrigger           = 0;
  pHandle->bValidEdge         = FALSE;
  pHandle->nDistanceMax       = US_DEFAULT_DIST_MAX;
  pHandle->pfOnTrigger        = pfOnTrigger;
  pHandle->pfOnReady          = pfOnReady;

  g_pusonicIrqHandles[nIndex] = pHandle;

  return USONIC_SUCCESS;
}

void USonicTrigger( PUSONIC_HANDLE pHandle )
{
  ASSERT( 0 != pHandle );

  /* Timeout after trigger complete */
  pHandle->nTimeout = 0;

  /* Reload trigger rising time */
  pHandle->nTrigger = g_nTriggerConst;

  /* Reset edge detection */
  pHandle->bValidEdge = FALSE;

  /* Callback to set trigger pin high */
  pHandle->pfOnTrigger( TRUE );
}

void USonicSetEchoTimeOut( PUSONIC_HANDLE pHandle,
                           int nTimeoutMs,
                           int nDistMax )
{
  ASSERT( 0 != pHandle );

  pHandle->nTimeoutConst = (int)((double)(nTimeoutMs*US_FACTOR)
                          / g_dTimerUsConst);

  if( 0 != nDistMax)
  {
    pHandle->nDistanceMax = nDistMax;
  }
}

uint32_t USonicRead( PUSONIC_HANDLE pHandle )
{
  ASSERT( 0 != pHandle );

  return pHandle->nDistance;
}

void USonicISR( PUSONIC_HANDLE pHandle, BOOL bEcho )
{
  uint32_t dist;

  ASSERT( 0 != pHandle );

  if( FALSE != bEcho)
  {
    pHandle->nTimerTick = 0;
    pHandle->bValidEdge = TRUE;

    return;
  }

  if( FALSE != pHandle->bValidEdge )
  {
    pHandle->bValidEdge = FALSE;

    /* Use previous value if counter is zero */
    if( 0 != pHandle->nTimerTick )
    {
     /* Distance calculation with ticks according to datasheet */
      dist = (uint32_t)((((double)pHandle->nTimerTick * g_dTimerUsConst)
           / US_FORMULA_FACTOR) * US_CONVERSION_FACTOR);
    }

    /* Limit is 4 cm */
    if( dist > US_LIMIT)
    {
      pHandle->nDistance = dist;
      pHandle->nTimeout = 0;
      pHandle->pfOnReady();
    }
  }
}

static void usonic_cbOnTimer( void )
{
  int cnt;

  PUSONIC_HANDLE usonic;

  for( cnt=0; cnt<TOTAL_USONIC; cnt++)
  {
    usonic = g_pusonicIrqHandles[cnt];

    if( 0 == usonic)
    {
      continue;
    }

    usonic->nTimerTick++;

    /* Check if trigger need to pull low */
    if( 0 != usonic->nTrigger )
    {
      usonic->nTrigger--;

      if( 0!= usonic->nTrigger )
      {
        /* Trigger time reached - Pull to low */
        usonic->pfOnTrigger( FALSE );

        /* Activate timeout in case missing echo or too long*/
        usonic->nTimeout = usonic->nTimeoutConst;
      }
    }

    /* Check timeout for far distance */
    if( 0 != usonic->nTimeout )
    {
      usonic->nTimeout--;

      if( 0 == usonic->nTimeout )
      {
        if( cnt == 0)
        {
          usonic->nDistance = usonic->nDistanceMax;
        }
        else
        {
          usonic->nDistance = usonic->nDistanceMax;
        }

        usonic->nTimerTick    = 0;
        usonic->nTimeout      = 0;
        usonic->nTrigger      = 0;
        usonic->bValidEdge    = FALSE;
        usonic->pfOnTrigger( TRUE );
        usonic->pfOnReady();
      }
    }
  }
}
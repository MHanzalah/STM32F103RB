#ifndef __ULTRASOUND_DOT_H__
#define __ULTRASOUND_DOT_H__

#define USONIC_SUCCESS                0
#define USONIC_FAILED                -1
#define USONIC_INVALID               -2
#define USONIC_INUSE                 -3
#define USONIC_TIMER_FREQ_INVALID    -4

#define US_ECHO_TIMEOUT               18U     /* ms, for 300cm->17.46ms, */
#define TOTAL_USONIC                  1U
#define US_DEFAULT_DIST_MAX           20000U
#define US_TIMER_FREQ_MIN             10000U  /* 10KHz */
#define US_TIMER_FREQ_MAX             1000000.0
#define US_TIMER_FREQ_THRES           10.0
#define US_FACTOR                     1000
#define US_LIMIT                      200
#define US_FORMULA_FACTOR             58.0
#define US_CONVERSION_FACTOR          100

typedef void USONIC_CBI_READY( void );
typedef void USONIC_CB_ON_TRIGGER( BOOL bOn );

typedef struct _tagUSONIC_HANDLE
{
  TIMER_HOOK               TimerHook;
  volatile uint32_t        nTimerTick;
  volatile uint32_t        nTrigger;
  volatile int             nTimeout;
  volatile int             nTimeoutConst;
  volatile uint32_t        nDistance;
  volatile uint32_t        nDistanceMax;
  volatile BOOL            bValidEdge;

  USONIC_CB_ON_TRIGGER*    pfOnTrigger;
  USONIC_CBI_READY*        pfOnReady;
}USONIC_HANDLE, *PUSONIC_HANDLE;

typedef struct _tagUsonic_Dist
{
  int nDist[TOTAL_USONIC];
}USONIC_DIST, *PUSONIC_DIST;

typedef struct _tagUS_Status
{
  uint32_t Status;
  uint32_t bUSonic    :1;

}US_STATUS, *PUS_STATUS;

int USonicInit( PTIMER_HANDLE pHandle, int nTimerFreq );
int USonicAddDevice( PUSONIC_HANDLE pHandle,
                     uint8_t nIndex,
                     USONIC_CB_ON_TRIGGER* pfOnTrigger,
                     USONIC_CBI_READY* pfOnReady );

void USonicTrigger( PUSONIC_HANDLE pHandle );
void USonicSetEchoTimeOut( PUSONIC_HANDLE pHandle,
                           int nTimeoutMs,
                           int nDistMax );

uint32_t USonicRead( PUSONIC_HANDLE pHandle );
void USonicISR( PUSONIC_HANDLE pHandle, BOOL bEcho );

#endif /* __ULTRASOUND_DOT_H__ */
#include <Common.h>
#include "BSP.h"
#include "Hal.h"
#include "IRQ.h"
#include "Timer.h"
#include "Ultrasound.h"


/* SYSTEM AND TIMER */
#define SYSTEMCLOCK_FREQ              1000U
#define TIMER1_TICK_HZ                10000U
#define SYS_TICK_MS                   100U

/* USONIC */
#define TOTAL_USONIC                  1U
#define USONIC_TIMEOUT_MS             13U
#define USONIC_TICK_MS                2U
#define USONIC_FREQ                   20000U

#define GREATER_FACTOR_1            12
#define LOWER_FACTOR_1              10
#define GREATER_FACTOR_2            10
#define LOWER_FACTOR_2              8

/* SYSTEM AND TIMER */
static TIMER_HANDLE                   g_Timer1Handle;
static volatile BOOL                  g_bSystemTick         = FALSE;
static volatile int                   g_nSystemTick         = SYS_TICK_MS;
static volatile int                   g_nDelayms            = 0;

/* USONIC */
static USONIC_HANDLE            g_USHandles[TOTAL_USONIC];
static volatile BOOL            g_bUSonicTickReady    = FALSE;
static volatile int             g_nUSonicTick         = USONIC_TICK_MS;
static int                      g_nUsonicIdx          = 0;
static volatile US_STATUS       g_USonicStatus;
static volatile US_STATUS       g_PrevObstacleStatus;
static USONIC_DIST              g_UsonicDist;
static USONIC_DIST              g_UsonicDist_prev[3];

static void main_ultraSoundInit( void );
static void main_UsonicExe( void );

static void main_cbUSOnTrigger( BOOL bON );
static void main_cbUSOnReady( void );

void main(void) 
{
  /* Initialize ports and peripherals */
  BSPInit();

  /* Prints out System Clock */
  TRACE( "System Clock Speed %d Hz\r\n", SystemCoreClock );

  /* Generate interrupt each 1 ms */
  SysTick_Config( SystemCoreClock/SYSTEMCLOCK_FREQ );

  /* Initialize timer for Ultrasonic */
  TimerInit( &g_Timer1Handle, TIMER1, TIMER1_TICK_HZ, TRUE );

  /* Ultrasound module initialization */
  main_ultraSoundInit();

  /* NVIC Interrupt enable */
  IRQInit();

  while(1)
  {
     /* Check if ready to read Usonic */
     if( FALSE != g_bUSonicTickReady )
     {
       /* Reset Usonic flag */
       g_bUSonicTickReady = FALSE;

       /* Read Usonic */
       main_UsonicExe();

       TRACE("Distance: %d\r\n", g_UsonicDist.nDist[0] );
     }
  }
}

static void main_cbUSOnTrigger( BOOL bON )
{
    US_TRIGG_SET( bON );
}

static void main_cbUSOnReady( void )
{
    g_USonicStatus.bUSonic = TRUE;
}

static void main_ultraSoundInit( void )
{
    int cnt;

    /* Ultrasonic initialization */
    USonicInit( &g_Timer1Handle, USONIC_FREQ );

    /* Add a callback to get notify when ultrasonic sensor is ready to read */
    USonicAddDevice( &g_USHandles[0],
                     0U,
                     main_cbUSOnTrigger,
                     main_cbUSOnReady );

    /* Set TimeoutMs to 12ms(equals 2.55m) and DistMax to -1 to indicate */
    /* an invalid measurement */
    for( cnt=0; cnt<TOTAL_USONIC; cnt++ )
    {
        USonicSetEchoTimeOut(&g_USHandles[cnt], USONIC_TIMEOUT_MS, -1);
    }

    USonicTrigger( &g_USHandles[0] );
}

static void main_UsonicExe( void )
{
    BOOL done = FALSE;
    int cnt;
    int A,B,C;

    if( 0 != g_USonicStatus.bUSonic )
    {
        /* Check which sensor is ready */
        for( cnt=0; cnt<TOTAL_USONIC; cnt++ )
        {
            if( 0 == (g_USonicStatus.bUSonic & BIT(cnt)) )
            {
                continue;
            }
    
            g_USonicStatus.bUSonic &= ~BIT(cnt);
    
            /* Keep old distance values for filtering */
            g_UsonicDist_prev[2].nDist[cnt] = g_UsonicDist_prev[1].nDist[cnt];
            g_UsonicDist_prev[1].nDist[cnt] = g_UsonicDist_prev[0].nDist[cnt];
    
            /* Read new distance value */
            g_UsonicDist_prev[0].nDist[cnt] = USonicRead( &g_USHandles[cnt] );

            /* Formulate three different cases */

            /* Difference in recent and previous */
            A = abs(g_UsonicDist_prev[0].nDist[cnt]
              - g_UsonicDist_prev[1].nDist[cnt]);
    
            /* Difference in previous and the past */
            B = abs(g_UsonicDist_prev[1].nDist[cnt]
              - g_UsonicDist_prev[2].nDist[cnt]);
    
            /* Difference in recent and the past */
            C = abs(g_UsonicDist_prev[0].nDist[cnt]
              - g_UsonicDist_prev[2].nDist[cnt]);
    
            /* Select and save the most accurate data */
    
            /* Check if first case is more accurate */
            if(A<B && A<C)
            {
                /* Ensure validity of magnitude */
                if( LOWER_FACTOR_1*g_UsonicDist_prev[0].nDist[cnt] 
                  < GREATER_FACTOR_1*g_UsonicDist_prev[1].nDist[cnt] 
                 && GREATER_FACTOR_2*g_UsonicDist_prev[0].nDist[cnt] 
                  > LOWER_FACTOR_2*g_UsonicDist_prev[1].nDist[cnt] )
                {
                    /* Get average between recent and previous */
                    g_UsonicDist.nDist[cnt] = (g_UsonicDist_prev[0].nDist[cnt] 
                                            + g_UsonicDist_prev[1].nDist[cnt])
                                            / 2;
                }
            }
            /* Check if second case is more accurate */
            else if(B<C)
            {
                /* Ensure validity of magnitude */
                if( LOWER_FACTOR_1*g_UsonicDist_prev[1].nDist[cnt] 
                  < GREATER_FACTOR_1*g_UsonicDist_prev[2].nDist[cnt] 
                 && GREATER_FACTOR_2*g_UsonicDist_prev[1].nDist[cnt] 
                  > LOWER_FACTOR_2*g_UsonicDist_prev[2].nDist[cnt] )
                {
                    /* Get average between previous and the past */
                    g_UsonicDist.nDist[cnt] = (g_UsonicDist_prev[1].nDist[cnt] 
                                            + g_UsonicDist_prev[2].nDist[cnt])
                                            / 2;
                }
            }
            /* Check if third case is more accurate */
            else if(C<B)
            {
                /* Ensure validity of magnitude */
                if( LOWER_FACTOR_1*g_UsonicDist_prev[0].nDist[cnt] 
                  < GREATER_FACTOR_1*g_UsonicDist_prev[2].nDist[cnt] 
                 && GREATER_FACTOR_2*g_UsonicDist_prev[0].nDist[cnt] 
                  > LOWER_FACTOR_2*g_UsonicDist_prev[2].nDist[cnt] )
                {
                    /* Get average between recent and the past */
                    g_UsonicDist.nDist[cnt] = (g_UsonicDist_prev[0].nDist[cnt] 
                                            + g_UsonicDist_prev[2].nDist[cnt])
                                            / 2;
                }
            }
            /* Check for invalid case */
            else if(g_UsonicDist_prev[0].nDist[cnt]==-1 
                 && g_UsonicDist.nDist[cnt]!=0 )
            {
                g_UsonicDist.nDist[cnt]=-1;
            }
    
            /* Iterates for each sensor */
            g_nUsonicIdx = cnt + 1;
            if(g_nUsonicIdx>=TOTAL_USONIC)
            {
                done = TRUE;
                g_nUsonicIdx = 0;
            }
            USonicTrigger( &g_USHandles[g_nUsonicIdx] );
    
            break;
        }
    }
}

void SysTick_Handler( void )
{
    /* System Tick */
    g_bSystemTick = TRUE;

    /* USonic Tick */
    if( 0 != g_nUSonicTick )
    {
        g_nUSonicTick--;
        if( 0 == g_nUSonicTick )
        {
            g_nUSonicTick = USONIC_TICK_MS;
            g_bUSonicTickReady = TRUE;
        }
    }
}

void EXTI2_US_ECHO_IRQHandler( uint32_t Status )
{
    UNUSE( Status );

    USonicISR(&g_USHandles[0], US_ECHO_IN() );
}

/*************************** End of file ****************************/

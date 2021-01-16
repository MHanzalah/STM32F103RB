#ifndef __PWM_DOT_H__
#define __PWM_DOT_H__

void PwmEnable( PTIMER_HANDLE pHandle,
                uint32_t nChannel,
                int nDutyCyclePercent,
                BOOL bInverse );

void PwmDisable( PTIMER_HANDLE pHandle, uint32_t nChannel );

#endif /* __PWM_DOT_H__ */
#ifndef __MOTOR_DOT_H__
#define __MOTOR_DOT_H__

#define MOTORS_STOP()                  M_PWM_DIS()

#define MOTORS_RUN()                   M_DIR_ON() \
                                       M_PWM_EN()

void MotorsMove( void );

#endif
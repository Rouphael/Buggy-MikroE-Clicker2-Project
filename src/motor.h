/* 
 * File:   motor.h
 * Author: Rafael
 */

#ifndef MOTOR_H
#define	MOTOR_H

#define OCxRS 7200

void PWM_Init(void);
void motor(int left_pwm,int right_pwm);

#endif	/* MOTOR_H */


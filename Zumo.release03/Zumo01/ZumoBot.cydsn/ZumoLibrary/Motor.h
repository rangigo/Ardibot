/**
 * @file    Motor.h
 * @brief   Motor header file
 * @details If you want to use Motor methods, Include Motor.h file.
*/
#ifndef MOTOR_H_ 
#define MOTOR_H_ 

#include <project.h>

void motor_start(); // start motor PWM timers
void motor_stop();  // stop motor PWM timers

/* moving forward */
void motor_forward(uint8 speed,uint32 delay);

/* moving left when l_speed < r_speed or moving right when l_speed > r_speed */
void motor_turn(int l_speed, int r_speed, uint32 delay);

/* moving backward */
void motor_backward(uint8 speed,uint32 delay);

void motor_static_turn_r(uint32 delay);
void motor_static_turn_l(uint32 delay);
void motor_forward_distance(uint32 delay);

#endif
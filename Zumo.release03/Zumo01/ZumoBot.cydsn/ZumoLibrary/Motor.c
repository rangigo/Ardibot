/**
 * @file    Motor.c
 * @brief   Basic methods for operating motor sensor. For more details, please refer to Motor.h file. 
 * @details included in Zumo shield
*/
#include "Motor.h"


/**
* @brief    Starting motor sensors
* @details  
*/
void motor_start()
{
    PWM_Start();
}


/**
* @brief    Stopping motor sensors
* @details
*/
void motor_stop()
{
    PWM_Stop();
}


/**
* @brief    Moving motors forward
* @details  giveing same speed to each side of PWM to make motors go forward
* @param    uint8 speed : speed value
* @param    uint32 delay : delay time
*/
void motor_forward(uint8 speed,uint32 delay)
{
    MotorDirLeft_Write(0);      // set LeftMotor forward mode
    MotorDirRight_Write(0);     // set RightMotor forward mode
    PWM_WriteCompare1(speed); 
    PWM_WriteCompare2(speed); 
    CyDelay(delay);
}


/**
* @brief    Moving motors to make a turn 
* @details  moving left when l_speed < r_speed or moving right when l_speed > r_speed
* @param    uint8 l_speed : left motor speed value
* @param    uint8 r_speed : right motor speed value
* @param    uint32 delay : delay time
*/
void motor_turn(int l_speed, int r_speed, uint32 delay)
{
    if (l_speed >= 0) MotorDirLeft_Write(0); else {MotorDirLeft_Write(1); l_speed = -l_speed;}
    if (r_speed >= 0) MotorDirRight_Write(0); else {MotorDirRight_Write(1); r_speed = -r_speed;}
    PWM_WriteCompare1(l_speed); 
    PWM_WriteCompare2(r_speed); 
    CyDelay(delay);
}


/**
* @brief    Moving motors backward
* @details  setting backward mode to each motors and gives same speed to each side of PWM
* @param    uint8 speed : speed value
* @param    uint32 delay : delay time
*/
void motor_backward(uint8 speed,uint32 delay)
{
    MotorDirLeft_Write(1);      // set LeftMotor backward mode
    MotorDirRight_Write(1);     // set RightMotor backward mode
    PWM_WriteCompare1(speed); 
    PWM_WriteCompare2(speed); 
    CyDelay(delay);
}

void motor_static_turn_r(uint32 delay) {
    uint8 static_speed = 100;
    MotorDirLeft_Write(0);
    MotorDirRight_Write(1);
    PWM_WriteCompare1(static_speed);
    PWM_WriteCompare2(static_speed);
    CyDelay(delay);
}

void motor_static_turn_l(uint32 delay) {
    uint8 static_speed = 100;
    MotorDirLeft_Write(1);
    MotorDirRight_Write(0);
    PWM_WriteCompare1(static_speed);
    PWM_WriteCompare2(static_speed);
    CyDelay(delay);
}

void motor_forward_distance(uint32 delay)
{
    MotorDirLeft_Write(0);      // set LeftMotor forward mode
    MotorDirRight_Write(0);     // set RightMotor forward mode
    PWM_WriteCompare1(200); 
    PWM_WriteCompare2(200); 
    CyDelay(delay*1000/48);
}
/*! @mainpage Example 1.5 Modularized and with doxygen comments
* @date Friday, January 29, 2021
* @authors Pablo Gomez, Ariel Lutenberg and Eric Pernia
* @section genDesc General Description
*
* This is a preliminary implementation of the smart home system, where the
* code has been modularized using functions and documented using Doxygen.
* The entry point to the program documentation can be found at
* this \ref Example_1_5_Modularized_withDoxygenComments.cpp "link"
*
* @section genRem General Remarks
* [Write here relevant information about the program]
*
*/

//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "servo_motor.h"
#include "windshield_wiper.h"
#include "wiper_system.h"

//=====[Declaration of private defines]========================================

#define TIME_PERIOD 0.02
#define DUTY_MIN            0.025
#define DUTY_MAX            0.125

//=====[Declaration and initialization of private global objects]===============

PwmOut Servo(PF_9);

//=====[Declaration and initialization of private global variables]=============

/**
 *  The speed of the motor chosen from a selection of presets
 */
static motor_speed_t rpm_motor;

/**
 *  The angle (as a duty cycle) the motor is intending to be at
 */
static float target_angle;

/**
 *  The current angle (as a duty cycle) the motor is at
 */
static float current_angle = 0;

/**
 *  The time accumulated for the purpose of using delays
 */
static int Accumulated_Time_In_MS = 0;

//=====[Implementations of public functions]===================================

void servoMotorInit(){
    Servo.period(TIME_PERIOD);
    Servo.write(DUTY_MIN);
}

void servoMotorUpdate(){
    switch (rpm_motor) {
        case LOW_SPEED:
            if (Accumulated_Time_In_MS > TIME_INCREMENT_MS) 
            {
                int dir = 0;
                if (abs(current_angle - target_angle) > (1.8/1850))
                {
                    Servo.write(current_angle);
                    if (target_angle - current_angle > 0)
                    {
                        dir = 1;
                    }
                    else 
                    {
                        dir = -1;
                    }
                    current_angle += dir*1.8/1850;
                }
            }
            else
            {
               Servo.write(current_angle);
            }
        break;
        case HI_SPEED:
            Servo.write(target_angle);
        break;
    }
    Accumulated_Time_In_MS += TIME_INCREMENT_MS;
}

void setSpeed(motor_speed_t speed){
    rpm_motor = speed;
}

void setAngle(float degrees){

    target_angle = 0.025 + (degrees)/1850;
}

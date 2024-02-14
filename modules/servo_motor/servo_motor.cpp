#include "mbed.h"
#include "arm_book_lib.h"
#include "servo_motor.h"
#include "windshield_wiper.h"

#define DUTY_HIGH_BACKWARD 0.05
#define DUTY_LOW_BACKWARD 0.0625
#define DUTY_OFF 0.075
#define DUTY_LOW_FORWARD 0.0875
#define DUTY_HIGH_FORWARD 0.1
#define TIME_PERIOD 0.02
#define DUTY_CYCLE_CST_FORWARD 0.000357
#define DUTY_CYCLE_CST_BACKWARD 0.000417
#define DUTY_ANGLE_CST 0.006

float DutyCycle = 0.075;
float rpm_motor;
float angle_motor;
float TimeInMS = 0;
PwmOut Servo(PF_9);
float Accumulated_Time_In_MS = 0;

void servoMotorInit(){
    Servo.period(TIME_PERIOD);
    Servo.write(DUTY_OFF);
}

void servoMotorUpdate(){
    if (-60<rpm_motor<70){
        if (rpm_motor > 0){
        DutyCycle = 0.075 + DUTY_CYCLE_CST_FORWARD* rpm_motor;
    }
        else{
        DutyCycle = 0.075 - DUTY_CYCLE_CST_BACKWARD* rpm_motor;
    }
    }
    TimeInMS = (rpm_angle *0.06)/rpm_motor;
    if (Accumulated_Time_In_MS < TimeInMS);
        Servo.write(DutyCycle);
        Accumulated_Time_In_MS = Accumulated_Time_In_MS + TIME_INCREMENT_MS;
    else{
        Servo.write(DutyOFF);
        Accumulated_Time_In_MS = 0;
    }
    
}


void setSpeed(int rpm){
    rpm_motor = rpm;   
}


/**
 *  Sets the taget angle for the servo to turn to
 */
void setAngle(int degrees){
    rpm_angle = degrees;
}



//=====[#include guards - end]=================================================


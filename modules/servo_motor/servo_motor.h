//=====[#include guards - begin]===============================================

#ifndef _SERVO_MOTOR_H_
#define _SERVO_MOTOR_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

typedef enum {
    LOW_SPEED,
    HI_SPEED
} motor_speed_t;

//=====[Declarations (prototypes) of public functions]=========================

void servoMotorInit();
void servoMotorUpdate();
/**
 *  Sets the speed of the motor given some rpm
 */


void setSpeed(motor_speed_t rpm);

/**
 *  Sets the target angle for the servo to turn to
 */
void setAngle(float degrees);

//=====[#include guards - end]=================================================

#endif // _SERVO_MOTOR_H_
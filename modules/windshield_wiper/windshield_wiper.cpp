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
#include "windshield_wiper.h"
#include "wiper_system.h"
#include "servo_motor.h"
#include "ignition.h"

//=====[Declaration of private defines]========================================

/**
 *  The delay times that are used for the up and down swings of the wiper
 */
#define WIPER_LOW_SPEED_TIME_UP_MS    1000
#define WIPER_LOW_SPEED_TIME_DOWN_MS  1000
#define WIPER_HI_SPEED_TIME_UP_MS     400
#define WIPER_HI_SPEED_TIME_DOWN_MS   400

/**
 *  Delay times for the different intermittent wiper modes in milleseconds
 */
#define SHORT_TIME_DELAY               3000
#define MEDIUM_TIME_DELAY              5000
#define LONG_TIME_DELAY                8000

/**
 *  Threshold values for the wiper mode selector
 */
#define WIPER_MODE_INPUT_OFF           0.2
#define WIPER_MODE_INPUT_LOW           0.4
#define WIPER_MODE_INPUT_INT           0.6

/**
 *  Threshold values for the intermittent time delay selector
 */
#define WIPER_DELAY_INPUT_SHORT        0.33
#define WIPER_DELAY_INPUT_MEDIUM       0.66

/**
 *  The maximum angle position of the windshield wiper
 */
#define WIPER_UP_POSITION              67.0

//=====[Declaration of private data types]=====================================

/**
 *  A state variable which represents what part of a wipe cycle the wiper is in
 */
typedef enum {
    UP_SWING,
    DOWN_SWING,
    HOLD,
} wiper_process_state_t;

//=====[Declaration and initialization of private global objects]===============

/**
 *  The wiper mode selector is a user input which controls wiper behavior
 */
AnalogIn windshield_wiper_mode(A0);

/**
 *  In the intermittent mode, this user input selects the delay length
 */
AnalogIn windshield_wiper_delay_mode(A1);

//=====[Declaration and initialization of private global variables]=============

/**
 *  Used to cause delays between windshield wipe actions
 */
static int accumulated_delay_ms = 0;

/**
 *  Sometimes different delay lengths are required. This stores those differences
 */
static int delay_time_ms = 0;

/**
 *  The windshield wiper should keep track of which speed mode it is using
 */
static motor_speed_t wiper_speed = LOW_SPEED;

/**
 *  The state of the wiper module
 */
static wiper_process_state_t wiperProcessState = HOLD;


//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void windshieldWiperInit() 
{

}

void windshieldWiperUpdate() 
{
    servoMotorUpdate();
    if (isIgnition()) 
    {
        windshield_wiper_state_t wiperState = getWindshieldWiperState();
        switch (wiperState)
        {
            case WIPER_OFF:
                setAngle(0);
                setSpeed(LOW_SPEED);
                wiperProcessState = HOLD;
            break;
            case WIPER_LO: case WIPER_INT:
                setSpeed(LOW_SPEED);
                wiper_speed = LOW_SPEED;
            break;
            case WIPER_HI:
                setSpeed(HI_SPEED);
                wiper_speed = HI_SPEED;
            break;
        }

        switch (wiperProcessState)
        {
            case UP_SWING:
                setAngle(WIPER_UP_POSITION);
                if (wiper_speed == LOW_SPEED) 
                {
                    delay_time_ms = WIPER_LOW_SPEED_TIME_UP_MS;
                }
                else 
                {
                    delay_time_ms = WIPER_HI_SPEED_TIME_UP_MS;
                }
                if (accumulated_delay_ms > delay_time_ms)
                {
                    accumulated_delay_ms = 0;
                    setAngle(0);
                    wiperProcessState = DOWN_SWING;
                }
            break;
            case DOWN_SWING:
                setAngle(0);
                if (wiper_speed == LOW_SPEED) 
                {
                    delay_time_ms = WIPER_LOW_SPEED_TIME_DOWN_MS;
                }
                else 
                {
                    delay_time_ms = WIPER_HI_SPEED_TIME_DOWN_MS;
                }
                if (accumulated_delay_ms > delay_time_ms)
                {
                    accumulated_delay_ms = 0;
                    wiperProcessState = HOLD;
                }
            break;
            case HOLD:
                setAngle(0);
                if (wiperState == WIPER_INT) {
                    switch (getWindshieldWiperDelay())
                    {
                        case SHORT:
                            delay_time_ms = SHORT_TIME_DELAY;
                        break;
                        case MEDIUM:
                            delay_time_ms = MEDIUM_TIME_DELAY;
                        break;
                        case LONG:
                            delay_time_ms = LONG_TIME_DELAY;
                        break;
                    }
                    if (accumulated_delay_ms > delay_time_ms)
                    {
                        accumulated_delay_ms = 0;
                        wiperProcessState = UP_SWING;
                    }
                } else {
                    if (wiperState != WIPER_OFF) {
                        setAngle(WIPER_UP_POSITION);
                    }
                    wiperProcessState = UP_SWING;
                }
            break;
        }

        accumulated_delay_ms += TIME_INCREMENT_MS;
    } else {
        setSpeed(LOW_SPEED);
        setAngle(0);
    }
}

windshield_wiper_state_t getWindshieldWiperState()
{
    if (windshield_wiper_mode.read() < WIPER_MODE_INPUT_OFF) 
    {
        return WIPER_OFF;
    } 
    else if (windshield_wiper_mode.read() < WIPER_MODE_INPUT_LOW)
    {
        return WIPER_LO;
    }
    else if (windshield_wiper_mode.read() < WIPER_MODE_INPUT_INT)
    {
        return WIPER_INT;
    }
    else
    {
        return WIPER_HI;
    }
}

windshield_wiper_delay_state_t getWindshieldWiperDelay()
{
    if (windshield_wiper_delay_mode.read() < WIPER_DELAY_INPUT_SHORT) 
    {  
        return SHORT;
    } 
    else if (windshield_wiper_delay_mode.read() < WIPER_DELAY_INPUT_MEDIUM)
    {
        return MEDIUM;
    }
    else
    {
        return LONG;
    }
}

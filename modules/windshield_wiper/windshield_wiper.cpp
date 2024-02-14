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
* @section changelog Changelog
*
* | Date | Description |
* |:----------:|:-----------------------------------------------|
* | 01/14/2024 | First version of program |
*
*
*/

//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "windshield_wiper.h"
#include "wiper_system.h"
#include "servo_motor.h"

#define WIPER_LOW_SPEED_RPM              30
#define WIPER_HI_SPEED_RPM               40

#define WIPER_LOW_SPEED_TIME_MS         372
#define WIPER_HI_SPEED_TIME_MS          291

#define SHORT_TIME_DELAY               3000
#define MEDIUM_TIME_DELAY              5000
#define LONG_TIME_DELAY                8000

typedef enum {
    UP_SWING,
    DOWN_SWING,
    HOLD
} wiper_process_state_t;

//=====[Declaration and initialization of public global objects]===============

AnalogIn windshield_wiper_mode(A0);
AnalogIn windshield_wiper_delay_mode(A1);

//=====[Declaration and initialization of public global variables]=============

int accumulated_delay_ms = 0;
int wiper_speed = 0;
wiper_process_state_t wiperProcessState = HOLD;


//=====[Declarations (prototypes) of public functions]=========================

//Implementation of global functions

void windshieldWiperInit() 
{

}

void windshieldWiperUpdate() 
{
    windshield_wiper_state_t wiperState = getWindshieldWiperState();
    switch (wiperState)
    {
        case WIPER_OFF:
            setAngle(0);
            wiperProcessState = HOLD;
        break;
        case WIPER_LO: case WIPER_INT:
            wiper_speed = WIPER_LOW_SPEED_RPM;
        break;
        case WIPER_HI:
            wiper_speed = WIPER_HI_SPEED_RPM;
        break;
    }

    switch (wiperProcessState)
    {
        int delay_time_ms;
        case UP_SWING:
            if (wiper_speed == WIPER_LOW_SPEED_RPM) 
            {
                setSpeed(WIPER_LOW_SPEED_RPM);
                delay_time_ms = WIPER_LOW_SPEED_TIME_MS;
            }
            else 
            {
                setSpeed(WIPER_HI_SPEED_RPM);
                delay_time_ms = WIPER_HI_SPEED_TIME_MS;
            }
            if (accumulated_delay_ms > delay_time_ms)
            {
                accumulated_delay_ms = 0;
                wiperProcessState = DOWN_SWING;
            }
        break;
        case DOWN_SWING:
            if (wiper_speed == WIPER_LOW_SPEED_RPM) 
            {
                setSpeed(- WIPER_LOW_SPEED_RPM);
                delay_time_ms = WIPER_LOW_SPEED_TIME_MS;
            }
            else 
            {
                setSpeed(- WIPER_HI_SPEED_RPM);
                delay_time_ms = WIPER_HI_SPEED_TIME_MS;
            }
            if (accumulated_delay_ms > delay_time_ms)
            {
                accumulated_delay_ms = 0;
                wiperProcessState = HOLD;
            }
        break;
        case HOLD:
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
                wiperProcessState = UP_SWING;
            }
        break;
    }

    accumulated_delay_ms += TIME_INCREMENT_MS;
}

windshield_wiper_state_t getWindshieldWiperState()
{
    if (true) 
    {
        return WIPER_OFF;
    } 
    else if (true)
    {
        return WIPER_LO;
    }
    else if (true)
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
    if (true) 
    {  
        return SHORT;
    } 
    else if (true)
    {
        return MEDIUM;
    }
    else
    {
        return LONG;
    }
}

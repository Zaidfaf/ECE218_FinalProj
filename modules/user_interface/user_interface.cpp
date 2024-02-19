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
#include "user_interface.h"
#include "display.h"
#include "windshield_wiper.h"
#include "wiper_system.h"
#include "ignition.h"

//=====[Declaration of private defines]========================================

#define DISPLAY_REFRESH_TIME_MS 1000

//=====[Declarations (prototypes) of private functions]========================

/**
 *  Initializes the LCD display for the system
 */
static void userInterfaceDisplayInit();

/**
 *  Updates the LCD display for the system
 */
static void userInterfaceDisplayUpdate();

//=====[Implementations of public functions]===================================

void userInterfaceInit()
{
    userInterfaceDisplayInit();
}

void userInterfaceUpdate()
{
    userInterfaceDisplayUpdate();
}

//=====[Implementations of private functions]===================================

static void userInterfaceDisplayInit()
{
    displayInit();
}

static void userInterfaceDisplayUpdate()
{
    static int accumulatedDisplayTime = 0;
    
    if( accumulatedDisplayTime >=
        DISPLAY_REFRESH_TIME_MS ) {
        accumulatedDisplayTime = 0;
        if (isIgnition()) {
            switch(getWindshieldWiperState()) {
                case WIPER_OFF:
                    displayCharPositionWrite ( 0,0 );
                    displayStringWrite( "WS Mode: OFF   " );
                    displayCharPositionWrite ( 0,1 );
                    displayStringWrite( "                " );
                    break;
                case WIPER_LO:
                    displayCharPositionWrite ( 0,0 );
                    displayStringWrite( "WS Mode: LOW   " );
                    displayCharPositionWrite ( 0,1 );
                    displayStringWrite( "                " );
                    break;
                case WIPER_HI:
                    displayCharPositionWrite ( 0,0 );
                    displayStringWrite( "WS Mode: HIGH  " );
                    displayCharPositionWrite ( 0,1 );
                    displayStringWrite( "                " );
                    break;
                case WIPER_INT:
                    displayCharPositionWrite ( 0,0 );
                    displayStringWrite( "WS Mode: INT   " );
                    switch(getWindshieldWiperDelay()) {
                    case SHORT:
                        displayCharPositionWrite ( 0,1 );
                        displayStringWrite( "WS DELAY: SHORT " );
                        break;
                    case MEDIUM:
                        displayCharPositionWrite ( 0,1 );
                        displayStringWrite( "WS DELAY: MEDIUM" );
                        break;
                    case LONG:
                        displayCharPositionWrite ( 0,1 );
                        displayStringWrite( "WS DELAY: LONG  " );
                        break;
                    }
                    
                break;
            }   
        } else {
            displayCharPositionWrite ( 0,0 );
            displayStringWrite( "   Welcome to   " );
        
            displayCharPositionWrite ( 0,1 );
            displayStringWrite( "    your car    " );
        }
    } else {
        accumulatedDisplayTime =
            accumulatedDisplayTime + TIME_INCREMENT_MS;        
    } 
}
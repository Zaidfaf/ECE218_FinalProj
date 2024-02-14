#include "mbed.h"
#include "arm_book_lib.h"
#include "user_interface.h"
#include "display.h"
#include "windshield_wiper.h"

static void userInterfaceDisplayInit();
static void resetDisplay();
static void userInterfaceDisplayUpdate();


void userInterfaceInit()
{
    userInterfaceDisplayInit();
}

void userInterfaceUpdate()
{
    userInterfaceDisplayUpdate();
}

static void userInterfaceDisplayInit()
{
    displayInit();
     
    displayCharPositionWrite ( 3,0 );
    displayStringWrite( "Welcome to" );
 
    displayCharPositionWrite ( 4,1 );
    displayStringWrite( "your car" );
}

static void resetDisplay(){
    displayCharPositionWrite ( 0,0 );
    displayStringWrite( "                " );
 
    displayCharPositionWrite ( 0,1 );
    displayStringWrite( "                " );
}
static void userInterfaceDisplayUpdate()
{
    static int accumulatedDisplayTime = 0;
    char temperatureString[3] = "";
    
    if( accumulatedDisplayTime >=
        DISPLAY_REFRESH_TIME_MS ) {

        accumulatedDisplayTime = 0;

        switch(getWindshieldWiperState());
        case WIPER_OFF:
            resetDisplay()
            displayCharPositionWrite ( 0,0 );
            displayStringWrite( "WS Mode: OFF" );
        case WIPER_LOW:
            resetDisplay()
            displayCharPositionWrite ( 0,0 );
            displayStringWrite( "WS Mode: LOW" );
        case WIPER_HI:
            resetDisplay()
            displayCharPositionWrite ( 0,0 );
            displayStringWrite( "WS Mode: HIGH" );
        case WIPER_INT:
            resetDisplay()
            displayCharPositionWrite ( 0,0 );
            displayStringWrite( "WS Mode: INT" );
            switch(getWindshieldWiperDelay());
            case SHORT:
                displayCharPositionWrite ( 0,1 );
                displayStringWrite( "WS DELAY: SHORT   " );
            case MEDIUM:
                displayCharPositionWrite ( 0,1 );
                displayStringWrite( "WS DELAY: MEDIUM  " );
            case LONG:
                displayCharPositionWrite ( 0,1 );
                displayStringWrite( "WS DELAY: LONG    " );


    } else {
        accumulatedDisplayTime =
            accumulatedDisplayTime + SYSTEM_TIME_INCREMENT_MS;        
    } 
}
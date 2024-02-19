//=====[#include guards - begin]===============================================

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

//=====[Declarations (prototypes) of public functions]=========================

/**
 *  Intializes the LCD display
 */
void displayInit( void );

/**
 *  Changes the location of the LCDs "cursor" to a given x and y
 */
void displayCharPositionWrite( uint8_t charPositionX, uint8_t charPositionY );

/**
 *  Write a string to the LCD display
 */
void displayStringWrite( const char * str );

//=====[#include guards - end]=================================================

#endif // _DISPLAY_H_
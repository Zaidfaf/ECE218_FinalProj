//=====[#include guards - begin]===============================================

#ifndef _WINDSHIELD_WIPER_H_
#define _WINDSHIELD_WIPER_H_

//=====[Declaration of public data types]======================================

/**
 *  The possible behaviors of the windshield wiper
 */
typedef enum {
    WIPER_OFF,
    WIPER_LO,
    WIPER_INT,
    WIPER_HI
} windshield_wiper_state_t;

/**
 *  The possible delay times of the windshield wiper
 */
typedef enum {
    SHORT,
    MEDIUM,
    LONG
} windshield_wiper_delay_state_t;

//=====[Declarations (prototypes) of public functions]=========================

/**
 *  Initialisze the winshield wiper module
 */
void windshieldWiperInit();

/**
 *  Update the windshield wipers
 */
void windshieldWiperUpdate();

/**
 *  Returns the current state (behavior) of the windshield wipers
 */
windshield_wiper_state_t getWindshieldWiperState();

/**
 *  Returns the current delay length of the intermittent mode
 */
windshield_wiper_delay_state_t getWindshieldWiperDelay();

//=====[#include guards - end]=================================================

#endif // _WINDSHIELD_WIPER_H_
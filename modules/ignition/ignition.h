//=====[#include guards - begin]===============================================

#ifndef _IGNITION_H_
#define _IGNITION_H_

//=====[Declarations (prototypes) of public functions]=========================

/**
 *  Initializes the ignition module
 */
void ignitionInit();

/**
 *  Updates the ignition module
 */
void ignitionUpdate();

/**
 *  Returns true if the ignition is on, false otherwise
 */
bool isIgnition();

//=====[#include guards - end]=================================================

#endif // _IGNITION_H_
#include "mbed.h"
#include "arm_book_lib.h"
#include "ignition.h"
#include "user_interface.h"
#include "windshield_wiper.h"
#include "wiper_system.h"

// main() runs in its own thread in the OS
int main()
{
    ignitionInit();
    userInterfaceInit();
    windshieldWiperInit();
    while (true) {
        ignitionUpdate();
        userInterfaceUpdate();
        windshieldWiperUpdate();
        delay(TIME_INCREMENT_MS);
    }
}


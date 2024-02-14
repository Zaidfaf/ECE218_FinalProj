#include "mbed.h"
#include "ignition.h"
#include "user_interface.h"
#include "windshield_wiper.h"

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
    }
}


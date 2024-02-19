Fafouri, Zaid and Harrington, Collin

---

**Windshield Wiper System**

This project prototypes the windshield wiper system of a motor vehicle. It allows a user to select from four windshield wiper modes,
OFF, LOW, INTERMITTENT, and HIGH. In the INTERMITTENT mode, the wipers pause in between sweeps based on a user selected delay time of
SHORT, MEDIUM, or LONG. In the LOW and HIGH modes, the windhsield wipers move at different speeds, roughly 30 and 40 rpm respectively.
All information about the current mode of the wipers is displayed to the user and a mock ignition system is included in the prototype.

---

**Ignition Subsystem**
Specification | Result | Comments
--- | --- | ---
When the ignition button is pressed and the driver is seated, the blue LED turns on | PASS | ---
If the driver leaves the vehicle, the ignition continues running | PASS | ---
Pressing and releasing the ignition button turns off the engine when it is on | PASS | ---

---

**Wiper Subsystem**
Specification | Result | Comments
--- | --- | ---
When the engine is running and the wiper mode is OFF, the wiper does not run and returns to zero position | PASS | ---
When the engine is running and the wiper mode is LO, the wiper runs at ~30rpm and does continuous sweeps| PASS | ---
When the engine is running and the wiper mode is HI, the wiper runs at ~40rpm and does continuous sweeps | PASS | ---
When the engine is running and the wiper mode is INT, the wiper runs at ~30rpm, doing one sweep at a time and delaying based on a user selected delay time | PASS | ---
Each INT time selection delays for the correct amount of time | PASS | ---
If the engine is off, the wipers do not sweep | PASS | ---
A display shows the current wiper mode (and wiper delay time if pertinent) | PASS | ---
If the engine is turned off or the wiper mode is set to off, the wiper returns to the zero position after completing its current cycle | PASS | ---
If the wiper is in intermittent mode and waiting to begin a sweep when the engine is turned off or the wiper mode is changed to off, the wiper remains at the zero position and does not begin a sweep | PASS | ---

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
Start the engine (i.e., light the blue LED) while the driver’s seat is occupied and when the ignition button is pushed | PASS | ---
Keep the engine running even if the driver should exit the vehicle | PASS | ---
When the engine is running, stop the engine when the ignition button is pushed and released | PASS | ---

---

**Wiper Subsystem**
Specification | Result | Comments
--- | --- | ---
If the engine is running, and the user selects HI, LO, INT, or OFF, run the wipers in the appropriate mode, with the typical parameter values | PASS | ---
Read the desired delay time for INT mode from the intermittent delay time selector | PASS | ---
Do not run the wipers if the engine is not running | PASS | ---
Display the selected mode, including the delay time selection (SHORT, MEDIUM, or LONG) for intermittent mode | PASS | ---
If the wiper mode selector is turned to OFF, or the engine is turned off, then if the wiper is moving, in any mode, complete the current cycle and return the wipers to 0 degrees | PASS | ---
If the wiper is hesitating in INT mode, remain stationary | PASS | ---

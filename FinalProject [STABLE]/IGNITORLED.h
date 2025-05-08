#include <msp430.h>

// Function Prototypes

/*
    void ignitorInit();
    Used to initiate the pins needed for the ignitor LED to operate.
*/
void ignitorInit();

/*
    void controlPilotValve(char state);
    Used to turn the ignitor LED on or off based on the input state.
    If state==1, the LED is turned on. If state==0, the LED is turned off.
*/
void controlIgnitor(char state);

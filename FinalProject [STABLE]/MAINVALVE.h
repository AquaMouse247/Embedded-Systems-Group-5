#include <msp430.h>

// Function Prototypes

/*
    void mainValveInit();
    Used to initiate the pins needed for the main valve
    to operate.
*/
void mainValveInit();

/*
    void controlMainValve(int setpoint);
    Used to open and close the main valve based on the given setpoint.
    500 -> -90 degrees
    1500 -> 0 degrees
    2500 -> +90 degrees
*/
void controlMainValve(int setpoint);

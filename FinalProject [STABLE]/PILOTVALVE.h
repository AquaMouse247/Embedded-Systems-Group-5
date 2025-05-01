#include <msp430.h>

// Function Prototypes

/*
    void pilotValveInit();
    Used to initiate the pins needed for the pilot valve
    to operate.
*/
void pilotValveInit();

/*
    void controlPilotValve(char state);
    Used to open and close the pilot valve base on the input state.
    If state==1, the valve is opened. If state==0, the valve is closed.
*/
void controlPilotValve(char state);
#include <msp430.h>
#include <PILOTVALVE.h>

void pilotInit()
{
    // Configure P5.0 (Pilot Valve)
    P5OUT &= ~BIT0;                         // Clear P5.0 output latch for a defined power-on state
    P5DIR |= BIT0;                          // Set P5.0 to output direction

}

void controlPilotValve(char state)
{
    // Pilot valve is open
    if (state==1)
    {
        P5OUT |= BIT0;      // Open the pilot valve
    }
    else
    {
        P5OUT &= ~BIT0;      // Close the pilot valve
    }
}

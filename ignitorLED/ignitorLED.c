#include <msp430.h>
#include "IGNITORLED.h"

void ignitorInit()
{
    // Configure P5.4 (Ignitor LED)
    P5OUT &= ~BIT4;                         // Clear P5.4 output latch for a defined power-on state
    P5DIR |= BIT4;                          // Set P5.4 to output direction

}

void controlIgnitor(char state)
{
    // Ignitor is on
    if (state==1)
    {
        P5OUT |= BIT4;      // Turn the LED on
    }
    else
    {
        P5OUT &= ~BIT4;      // Turn the LED off
    }
}

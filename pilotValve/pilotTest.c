#include "intrinsics.h"
#include <msp430.h>
#include "PILOTVALVE.h"


void main()
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    
    P1OUT &= ~BIT0;                         // Clear P1.0 output latch for a defined power-on state
    P1DIR |= BIT0;                          // Set P1.0 to output direction

    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings

    pilotInit();

    char state = 1;

    controlPilotValve(state);
    while (1) {
        controlPilotValve(state);
        __delay_cycles(100000);
        state = ~state;
    }

}
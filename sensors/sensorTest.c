#include "intrinsics.h"
#include <msp430.h>
#include "SENSORS.h">

int pot = 0;
int therm = 0;
char flame = 0;
int flameVal = 0;

void main()
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    
    P1OUT &= ~BIT0;                         // Clear P1.0 output latch for a defined power-on state
    P1DIR |= BIT0;                          // Set P1.0 to output direction

    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings

    ADCInit();
    __bis_SR_register(GIE);  // Enable global interrupts

    while (1) {
        //pot = potRead();
        therm = thermRead();
        //flame = flameDetect();
        //flameVal = readFlame();
        // 3500 = 100C
        __delay_cycles(100000);
    }

}
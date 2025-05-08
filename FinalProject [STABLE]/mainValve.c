#include <msp430.h>
#include <MAINVALVE.h>


void mainValveInit()
{

    P2DIR |= BIT0;                      // P2.0 output
    P2SEL0 |= BIT0;                     // Set P2.0 to output using
    P2SEL1 &= ~BIT0;                    // Configure for timer TB1.1

    // The servo has range from -90 to +90 degrees, a total range of
    // 180 degrees. A 1ms pulse is -90 degrees, a 1.5ms pulse is 0 
    // degrees and a 2ms pulse is 90 degrees.

    // SMCLK = 1MHz -> 1 count = 1us
    // 20ms/1us = 20000

    TB1CCR0 = 20000-1;                         // PWM Period, 20 ms
    // 500 -> -90 degrees
    // 1500 -> 0 degrees
    // 2500 -> +90 degrees

    TB1CCTL1 = OUTMOD_7;                      // CCR1 reset/set
    TB1CCR1 = 1500;            // Initial duty cycle: 1.5 ms pulse (center/neutral for servo)

    TB1CTL = TBSSEL__SMCLK | MC__UP | TBCLR;  // SMCLK, up mode, clear TBR
}

void controlMainValve(int setpoint)
{

    TB1CCR1 = setpoint;                            // CCR1 PWM duty cycle
}

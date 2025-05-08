#include <msp430.h>
#include "TIMERS.h"

volatile unsigned int overflowCount = 0;    // Stores the timer's overflow value

void startFiveMinuteTimer()
{

    // Set P1.0 as output for LED
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;

    // Configure Timer_B0
    TB0CTL = TBSSEL__SMCLK | ID__8 | MC__CONTINUOUS | TBCLR; 
    // SMCLK, input divider /8, continuous mode, clear timer

    TB0CCTL0 = CCIE;                // Enable interrupt on CCR0
    TB0CTL |= TBIE;                 // Enable Timer_B overflow interrupt

}

// Timer_B overflow ISR
#pragma vector = TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void)
{
    switch (__even_in_range(TB0IV, TB0IV_TBIFG)) {
    case TB0IV_TBIFG: // Overflow
        overflowCount++;
        if (overflowCount >= OVERFLOWS_FOR_5_MINUTES)
        {
            overflowCount = 0;
            P1OUT ^= BIT0; // Toggle LED for verification
        }
        break;
    default: break;
    }
}

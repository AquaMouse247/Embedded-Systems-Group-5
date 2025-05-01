#include <msp430.h>
#include "TIMERS.h"

volatile unsigned int overflowCount = 0;

void fiveMinuteTimerInit()
{

    // Set P1.0 as output for LED
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;

    // Configure Timer_B0
    TB0CTL = TBSSEL__SMCLK | ID__8 | MC__CONTINUOUS | TBCLR; 
    // SMCLK, input divider /8, continuous mode, clear timer

    TB0CCTL0 = CCIE;                // Enable interrupt on CCR0 (optional)
    TB0CTL |= TBIE;                 // Enable Timer_B overflow interrupt

    //__enable_interrupt();           // Enable global interrupts
}

void thirstySecondTimerInit()
{

    // Set P1.0 as output for LED
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;

    // Timer_B setup: SMCLK (1MHz), divide by 8, continuous mode
    TB0CTL = TBSSEL__SMCLK | ID__8 | MC__CONTINUOUS | TBCLR;

    TB0CTL |= TBIE;          // Enable Timer_B overflow interrupt
    TB0CTL &= ~TBIFG;        // Clear any pending overflow flag

    //__enable_interrupt();    // Enable global interrupts
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
            P1OUT ^= BIT0; // Toggle LED for example
        }
        break;
    default: break;
    }
}


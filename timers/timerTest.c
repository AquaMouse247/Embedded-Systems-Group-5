//*******************************************************************************
//  MSP430FR235x Demo - Timer0_B3, PWM TB0.1-2, Up Mode, DCO SMCLK
//
//  Description: This program generates two PWM outputs on P1.6,P1.7 using
//  Timer0_B configured for up mode. The value in CCR0, 1000-1, defines the PWM
//  period and the values in CCR1 and CCR2 the PWM duty cycles. Using ~1MHz
//  SMCLK as TBCLK, the timer period is ~1ms with a 75% duty cycle on P1.6
//  and 25% on P1.7.
//  ACLK = default REFO ~32768Hz, MCLK = SMCLK = default DCODIV ~1MHz
//
//
//           MSP430FR2355
//         ---------------
//     /|\|               |
//      | |               |
//      --|RST            |
//        |     P6.2/TB3.3|--> RED
//        |     P6.1/TB3.2|--> GRN
//        |     P6.0/TB3.1|--> BLU
//
//
//   Darren Lu
//   Texas Instruments Inc.
//   Oct. 2016
//   Built with IAR Embedded Workbench v6.50 & Code Composer Studio v6.2
//******************************************************************************
#include "intrinsics.h"
#include "msp430fr2355.h"
#include <msp430.h>
#include <TIMERS.h>


// For RGB LED
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                 // Stop WDT

    //setupFiveMinuteTimer();
    setupTimerFor30Seconds();


    P1DIR |= BIT0;                      // P1.0 output
    P1OUT &= ~BIT0;
    
    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    while (1)
    {

    }
}

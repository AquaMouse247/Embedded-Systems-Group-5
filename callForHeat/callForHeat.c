
#include <msp430.h>
#include "CFH.h"


void CFHInit()
{
    // Configure P3.1
    P3SEL0 &= ~BIT1;    // Set P3.1 as GPIO
    P3SEL1 &= ~BIT1;    // Set P3.1 as GPIO
    P3DIR &= ~BIT1;      // Configure P3.1 as input
    P3OUT &= ~BIT1;      // Configure P3.1 as pulled-down
    P3REN &= ~BIT1;      // P3.1 pull-down register enable
}

char readCFH()
{
    char CFH = 0;

    //Checks if P3.1 is HIGH
    if(P3IN & BIT1)
    {
        CFH = 1;        // Turn on the call for heat 
    }
    else
    {
        //P3.1 is LOW
        CFH = 0;        // Turn off the call for heat 
    }
    return CFH;
}

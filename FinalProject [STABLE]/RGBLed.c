#include "intrinsics.h"
#include <RGBLed.h>
#include <SYSTEM.h>

enum systemStates{HEATING, IDLE, FLAMELOST, OVERHEAT, RANGE};

void RGBInit()
{

    P6DIR |= BIT0 | BIT1 | BIT2;                     // P6.0, P6.1, and P6.2 output
    P6SEL0 |= BIT0 | BIT1 | BIT2;                    // Set P6.0-P6.2 to oouptus using
    P6SEL1 &= ~(BIT0 | BIT1 | BIT2);                 // TB3.1-TB3.3.

    // The RGB LED we are using is common anode.
    // This means that the duty cycle is inverted.
    // We could either manually invert the duty cycle or switch
    // to output mode 3.

    TB3CCR0 = 1024-1;                         // PWM Period

    TB3CCTL1 = OUTMOD_3;                      // CCR1 set/reset
    TB3CCR1 = 750;                            // CCR1 PWM duty cycle - blue
    
    TB3CCTL2 = OUTMOD_3;                      // CCR2 set/reset
    TB3CCR2 = 250;                            // CCR2 PWM duty cycle - green

    TB3CCTL3 = OUTMOD_3;                      // CCR3 set/reset
    TB3CCR3 = 500;                            // CCR3 PWM duty cycle - red

    TB3CTL = TBSSEL__SMCLK | MC__UP | TBCLR;  // SMCLK, up mode, clear TBR
}

// Sets the color of an RGB LED using red, green, and blue color values between
// 0 and 255.
void setRGBColor(char red, char green, char blue)
{
    TB3CCR3 = red << 2; 
    TB3CCR2 = green << 2;
    TB3CCR1 = blue << 2;
}

// Sets the color of an RGB LED based on the given state.
void setSystemStatus(int state)
{
    char red;
    char green;
    char blue;

    switch (state)
    {
        case HEATING: // Orange
            red = 255;
            green = 153;
            blue = 0;
            blink = 0;
            break;
        case IDLE: // Blue
            red = 0;
            green = 0;
            blue = 255;
            break;
        case FLAMELOST: // Red
            red = 255;
            green = 0;
            blue = 0;
            blink = 0;
            break;
        case RANGE: // Within range
            red = 0;
            green = 255;
            blue = 0;
            blink = 0;
            break;
        case OVERHEAT: // Purple
            red = 144;
            green = 0;
            blue = 255;
            blink = 0;
            break;
    }

    TB3CCR3 = red << 2;         // Set intensity of red LED
    TB3CCR2 = green << 2;       // Set intensity of green LED
    TB3CCR1 = blue << 2;        // Set intensity of blue LED

}

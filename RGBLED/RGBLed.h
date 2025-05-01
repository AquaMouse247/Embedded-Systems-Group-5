#include <msp430.h>

// Function Prototypes

/*
    void RGBInit();
    Initializes the RGB LED pins.
*/
void RGBInit();

/*
    void setRGBColor(char red, char green, char blue);
    Sets the color of an RGB LED using red, green, and blue 
    color values between 0 and 255.
*/
void setRGBColor(char red, char green, char blue);

/*
    void setSystemStatus(int state);
    Sets the color of an RGB LED based on the given state.
*/
void setSystemStatus(int state);

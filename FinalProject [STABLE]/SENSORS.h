#include <msp430.h>


#define FLAMEVALUE 10;          // Value assigned to represent flame value

/*
    unsigned int thermRead();
    Reads the value from the thermistor and returns it.
*/
unsigned int thermRead();

/*
    unsigned int potRead();
    Reads the value from the potentiometer and returns it.
*/
unsigned int potRead();

/*
    char flameDetect();
    Reads in the value from the thermocouple and returns whether a flame was detected.
    Returns 1 if a flame was detected, otherwise returns 0.
*/
char flameDetect();

/*
    void ADCInit();
    Initializes the RGB LED pins.
*/
void ADCInit();

/*
    unsigned int readADC(char readChannel);
    Reads in the ADC value from the given channel and returns it.
*/
unsigned int readADC(char readChannel);

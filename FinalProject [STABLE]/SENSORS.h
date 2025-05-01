#include <msp430.h>


// Thermocouple
//unsigned int FLAMEVALUE = 1000;
#define FLAMEVALUE 1000;

unsigned int thermRead();
unsigned int potRead();
char flameDetect();

void ADCInit();
unsigned int readADC(char readChannel);

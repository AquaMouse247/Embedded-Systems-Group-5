#include <msp430.h>


// Thermocouple
//unsigned int FLAMEVALUE = 1000;
#define FLAMEVALUE 10;

unsigned int thermRead();
unsigned int potRead();
unsigned int readFlame();
char flameDetect();

void ADCInit();
unsigned int readADC(char readChannel);

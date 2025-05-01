#include "msp430fr2355.h"
#include <msp430.h>
#include "SENSORS.h"

// Contains functions for reading the thermistor, thermocouple, and potentiometer

// Thermistor - P1.5/A5
// Thermocouple - P1.3/A3
// Potentiometer - P1.4/A4

char ADCReading = 0;
unsigned int ADCResult = 0;

unsigned int thermRead()
{
    return readADC(5);
}

char flameDetect()
{
    return readADC(3) > FLAMEVALUE;
}
unsigned int readFlame()
{
    return readADC(3);
}

unsigned int potRead()
{
    // Min output -> 0
    // Max output -> 4095 (2^12)
    return readADC(4);
}

void ADCInit()
{
    // Configure ADC pins (this should be in init)
    P1SEL0 |= BIT3 | BIT4 | BIT5;
    P1SEL1 |= BIT3 | BIT4 | BIT5;

    // Configure ADC12
    ADCCTL0 |= ADCSHT_2 | ADCON;                                // ADCON, S&H=16 ADC clks
    ADCCTL1 |= ADCSHP;                                          // ADCCLK = MODOSC; sampling timer
    ADCCTL2 &= ~ADCRES;                                         // clear ADCRES in ADCCTL
    ADCCTL2 |= ADCRES_2;                                        // 12-bit conversion results
    ADCIE |= ADCIE0;                                            // Enable ADC conv complete interrupt

}

unsigned int readADC(char readChannel)
{
    switch(readChannel)
    {
        case 3:
            ADCMCTL0 |= ADCINCH_3;
            break;
        case 4:
            ADCMCTL0 |= ADCINCH_4;
            break;
        case 5:
            ADCMCTL0 |= ADCINCH_5;
            break;
        default:
            ADCMCTL0 |= ADCINCH_5;
            break;
    }
    ADCReading = 1;
    //ADCMCTL0 &= ~ADCINCH
    //ADCCTL0 &= ~ADCENC;
    //ADCMCTL0 |= readChannel            // ADC input select; Vref=AVCC
    ADCCTL0 |= ADCENC | ADCSC;         // Sampling and conversion start
    while(ADCReading);
    return ADCResult;
}

unsigned int valveSetpoint(int pot, int therm)
{
    // Calculate the difference between the pot setpoint
    // and the current boiler temp from the thermistor.

    

    int valve = 0;
    return valve;
}

// ADC interrupt service routine
#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void)
{
    switch(__even_in_range(ADCIV,ADCIV_ADCIFG))
    {
        case ADCIV_NONE:
            break;
        case ADCIV_ADCOVIFG:
            break;
        case ADCIV_ADCTOVIFG:
            break;
        case ADCIV_ADCHIIFG:
            break;
        case ADCIV_ADCLOIFG:
            break;
        case ADCIV_ADCINIFG:
            break;
        case ADCIV_ADCIFG:
            ADCResult = ADCMEM0;
            ADCReading = 0;
            break;
        default:
            break;
    }
}

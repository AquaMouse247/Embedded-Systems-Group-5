#include <msp430.h>


void fiveMinuteTimerInit();

void thirstySecondTimerInit();

#define OVERFLOWS_FOR_5_MINUTES 572 // Calculated below (maybe 229)
//#define OVERFLOWS_FOR_30_SECONDS 57  // See calculation below


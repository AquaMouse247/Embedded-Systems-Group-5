#include <msp430.h>

// Function Prototypes

/*
    void CFHInit();
    Initializes the call for heat pins.
*/
void CFHInit();

/*
    char readCFH();
    Reads in the call for heat and returns the current value.
    Returns 1 if the call for heat was recieved, otherwise returns 0.
*/
char readCFH();

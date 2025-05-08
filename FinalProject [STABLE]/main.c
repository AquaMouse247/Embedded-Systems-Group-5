#include <msp430.h>
#include "SYSTEM.h"
#include "intrinsics.h"
#include <stdio.h>

enum systemStates{HEATING, IDLE, FLAMELOST, OVERHEAT, RANGE}    // Defines all system states
state = IDLE;   // Set initial system state

char CFH = 0;           // Holds the call for heat value
char flameTimeout = 0;  // Holds the flame timer's timeout value
int flameLosses = 0;    // Holds the number of times the flame has been lost


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    
    P1OUT &= ~BIT0;                         // Clear P1.0 output latch for a defined power-on state
    P1DIR |= BIT0;                          // Set P1.0 to output direction

    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings

    // Initialize all subsystems
    RGBInit();
    pilotValveInit();
    mainValveInit();
    ignitorInit();
    ADCInit();

    __bis_SR_register(GIE);  // Enable global interrupts

    
    while(1)
    {
      __delay_cycles(100000);
      char cfh = 0;
      cfh = readCFH();

      // Check for call for heat
      if (cfh==1) // Call for heat received   
      {
        state=HEATING;
        controlIgnitor(1);
        __delay_cycles(100000);
        controlIgnitor(0);
      }
      else // Remain in idle state  
      {
        state=IDLE;
        controlPilotValve(0);
        controlMainValve(500);
      }
      __delay_cycles(100000);

      if (state==HEATING) // Call for heat received Heating state activated
      {
        __delay_cycles(100000);
        setSystemStatus(state); // RGB LED would change color to indicate CFH received
        controlPilotValve(1);   // Open pilot valve
        
        int setpoint = 0;
        setpoint = potRead();

        controlMainValve(setpoint);
        setSystemStatus(state);  // RGB LED would change color to indicate heating status
        int therm = thermRead();
        while(therm < setpoint) // While the boiler temp is less than the setpoint
        {
          int therm = thermRead();

          if (!flameDetect()) // If flame turns off during heating
          {
              controlMainValve(500); // Turn off main valve
              controlPilotValve(0); // Close pilot valve
              flameLosses++;        // Add to flame count
              if (flameLosses > 5)
              {
                  initFiveMinuteTimer();  // If there have been more than five flame
                                      // losses, wait five minutes first.
              }
              controlIgnitor(1);
          }
          // If the flame is active, continue heating
          __delay_cycles(100000);
        }
      
        // Finished heating
        state = IDLE;
        setSystemStatus(state);
        controlMainValve(500);    // Close main valve
        controlPilotValve(0);     // Close pilot valve
      }

    }
    
}

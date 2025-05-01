#include <msp430.h>
#include "SYSTEM.h"
#include "intrinsics.h"

enum systemStates{HEATING, IDLE, FLAMELOST, OVERHEAT, GREEN};
systemStates state = IDLE;

char CFH = 0;   // Holds the call for heat value
char flameTimeout = 0;  // Holds the flame timer's timeout value
int flameLosses = 0;


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    
    P1OUT &= ~BIT0;                         // Clear P1.0 output latch for a defined power-on state
    P1DIR |= BIT0;                          // Set P1.0 to output direction

    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings

    /*
    while(systemStates.HEAT)
    {
        
        startFlameTimer();
        controlIgnitor(1);                  // Turn on the ignitor
        controlPilotValve(1);               // Open the pilot valve
        Wait2Seconds();

        while(!flameTimeout)
        {
            char flame = readThermocouple();                 // Check for a flame
            if (flame==1) break;
        }

        if (flame==0)
        {
            flameLosses++;        //Add to flame loss count
            break;
        }
        



        //while(!CallForHeat() || !checkFlame() || !checkBoilerOverheat())
        while (1) 
        {
            if(!CallForHeat())
            {
                break;
            }

            if(!checkFlame())
            {
                FLAME_EXTINGUISHED = 1;
                break;
            }

            if(!checkBoilerOverheat())
            {
                OVERHEAT = 1;
                break;
            }
        }

        turnOffMainValve();
        turnOffPilotValve();
        turnOffIgnitor();


        __bis_SR_register(CPUOFF)
    }
    */

    if (state==systemStates.HEATING) //Call for heat received Heating state activated
    {
      displaySystemStatus(state); //RGB LED would change color to indicate CFH received
      controlPilotValve(1);
       
      int setpoint = potRead();

      controlMainValve(setpoint);
      displaySystemStatus(state);  //RGB LED would change color to indicate heating status
      while(thermRead() < setpoint) //While the boiler temp is less than the setpoint
      {
        if (!flameDetect()) //If flame turns off during heating
        {
            controlMainValve(500); //Turn off main valve
            controlPilotValve(0); //Close pilot valve
            flameLosses++;        //Add to flame count
            if (flameLosses > 5)
            {
                startFiveMinuteTimer();  // If there have been more than five flame
                                    // losses, wait five minutes first.
            }
            controlIgnitor(1);
        }
        // If the flame is active, continue heating
        wait(samplingTime);
      }
     
      // Finished heating
      displaySystemStatus(state);
      controlMainValve(500);
      controlPilotValve(0);
      state = systemStates.IDLE;
    }

  }


void startPilotFlame()
{
    startFiveMinuteTimer();                              //Timer for flame detection starts
    controlPilotValve(1);                            //Pilot Valve is opened
    controlIgnitor(1);           //Ignitor turns on




    while (!flameDetect())  //While no flame is detected
    {
      displaySystemStatus(state);     //RGB color changes to indicate no flame
      if (flameTimeout)     //If the timer flag which indicates the timer runs out is active
      {
        controlPilotValve(0); //Pilot valve closes
        controlIgnitor(0); //Ignitor turns off
        return; // Go back to the beginning
      }
    }
    // Flame was detected
    displaySystemStatus(state); //RGB LED indicates flame is active
    controlIgnitor(0); //Ignitor turns off
}

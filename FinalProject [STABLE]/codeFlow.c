/*
// Global Variables


int flamelosses = 0;




int main()
{
 
    // Initialize stuff
  flameInit();
  thermInit();
  initPot()
  initRGBLED();
  initPValve();
  initMainValve();
  initIgnitorLED();
  initPValve();
  initCFH();
 


  while (1)
  {
 
    if (states.HEAT) //Call for heat received Heating state activated
    {
      displaySystemStatus(cfhColor); //RGB LED would change color to indicate CFH received
      startPilotFlame()
       
         
      controlMainValve(setpoint);
      displaySystemStatus(heatingColor);  //RGB LED would change color to indicate heating status
      while(thermRead() < setpoint) //While the boiler temp is less than the setpoint
      {
        if (!flameDetect()) //If flame turns off during heating
        {
          controlMainValve(close); //Turn off main valve
            controlPValve(close); //Close pilot valve
          flameLosses++;        //Add to flame count
          if (flameLosses > 5)
            wait(fiveMinutes); // If there have been more than five flame
                                                 // losses, wait five minutes first.
          startPilotFlame();
        }
        // If the flame is active, continue heating
        wait(samplingTime);
      }
     
      // Finished heating
      displaySystemStatus(idleColor)
      controlMainValve(close);
      controlPValve(close);
      state = states.IDLE
    }
  }
}


void startPilotFlame()
{
    startFlameTimer();                              //Timer for flame detection starts
    controlPValve(open);                            //Pilot Valve is opened
    controlIgnitor(ignStates.ON);           //Ignitor turns on




    while (!flameDetect())  //While no flame is detected
    {
      displaySystemStatus(noFlameColor)     //RGB color changes to indicate no flame
      if (flameTimeout)     //If the timer flag which indicates the timer runs out is active
      {
        controlPValve(close); //Pilot valve closes
        controlIgnitor(ignStates.OFF); //Ignitor turns off
        return; // Go back to the beginning
      }
    }
    // Flame was detected
    displaySystemStatus(flameColor) //RGB LED indicates flame is active
    controlIgnitor(ignStates.OFF); //Ignitor turns off
}


// Interrupts
__interrupt void CFH(void);
__interrupt void overheat(void);
__interrupt void pilotTimeout(void);
__interrupt void samplingTime(void);
*/






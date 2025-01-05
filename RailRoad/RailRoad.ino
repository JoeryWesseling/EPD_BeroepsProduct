/*Spporwegovergang opdracht EPD
Joery Wesseling
2111633

*/

void setup() {
  serialMonitorSetup();           
  ledSetup();                     
  railroadSetup();                 
  shiftregisterControlSetup();     
  buttonStateSetup();             
  servoSetup();                    
  buttonSetup();                   
}


void loop() {
  railRoadStateMachine();
  buttonStateMachine();
}


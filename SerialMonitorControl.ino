/*
In this tab is everything to do with setting up the serial monitor. 
*/
void serialMonitorSetup(){
  Serial.begin(9600);
}


void serialMonitorLoop(){
  if(Serial.available()>0){
    char incomingByte=Serial.read();
   
    }
  }

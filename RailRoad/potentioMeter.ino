const int POT_PIN = A4; 
const int MAX_GREEN_DELAY = 5000;

void setupPotentioMeter(){
    pinMode(POT_PIN,INPUT);
}

void updateGreenDelay(){
  int potValue = analogRead(POT_PIN);
  greenDelay = map(potValue,0,1023,0,MAX_GREEN_DELAY);
}
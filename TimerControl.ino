//this tab is for timers. 
unsigned long currentMillis = 0L;
bool timerControl(unsigned long previousMillis, int INTERVAL) {
  currentMillis = millis();
  if (currentMillis - previousMillis >= INTERVAL) {
    return true;
  }
  return false;
}
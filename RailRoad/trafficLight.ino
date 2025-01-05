

// Traffic light tab

const byte northLedGreenPin = 10;
const byte northLedYellowPin = 9;
const byte northLedRedPin = 8;


const byte southLedGreenPin = 11;
const byte southLedYellowPin = 12;
const byte southLedRedPin = 13;


unsigned long ledPreviousMillis = 0L;
byte ledState = LOW;


byte getNorthLedGreenPin() {
  return northLedGreenPin;
}
byte getNorthLedYellowPin() {
  return northLedYellowPin;
}
byte getNorthLedRedPin() {
  return northLedRedPin;
}
byte getSouthLedGreenPin() {
  return southLedGreenPin;
}
byte getSouthLedYellowPin() {
  return southLedYellowPin;
}
byte getSouthLedRedPin() {
  return southLedRedPin;
}

void blinkYellow(int interval) {
  if (timerControl(ledPreviousMillis, interval)) {
    ledPreviousMillis = millis();
    digitalWrite(northLedYellowPin, ledState);
    digitalWrite(southLedYellowPin, ledState);
    ledState = !ledState;
  }
}
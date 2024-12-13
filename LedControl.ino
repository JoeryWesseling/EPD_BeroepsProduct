

const byte ledPins[] = { 13, 12, 11, 10, 9, 8 };
const byte pinLength = 6;

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

void ledSetup() {
  for (int i = 0; i < pinLength; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}
void turnLedOn(byte pinNumber) {
  digitalWrite(pinNumber, HIGH);
}
void turnLedOff(byte pinNumber) {
  digitalWrite(pinNumber, LOW);
}
void turnAllLedsOff() {
  for (int i = 0; i < pinLength; i++) {
    turnLedOff(ledPins[i]);
  }
}
void blinkYellow(int interval) {
  if (timerControl(ledPreviousMillis, interval)) {
    ledPreviousMillis = millis();
    digitalWrite(northLedYellowPin, ledState);
    digitalWrite(southLedYellowPin, ledState);
    ledState = !ledState;
  }
}

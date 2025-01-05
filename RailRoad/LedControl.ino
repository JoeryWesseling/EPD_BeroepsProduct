
/*Led setup tab*/

const byte ledPins[] = { 13, 12, 11, 10, 9, 8 };



void ledSetup() {
  for (int i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++) {
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
  for (int i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++) {
    turnLedOff(ledPins[i]);
  }
}


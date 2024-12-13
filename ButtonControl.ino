//this tab is for the button control

const byte buttonPins[] = { A0, A1, A2, A3 };
const byte buttonPinLength = 4;
const byte buttonEastPin = A1;
const byte buttonWestPin = A0;
const byte buttonSouthPin = A3;
const byte buttonNorthPin = A2;
void buttonSetup() {
  for (int i = 0; i < buttonPinLength; i++) {
    pinMode(buttonPins[i], INPUT);
  }
} 
byte getButtonEastPin() {
  return buttonEastPin;
}
byte getButtonWestPin() {
  return buttonWestPin;
}
byte getButtonSouthPin() {
  return buttonSouthPin;
}
byte getButtonNorthPin() {
  return buttonNorthPin;
}

boolean buttonHardware_Down(byte buttonPin) {
  return (digitalRead(buttonPins[buttonPin]) == LOW);
}
boolean buttonHardware_Up(byte buttonPin) {
  return !buttonHardware_Down(buttonPin);
}



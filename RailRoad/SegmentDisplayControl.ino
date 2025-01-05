const byte clockPin = 5; //clock signal pin
const byte storageRegisterClock = 6; // latch signal  (storage register clock pin)
const byte dataSerial = 7; // data input pin


// Shift register control functions
void shiftregisterControlSetup() {
  pinMode(clockPin, OUTPUT);
  pinMode(dataSerial, OUTPUT);
  pinMode(storageRegisterClock, OUTPUT);
}

void shiftregisterControlSetClockPulse() {
  digitalWrite(clockPin, HIGH);
  digitalWrite(clockPin, LOW);
}

void shiftregisterControlSetStoragePulse() {
  digitalWrite(storageRegisterClock, HIGH);
  digitalWrite(storageRegisterClock, LOW);
}

void shiftregisterControlSetdataSerial(bool status) {
  digitalWrite(dataSerial, status);
}


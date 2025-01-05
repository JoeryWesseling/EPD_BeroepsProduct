const byte amountOfSegments = 8;

// Countdown pattern for digits 5 through 0
const byte fiveCountdownPattern[] = {
 //ABCDEFG.
  B10110110, // 5
  B01100110, // 4
  B11110010, // 3
  B11011010, // 2
  B01100000, // 1
  B11111100  // 0
};

const byte emptyDisplay = B00000000;
const byte initialCountdown = 5;  // Initial countdown value

// Variables for countdown logic
unsigned long previousMillis = 0;   
const long interval = 1000;        
byte countNumber = initialCountdown;

// Function to get the display pattern for a number
byte getDisplayNumber(byte number) {
  if (number < sizeof(fiveCountdownPattern)) {
    return fiveCountdownPattern[number];
  }
  return emptyDisplay;  // Default to empty display
}

// Function to set the pattern on the 7-segment display
void setPattern(byte pattern) {
  for (byte segmentNumber = 0; segmentNumber < amountOfSegments; segmentNumber++) {
    shiftregisterControlSetdataSerial(pattern & (1 << segmentNumber));
    shiftregisterControlSetClockPulse();
  }
  shiftregisterControlSetStoragePulse();
}



// Countdown display logic
void countdownDisplay() {
  unsigned long currentMillis = millis();  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    setPattern(getDisplayNumber(countNumber));
    if (countNumber > 0) {
      countNumber--;
    } else {
      turnDisplayOff();
    }
  }
}

// Function to turn off the display
void turnDisplayOff() {
  setPattern(emptyDisplay);
}
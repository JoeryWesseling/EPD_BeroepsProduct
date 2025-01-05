// Button states
const byte buttonReleased = 1;
const byte buttonStateCheckPressed = 2;
const byte buttonPressed = 3;
const byte buttonStateCheckReleased = 4;

const byte westButtonIndex = 0;
const byte eastButtonIndex = 1;
const byte northButtonIndex = 2;
const byte southButtonIndex = 3;

byte buttonStates[] = { buttonReleased, buttonReleased, buttonReleased, buttonReleased };
bool buttonClick[] = { false, false, false, false };
unsigned long buttonPreviousMillis = 0L;
const byte amountOfButtons = 4;
const int buttonInterval = 10;

// Helper functions to get button index
byte getWestButtonIndex() { return westButtonIndex; }
byte getEastButtonIndex() { return eastButtonIndex; }
byte getNorthButtonIndex() { return northButtonIndex; }
byte getSouthButtonIndex() { return southButtonIndex; }

// Setup for button states
void buttonStateSetup() {
  for (int i = 0; i < amountOfButtons; i++) {
    buttonClick[i] = false;
    buttonStates[i] = buttonReleased;
  }
}

// Check if the button was clicked
bool checkButtonClicked(byte index) {
  if (buttonClick[index]) {
    buttonClick[index] = false;
    return true;
  }
  return false;
}

// Handle all button state changes
void buttonStateMachine() {
  for (int index = 0; index < amountOfButtons; index++) {
    byte state = buttonStates[index];

    // Check the state and handle accordingly
    switch (state) {
      case buttonReleased:
        if (buttonHardware_Down(index)) {
          buttonStates[index] = buttonStateCheckPressed;
          buttonPreviousMillis = millis();
        }
        break;

      case buttonStateCheckPressed:
        if (buttonHardware_Up(index)) {
          buttonStates[index] = buttonReleased;
        } else if (buttonHardware_Down(index) && (millis() - buttonPreviousMillis >= buttonInterval)) {
          buttonStates[index] = buttonPressed;
        }
        break;

      case buttonPressed:
        if (buttonHardware_Up(index)) {
          buttonStates[index] = buttonStateCheckReleased;
          buttonPreviousMillis = millis();
        }
        break;

      case buttonStateCheckReleased:
        if (buttonHardware_Down(index)) {
          buttonStates[index] = buttonPressed;
        } else if (buttonHardware_Up(index) && (millis() - buttonPreviousMillis >= buttonInterval)) {
          buttonStates[index] = buttonReleased;
          buttonClick[index] = true;
        }
        break;
    }
  }
}

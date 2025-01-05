void startTrafficLightTimer() {
  trafficLightPreviousMillis = millis();
}

void enterRedState() {
  Serial.println("Entering Red State");
  startTrafficLightTimer();
  turnLedOn(getNorthLedRedPin());
  turnLedOn(getSouthLedRedPin());
}
void redDo() {
  checkTrafficWest();
  checkTrafficEast();
  checkTrafficNorth();
  checkTrafficSouth();
}
void exitRedState() {
  turnAllLedsOff();
  inWaitlist = EMPTY_TRAFFIC;
}


void southGreenEntry() {
  Serial.println("South Green enter");

  inWaitlist = EMPTY_TRAFFIC;
  secondWaitList();
  startTrafficLightTimer();
  turnLedOn(getNorthLedRedPin());
  turnLedOn(getSouthLedGreenPin());
}
void southGreenDo() {
  checkTrafficNorth();
  checkTrafficWest();
  checkTrafficEast();
}
void southGreenExit() {
  turnAllLedsOff();
}


void enterYellowSouth() {
  Serial.println("South Yellow Entry");

  startTrafficLightTimer();
  turnLedOn(getNorthLedRedPin());
  turnLedOn(getSouthLedYellowPin());
}

void doYellowSouth() {
  checkTrafficNorth();
  checkTrafficWest();
  checkTrafficEast();
}

void exitYellowSouth() {
  turnAllLedsOff();
}


void enterGreenNorth() {
  Serial.println("NORTH GREEN ENTRY");

  inWaitlist = EMPTY_TRAFFIC;
  secondWaitList();
  startTrafficLightTimer();
  turnLedOn(getNorthLedGreenPin());
  turnLedOn(getSouthLedRedPin());
}
void doGreenNorth() {
  checkTrafficSouth();
  checkTrafficWest();
  checkTrafficEast();
}
void exitGreenNorth() {
  turnAllLedsOff();
}

void entryYellowNorth() {
  Serial.println("NORTH YELLOW ENTRY");
  startTrafficLightTimer();
  turnLedOn(getNorthLedYellowPin());
  turnLedOn(getSouthLedRedPin());
}

void doYellowNorth() {
  checkTrafficSouth();
  checkTrafficWest();
  checkTrafficEast();
}

void exitYellowNorth() {
  turnAllLedsOff();
}


void enterTrainComing(){
  changeUpcomingTrain();
  upcomingTrain = EMPTY_TRAFFIC;
  turnLedOn(getNorthLedRedPin());
  turnLedOn(getSouthLedRedPin());
}

void doTrainComing() {
    checkTrafficNorth();
    checkTrafficSouth();
    quickBeep();
    blinkYellow(BLINK_YELLOW_INTERVAL);
    moveServoSlowly(getPosServo() + STEP_SIZE);

}

void exitTrainComing(){
  turnAllLedsOff();
}


void enterTrainDriving() {
  turnLedOn(getNorthLedRedPin());
  turnLedOn(getSouthLedRedPin());
  Serial.println("TRAIN DRIVING ENTRY");
}

void doTrainDriving() {
  checkTrafficNorth();
  checkTrafficSouth();
  blinkYellow(BLINK_YELLOW_INTERVAL);
  
}

void exitTrainDriving() {
  turnAllLedsOff();
}

void enterTrainPassed() {
  // Serial.println("TRAIN PASSED ENTRY");
  turnLedOn(getNorthLedRedPin());
  turnLedOn(getSouthLedRedPin());
}

void doTrainPassed() {
  quickBeep();
  blinkYellow(BLINK_YELLOW_INTERVAL);
  moveServoSlowly(getPosServo() - STEP_SIZE);

}
void exitTrainPassed() {
  turnAllLedsOff();
}


void enterTrainCountdown() {
  turnLedOn(getNorthLedRedPin());
  turnLedOn(getSouthLedRedPin());
  countdownNumber = 5;
  displayPreviousMillis = millis();
  // Serial.println("TRAIN COUNTDOWN ENTRY");
}

void doTrainCountdown() {
  checkTrafficNorth();
  checkTrafficSouth();
  beepPause();
  blinkYellow(BLINK_YELLOW_INTERVAL);

  if(timerControl(displayPreviousMillis,DISPLAY_INTERVAL)){
      setPattern(getDisplayNumber(countdownNumber));
      countdownNumber-=1;
      Serial.println(countdownNumber);
      displayPreviousMillis=millis();
  }
}
void exitTrainCountdown() {
  turnAllLedsOff();
  turnDisplayOff();
}

//button clicked and no train coming? Train coming from west! 
void checkTrafficWest() {
  if (checkButtonClicked(getWestButtonIndex()) && upcomingTrain==EMPTY_TRAFFIC) {
    upcomingTrain=WEST_TRAFFIC;
    Serial.println("WEST");
  }
}

//button clicked and no train coming? Train coming from east! 
void checkTrafficEast() {
  if (checkButtonClicked(getEastButtonIndex()) && upcomingTrain==EMPTY_TRAFFIC) {
    upcomingTrain=EAST_TRAFFIC;
    Serial.println("EAST");
  }
}

void checkTrafficNorth() {
  bool buttonClicked=checkButtonClicked(getNorthButtonIndex());
  if (buttonClicked && inWaitlist == EMPTY_TRAFFIC) {
    inWaitlist = NORTH_TRAFFIC;
  }
  else if(inWaitlist==SOUTH_TRAFFIC && buttonClicked){
    inSecondWaitlist=NORTH_TRAFFIC;
  }
}

void checkTrafficSouth() {
  bool buttonClicked=checkButtonClicked(getSouthButtonIndex());
  if (buttonClicked && inWaitlist == EMPTY_TRAFFIC) {
    inWaitlist = SOUTH_TRAFFIC;
  }
  else if(inWaitlist==NORTH_TRAFFIC && buttonClicked){
    inSecondWaitlist=SOUTH_TRAFFIC;
  }
}

void secondWaitList(){
  if(inSecondWaitlist != EMPTY_TRAFFIC){
    inWaitlist=inSecondWaitlist;
    inSecondWaitlist=EMPTY_TRAFFIC;
  }
}

bool checkWaitlist(byte trafficIndex) {
  return inWaitlist == trafficIndex;
}

bool checkUpcomingTrain(byte trafficIndex){
  return upcomingTrain==trafficIndex;
}

void changeUpcomingTrain(){
  if(upcomingTrain==EAST_TRAFFIC){
    trainButtonIndex=getWestButtonIndex();
  }
  else if(upcomingTrain==WEST_TRAFFIC){
    trainButtonIndex=getEastButtonIndex();
  }
}
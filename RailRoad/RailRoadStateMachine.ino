

const byte RED_STATE = 0;
const byte STATE_SOUTH_GREEN = 1;
const byte STATE_SOUTH_YELLOW = 2;
const byte STATE_NORTH_GREEN = 3;
const byte STATE_NORTH_YELLOW = 4;
const byte STATE_TRAIN_COMING=5;
const byte STATE_TRAIN_DRIVING = 6;
const byte STATE_TRAIN_PASSED = 7;
const byte STATE_COUNTDOWN = 8;


const int GREEN_INTERVAL = 1000;
const int YELLOW_INTERVAL = 1500;
const int RED_INTERVAL = 1000;
const int BLINK_YELLOW_INTERVAL = 250;
const int DISPLAY_INTERVAL = 1000;

const byte STEP_SIZE = 1;

const byte NORTH_TRAFFIC = 1;
const byte SOUTH_TRAFFIC = 2;
const byte WEST_TRAFFIC = 3;
const byte EAST_TRAFFIC = 4;
const byte EMPTY_TRAFFIC = 5;

unsigned long displayPreviousMillis = 0L;
unsigned long trafficLightPreviousMillis = 0L;

int greenDelay = 0;

byte upcomingTrain;
byte inWaitlist;
byte inSecondWaitlist;
byte trainButtonIndex;
byte countdownNumber = 5;
byte railroadCrossingState;

void railroadSetup() {
  railroadCrossingState = RED_STATE;
  enterRedState();
  upcomingTrain = EMPTY_TRAFFIC;
  inWaitlist = EMPTY_TRAFFIC;
  inSecondWaitlist = EMPTY_TRAFFIC;
  moveServo(0);


  setupPotentioMeter();
  updateGreenDelay();


}
void railRoadStateMachine() {
  updateGreenDelay();

  switch (railroadCrossingState) {
    case STATE_SOUTH_GREEN: // 0
      southGreenDo();
      //If a train is coming add the green delay to the green interval
      if(!checkUpcomingTrain(EMPTY_TRAFFIC)){
        if(timerControl(trafficLightPreviousMillis,GREEN_INTERVAL + greenDelay)){
          southGreenExit();
          railroadCrossingState = STATE_SOUTH_YELLOW; 
          enterYellowSouth();
          Serial.print("Green Delay: ");
          Serial.println(greenDelay);
        }
        //else normal timing
      } else if(timerControl(trafficLightPreviousMillis,GREEN_INTERVAL )){
        southGreenExit();
        railroadCrossingState = STATE_SOUTH_YELLOW;
        enterYellowSouth();
        
      }

 
      /* originele situatie:
      if (!checkUpcomingTrain(EMPTY_TRAFFIC) ) {
        southGreenExit();
        railroadCrossingState = STATE_SOUTH_YELLOW;
        enterYellowSouth();
      } else if (timerControl(trafficLightPreviousMillis, GREEN_INTERVAL)) {
        southGreenExit();
        railroadCrossingState = STATE_SOUTH_YELLOW;
        enterYellowSouth();
      }*/
      break;

    case STATE_NORTH_GREEN: // 1
      doGreenNorth();
      if(!checkUpcomingTrain(EMPTY_TRAFFIC)){
        if(timerControl(trafficLightPreviousMillis,GREEN_INTERVAL + greenDelay)){
          exitGreenNorth();
          railroadCrossingState = STATE_NORTH_YELLOW;
          entryYellowNorth();
          Serial.print("Green Delay: ");
          Serial.println(greenDelay);
        }
      } else if (timerControl(trafficLightPreviousMillis,GREEN_INTERVAL)){
        exitGreenNorth();
        railroadCrossingState = STATE_NORTH_YELLOW;
         entryYellowNorth();
        
      }


      /*
      if (!checkUpcomingTrain(EMPTY_TRAFFIC)) {
        exitGreenNorth();
        railroadCrossingState = STATE_NORTH_YELLOW;
        entryYellowNorth();
      } else if (timerControl(trafficLightPreviousMillis, GREEN_INTERVAL)) {
        exitGreenNorth();
        railroadCrossingState = STATE_NORTH_YELLOW;
        entryYellowNorth();
      }*/
      break;
    case STATE_NORTH_YELLOW: // 2
      doYellowNorth();
      if (!checkUpcomingTrain(EMPTY_TRAFFIC) && timerControl(trafficLightPreviousMillis, YELLOW_INTERVAL)) {
        exitYellowNorth();
        
        railroadCrossingState = STATE_TRAIN_COMING;
        enterTrainComing();
      }  else if (timerControl(trafficLightPreviousMillis, YELLOW_INTERVAL)) {
        exitYellowNorth();
        railroadCrossingState = RED_STATE;
        enterRedState();
      }
      break;
    case STATE_SOUTH_YELLOW: // 3
      doYellowSouth();
      if (!checkUpcomingTrain(EMPTY_TRAFFIC) && timerControl(trafficLightPreviousMillis, YELLOW_INTERVAL)) {
        exitYellowSouth();
        railroadCrossingState = STATE_TRAIN_COMING;
        enterTrainComing();
      }else if (timerControl(trafficLightPreviousMillis, YELLOW_INTERVAL)) {
        exitYellowSouth();
        railroadCrossingState = RED_STATE;
        enterRedState();
      }
      break;
    case RED_STATE: // 4
      redDo();
      if (!checkUpcomingTrain(EMPTY_TRAFFIC)) {
        exitRedState();
        railroadCrossingState = STATE_TRAIN_COMING;
        enterTrainComing();
      } else if (checkWaitlist(SOUTH_TRAFFIC) && timerControl(trafficLightPreviousMillis, RED_INTERVAL)) {
        exitRedState();
        railroadCrossingState = STATE_SOUTH_GREEN;
        southGreenEntry();
      } else if (checkWaitlist(NORTH_TRAFFIC) && timerControl(trafficLightPreviousMillis, RED_INTERVAL)) {
        exitRedState();
        railroadCrossingState = STATE_NORTH_GREEN;
        enterGreenNorth();
      }
      break;
   
    case STATE_TRAIN_COMING: // 5
      doTrainComing();
      if(getPosServo() == getServoMax()){
        exitTrainComing();
        railroadCrossingState=STATE_TRAIN_DRIVING;
        enterTrainDriving();
      }
      break;
      
    case STATE_TRAIN_DRIVING: // 6
      doTrainDriving();
      if (checkButtonClicked(trainButtonIndex)) {
        exitTrainDriving();
        railroadCrossingState = STATE_TRAIN_PASSED;
        enterTrainPassed();
      }
      break;
    case STATE_TRAIN_PASSED: // 7
      doTrainPassed();
      if (getPosServo() == getServoMin()) {
        exitTrainPassed();
        railroadCrossingState = STATE_COUNTDOWN;
        enterTrainCountdown();
      }
      break;
    case STATE_COUNTDOWN: // 8
      doTrainCountdown();
      if(countdownNumber==255){
        exitTrainCountdown();
        railroadCrossingState=RED_STATE;
        enterRedState();
      }
      break;
  }
}


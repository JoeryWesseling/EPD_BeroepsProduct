//everything to do with the buzzer. 

//setting the buzzerpin
const byte buzzerPin = 4;

//setting buzzer variables and intervalls
const int quickBuzzerInt = 50;
const int psdBuzzerInt = 1000;
const int frequency = 2000;
const int duration = 250;
unsigned long buzzerPreviousMillis = 0L;

byte count;
void buzzerSetup(){
  pinMode(buzzerPin,OUTPUT);
  count = 0;
}
void quickBeep(){
  if(timerControl(buzzerPreviousMillis,quickBuzzerInt)){
    buzzerPreviousMillis=millis();
    tone(buzzerPin,frequency,duration);
  }
}

void beepPause(){
  if(timerControl(buzzerPreviousMillis,quickBuzzerInt) && count!= 3){
    count++;
    buzzerPreviousMillis = millis();
    tone(buzzerPin,frequency,duration);
  }
  if(timerControl(buzzerPreviousMillis,psdBuzzerInt) && count == 3){
    count = 0;
  }
}


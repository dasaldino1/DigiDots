#define GAMEMODE1 true
#define GAMEMODE2 false

const int buttonPin = 2; // button
const int switchPin = 14; // Mode switch
const int ledPins[11] = {3,4,5,6,7,8,9,10,11,12,13};

const int startSpeed = 200;

int winNum = 0;

bool pressed = false;
int currentLedNum = 0;
bool direction = true;
int speed = startSpeed;
bool gameMode = GAMEMODE1;

void winAnimation(){
  for (int i = 4; i < 7; i ++){
    digitalWrite(ledPins[i], HIGH);
  }
  delay(100);
  for (int i = 4; i < 7; i ++){
    digitalWrite(ledPins[i], LOW);
  }
  delay(100);
}
void loseAnimation(){
  digitalWrite(ledPins[0], HIGH);
  digitalWrite(ledPins[1], HIGH);
  digitalWrite(ledPins[9], HIGH);
  digitalWrite(ledPins[10], HIGH);
  delay(200);
  digitalWrite(ledPins[0], LOW);
  digitalWrite(ledPins[1], LOW);
  digitalWrite(ledPins[9], LOW);
  digitalWrite(ledPins[10], LOW);
  delay(200);
 
}

void configurePins() {
  for (int i = 0; i < 11; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(buttonPin, INPUT);
  pinMode(switchPin, INPUT);
}

void reset() {
  speed = startSpeed;
  direction = true;
  for (int i = 0; i < 11; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  pressed = false;

}

void buttonPressedISR (){
  pressed = true;
}

void nextLed() {
  if (direction) {
    if (currentLedNum == 10) {
      direction = false;
      currentLedNum = 9;
    }
    else currentLedNum++;
  }
  else {
    if (currentLedNum == 0) {
      direction = true;
      currentLedNum = 1;
    }
    else currentLedNum--;
  }
}

void gameMode1() {
  if (!pressed){
    nextLed();
    digitalWrite(ledPins[currentLedNum], HIGH);
    if (!direction){
      digitalWrite(ledPins[currentLedNum + 1], LOW);
    }
    else digitalWrite(ledPins[currentLedNum - 1], LOW);
    delay(speed);
  }
  else{
    if (currentLedNum == 5){
      for (int i = 0; i < 4; i++){
       winAnimation();
      }
      delay(500);
      winNum++;
      speed = speed*0.89;
      pressed = false;
    }
    else{
      loseAnimation();
      delay(500);
      reset();
      currentLedNum = -1;
      winNum = 0;
      pressed = false;
    }
  }
}
void gameMode2() {}

// Arduino main functions
void setup() {
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPressedISR, RISING);
  configurePins();
  reset();
}

void loop() {
  if (digitalRead(switchPin) != gameMode) {
    gameMode = !gameMode;
    reset();
  }

  if (gameMode == GAMEMODE1) gameMode1();
  else gameMode2();
}


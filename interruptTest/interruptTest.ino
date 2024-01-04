#define GAMEMODE1 true
#define GAMEMODE2 false

const int buttonPin = 2; // button
const int switchPin = 14; // Mode switch
const int ledPins[11] = {3,4,5,6,7,8,9,10,11,12,13};

const int startSpeed = 200;
const int speedRamp = 20;

bool ledStates[11];
bool pressed = false;
int currentLedNum = 0;
bool direction = true;
int speed = startSpeed;
bool gameMode = GAMEMODE1;

void winAnimation(){
  for (int i = 0; i < 11; i ++){
    digitalWrite(ledPins[i], HIGH);
  }
  delay(100);
  for (int i = 0; i < 11; i ++){
    digitalWrite(ledPins[i], LOW);
  }
  delay(100);
}
void loseAnimation(){
  digialWrite(ledPins[0], HIGH);

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
    ledStates[i] = false;
  }
  writeLeds();
}

void buttonPressedISR (){
  pressed = true;
}

void writeLeds() {
  for (int i = 0; i < 11; i++) {
    digitalWrite(ledPins[i], ledStates[i]);
  }
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
    digitalWrite(ledPins[currentLedNum], HIGH);
    nextLed();
    if (!direction){
      digitalWrite(ledPins[currentLedNum + 1], LOW);
    }
    else digitalWrite(ledPins[currentLedNum - 1], LOW);
  }
  else {
    if (currentLedNum == 5){

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


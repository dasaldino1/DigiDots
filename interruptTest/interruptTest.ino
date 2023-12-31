#define GAMEMODE1 true
#define GAMEMODE2 false

const int buttonPin = 2; // button
const int switchPin = 14; // Mode switch
const int ledPins[11] = {3,4,5,6,7,8,9,10,11,12,13};

const int startSpeed = 200;
const int speedRamp = 20;

bool ledStates[11];
bool ended = false;
int currentLedNum = 0;
int speed = startSpeed;
bool gameMode = GAMEMODE1;

void configurePins() {
  for (int i = 0; i < 11; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(buttonPin, INPUT);
  pinMode(switchPin, INPUT);
}

void reset() {
  speed = defaultSpeed;
  for (int i = 0; i < 11; i++) {
    ledStates[i] = false;
  }
  writeLeds();
}

void buttonPressedISR (){
  ended = true;
}

void writeLeds() {
  for (int i = 0; i < 11; i++) {
    digitalWrite(ledPins[i], ledStates[i]);
  }
}

void gameMode1() {}
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
    reset()
  }

  if (gameMode == GAMEMODE1) gameMode1();
  else gameMode2();
}


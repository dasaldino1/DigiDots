
const byte ledPin = 8; // LED
const int buttonPin = 2; // button

bool ledPins[11] = {3,4,5,6,7,8,9,10,11,12,13};

bool ended = false;

int currentLedNum = 0;

int speed = 100;

void isrTest (){
  ended = true;
}

void setup() {  
  pinMode(buttonPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin),isrTest,RISING);
  for(int i = ledPins[0]; i <= ledPins[10]; i ++){
    pinMode(i, OUTPUT);
  }
}

void loop() {
  if(!ended){
    if (currentLedNum != ledPins[0]){
      digitalWrite(currentLedNum, HIGH);
      digitalWrite(currentLedNum - 1, LOW);
      delay(speed);
      currentLedNum ++;
    }
    else {
      digitalWrite(currentLedNum, HIGH);
      digitalWrite(ledPins[10], LOW);
      delay(speed);
      currentLedNum = ledPins[0];
    }
  }
  else{
    if(currentLedNum == 5){
      digitalWrite(ledPins[0], HIGH);
      //win Animation
    }
    else{
      digitalWrite(ledPins[10],HIGH);
      //lose animation
    }
  }
}


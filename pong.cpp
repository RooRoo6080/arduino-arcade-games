const int numLeds = 9; //EDIT
const int led[numLeds] = {2, 3, 4, 5, 6, 7, 8, 9, 10}; //EDIT
const int startButton = 11; // EDIT
const int l = 13; // EDIT
const int r = 12; // EDIT
long gap = 1000; // starting time interval
bool state = false; // reading of button when pressed: HIGH = true, LOW = false
bool run = true;
bool pressed = false;
long start;

void setup() {
  for (int i = 0; i < numLeds; i++) pinMode(led[i], OUTPUT);
  pinMode(startButton, INPUT_PULLUP);
  pinMode(l, INPUT_PULLUP);
  pinMode(r, INPUT_PULLUP);
  start = millis();
}

void lWon() {
  for (int j = 0; j < 5; j++) {
    for (int i = 0; i < numLeds / 2; i++) {
    digitalWrite(led[i], HIGH);
    }
    delay(100);
    for (int i = 0; i < numLeds / 2; i++) {
      digitalWrite(led[i], LOW);
    }
    delay(100);
  }
  reset();
}

void rWon() {
  for (int j = 0; j < 5; j++) {
    for (int i = numLeds / 2; i < numLeds; i++) {
    digitalWrite(led[i], HIGH);
    }
    delay(100);
    for (int i = numLeds / 2; i < numLeds; i++) {
      digitalWrite(led[i], LOW);
    }
    delay(100);
  }
  reset();
}

void reset() {
  gap = 1000; // starting time interval
  run = false;
  pressed = false;
}

void loop() {
  outer:
  if (digitalRead(startButton) == state) run = true;
  if (run) {
    pressed = false;
    // left to right
    for (int i = 1; i < numLeds; i++) {
      digitalWrite(led[i], HIGH);
      while (millis() - start < gap ) {
        if (digitalRead(l) == state) {
          digitalWrite(led[i], LOW);
          rWon();
          goto outer;
        }
        if (i != numLeds - 1 && digitalRead(r) == state) {
          digitalWrite(led[i], LOW);
          lWon();
          goto outer;
        }
        else if (i == numLeds - 1 && digitalRead(r) == state) {
          pressed = true;
          delay(200);
          break;
        }
      }
      digitalWrite(led[i], LOW);
      start = millis();
    }
    if (!pressed) {
    	lWon();
      	goto outer;
    }
    gap -= 100; // time interval reduction every turn
    if (gap < 100) gap = 100; // time interval min value
    pressed = false;
    // right to left
    for (int i = numLeds - 2; i >= 0; i--) {
      digitalWrite(led[i], HIGH);
      while (millis() - start < gap ) {
        if (digitalRead(r) == state) {
          digitalWrite(led[i], LOW);
          lWon();
          goto outer;
        }
        if (i != 0 && digitalRead(l) == state) {
          digitalWrite(led[i], LOW);
          rWon();
          goto outer;
        }
        else if (i == 0 && digitalRead(l) == state) {
          pressed = true;
          delay(200);
          break;
        }
      }
      digitalWrite(led[i], LOW);
      start = millis();
    }
    if (!pressed) {
    	rWon();
      	goto outer;
    }
    gap -= 100; // time interval reduction every turn
    if (gap < 100) gap = 100; // time interval min value
  }
}

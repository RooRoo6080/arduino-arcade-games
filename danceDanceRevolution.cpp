const int led[9] = {2, 3, 4, 5, 6, 7, 8, 9, 10};
const int buttonPins[3] = {11, 12, 13};
long intervals[3] = {1000, 1000, 1000};
unsigned long start[] = {0, 0, 0};
bool pressed[] = {false, false, false};
bool run = true;

void setup() {
  for (int i = 0; i < 9; i++) pinMode(led[i], OUTPUT);
  for (int i = 0; i < 3; i++) pinMode(buttonPins[i], INPUT_PULLUP);
  start[0] = start[1] = start[2] = millis();
}

int drop(int r1, int r2, int r3, int index) {
  if (run) {
    int diff = millis() - start[index];
    if (diff > intervals[index] * 2 && diff < intervals[index] * 3) {
      if (digitalRead(buttonPins[index]) == LOW) {
        pressed[index] = true;
        diff = intervals[index] * 3;
      }
    } else { if (digitalRead(buttonPins[index]) == LOW) diff = intervals[index] * 3; }
  	digitalWrite(r1, HIGH);
    if (diff >= intervals[index]) {
      digitalWrite(r1, LOW);
      digitalWrite(r2, HIGH);
    }
    if (diff >= intervals[index] * 2) {
      digitalWrite(r2, LOW);
      digitalWrite(r3, HIGH);
    }
    if (diff >= intervals[index] * 3) {
      digitalWrite(r3, LOW);
      if (!pressed[index]) stop();
      start[index] = millis();
      intervals[index] -= random(10, 50);
      if (intervals[index] <= 100) intervals[index] = 100;
      pressed[index] = false;
      return random(300, 2000);
    }
  }
}

void stop() {
  run = false;
  for (int i = 0; i < 5; i++) {
    for (int i = 0; i < 9; i++) digitalWrite(led[i], HIGH);
    delay(200);
    for (int i = 0; i < 9; i++) digitalWrite(led[i], LOW);
    delay(200);
  }
  while (true) {
    if (run == false && digitalRead(buttonPins[0]) == LOW) {
      reset();
      break;
    }
  }
}

void reset() {
  intervals[0] = intervals[1] = intervals[2] = 1000;
  start[0] = start[1] = start[2] = millis();
  pressed[0] = pressed[1] = pressed[2] = false;
  run = true;
  delay(100);
}

void loop() {
  int c1, c2, c3;
  c1 = c2 = c3 = 100;
  
  if (millis() - start[0] >= c1) c1 = drop(led[0], led[3], led[6], 0);
  if (millis() - start[1] >= c2) c2 = drop(led[1], led[4], led[7], 1);
  if (millis() - start[2] >= c3) c3 = drop(led[2], led[5], led[8], 2);
}

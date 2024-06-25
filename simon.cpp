const int leds[4] = {6, 7, 8, 9};
const int buttons[4] = {2, 3, 4, 5};
const int blinkDelay = 1000;
bool play = true;

class Node {
public:
  int data;
  Node* next;

  Node(int value) {
    data = value;
    next = nullptr;
  }
};

class LinkedList {
private:
  Node* head;

public:
  LinkedList() {
    head = nullptr;
  }

  void append(int value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
      head = newNode;
    } else {
      Node* temp = head;
      while (temp->next != nullptr) {
        temp = temp->next;
      }
      temp->next = newNode;
    }
  }
  
  void reset() {
    Node* current = head;
    Node* nextNode = nullptr;
    while (current != nullptr) {
      nextNode = current->next;
      delete current;
      current = nextNode;
    }
    head = nullptr;
  }

  void display() {
    Node* temp = head;
    while (temp != nullptr) {
      digitalWrite(leds[temp->data], HIGH);
  	  delay(blinkDelay);
  	  digitalWrite(leds[temp->data], LOW);
      delay(100);
      temp = temp->next;
    }
  }
  bool check() {
    Node* temp = head;
    while (temp != nullptr) {
      int pressed = -1;
      while (pressed == -1) {
        for (int i = 0; i < 4; i++) {
          if (digitalRead(buttons[i]) == LOW) {
          	pressed = i;
            digitalWrite(leds[i], HIGH);
  	  		delay(100);
  	  		digitalWrite(leds[i], LOW);
            break;
          }
        }
      }
      if (pressed != temp->data) {
        for (int i = 0; i < 5; i++) flash();
        return false;
      }
      temp = temp->next;
    }
    return true;
  }
  void flash() {
  	for (int i = 0; i < 4; i++) digitalWrite(leds[i], HIGH);
    delay(200);
    for (int i = 0; i < 4; i++) digitalWrite(leds[i], LOW);
    delay(200);
  }
};

LinkedList list;

void setup() {
  for (int i = 0; i < 4; i++) pinMode(leds[i], OUTPUT);
  for (int i = 0; i < 4; i++) pinMode(buttons[i], INPUT_PULLUP);
}

void loop() {
  if (play) {
    list.append(random(0, 4));
  	list.display();
    play = list.check();
    list.flash();
  } else {
    if (digitalRead(buttons[0]) == LOW) {
      list.reset();
      play = true;
    }
  }
}

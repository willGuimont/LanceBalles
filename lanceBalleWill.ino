#include <Servo.h>

const int pinA1 = 8;
const int pinA2 = 7;
const int pinA3 = 3;
const int pinB1 = 9;
const int pinB2 = 10;
const int pinB3 = 6;
const int pinServo = 5;
const int buttonPin = 12;
const int ledPin = 13;
const int readyAngle = 35;
const int pushAngle = 120;

class Launcher {
public:
  Launcher(int pin1, int pin2, int pin3) : pin1(pin1), 
                                           pin2(pin2), 
                                           pin3(pin3) {};

  void forward() {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    for (int i = 0; i < 255; ++i) {
      analogWrite(pin3, i);
      delay(10);
    }
  }

  void backward() {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
  }

  void stop() {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
  }
  
private:
  int pin1;
  int pin2;
  int pin3;
};

Launcher right(pinA1, pinA2, pinA3);
Launcher left(pinB1, pinB2, pinB3);
Servo feeder;

void setup() {
  pinMode(pinA1, OUTPUT);
  pinMode(pinA2, OUTPUT);
  pinMode(pinA3, OUTPUT);
  pinMode(pinB1, OUTPUT);
  pinMode(pinB2, OUTPUT);
  pinMode(pinB3, OUTPUT);
  
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  feeder.attach(5);
  feeder.write(pushAngle);

  left.forward();
  right.forward();
}

void loop() {
  int val = digitalRead(buttonPin);
  if (val == HIGH) {
    // pressed
    digitalWrite(ledPin, LOW);
    feeder.write(readyAngle);
    delay(100);
    feeder.write(readyAngle+10);
    delay(100);
    feeder.write(readyAngle);
    delay(100);
    feeder.write(pushAngle);
    
  } else {
    // not pressed
    digitalWrite(ledPin, HIGH);
  }
}

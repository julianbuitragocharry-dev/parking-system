#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>

// Servo
Servo servo;
const int servoPin = 9;
char command;

// Bluetooth
SoftwareSerial BT(2, 3); // RX, TX

// functions declaration
void openServo();
void closeServo();

void setup() {
  servo.attach(servoPin);
  BT.begin(38400);
  closeServo();
}

void loop() {
  if(BT.available() > 0) {
    command = BT.read();
  }

  if (command == 'O') {
    openServo();
  } else if (command == 'C') {
    closeServo();
  }
}

// Servo functions
void openServo() {
  servo.write(90);
}

void closeServo() {
  servo.write(0);
}
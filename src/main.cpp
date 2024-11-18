#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <NewPing.h>

// Servo
Servo servo;
const int servoPin = 9;
char command;

// Bluetooth
SoftwareSerial BT(2, 3); // RX, TX

// Ultrasonic sensor
const int trigPin1 = 13;
const int echoPin1 = 12;
const int trigPin2 = 11;
const int echoPin2 = 10;
const int trigPin3 = 9;
const int echoPin3 = 8;
const int trigPin4 = 7;
const int echoPin4 = 6;
const int maxDistance = 200;
int distance = 0;

NewPing lotA1(trigPin1, echoPin1, maxDistance);
NewPing lotA2(trigPin2, echoPin2, maxDistance);
NewPing lotB1(trigPin3, echoPin3, maxDistance);
NewPing lotB2(trigPin4, echoPin4, maxDistance);

// functions declaration
void openServo();
void closeServo();

void setup() {
  servo.attach(servoPin);
  BT.begin(38400);
  closeServo();

  Serial.begin(9600);
}

void loop() {
  // Servo system
  if(BT.available() > 0) {
    BT.write("Command received:::");
    command = BT.read();
    BT.write(command);
  }

  if (command == 'O') {
    BT.write(command);
    openServo();
  } else if (command == 'C') {
    BT.write(command);
    closeServo();
  }

  // Ultrasonic sensor system
  distance = lotA1.ping_cm();
  if (distance < 4) {
    Serial.println(distance);
    Serial.println("Lot A1 is occupied");
    BT.println("A1a");
  } else {
    Serial.println(distance);
    Serial.println("Lot A1 is vacant");
    BT.println("A1o");
  }

  // distance = lotA1.ping_cm();
  // if (distance < 5) {
  //   Serial.println("Lot A1 is occupied");
  // } else {
  //   Serial.println("Lot A1 is vacant");
  // }

  // distance = lotA2.ping_cm();
  // if (distance < 5) {
  //   Serial.println("Lot A2 is occupied");
  // } else {
  //   Serial.println("Lot A2 is vacant");
  // }
  
  // distance = lotB1.ping_cm();
  // if (distance < 5) {
  //   Serial.println("Lot B1 is occupied");
  // } else {
  //   Serial.println("Lot B1 is vacant");
  // }
  
  // distance = lotB2.ping_cm();
  // if (distance < 5) {
  //   Serial.println("Lot B2 is occupied");
  // } else {
  //   Serial.println("Lot B2 is vacant");
  // }
}

// Servo functions
void openServo() {
  servo.write(90);
}

void closeServo() {
  servo.write(0);
}
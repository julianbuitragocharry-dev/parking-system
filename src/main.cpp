#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <NewPing.h>

// Servo
Servo servo;
const int servoPin = 5;
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
String sensorData = "";
String previousData = "";

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
    openServo();
    Serial.println("Servo opened::" + command);
    BT.println("Servo opened::" + command);
  } else if (command == 'C') {
    closeServo();
    Serial.println("Servo closed::" + command);
    BT.println("Servo closed::" + command);
  }

  // Ultrasonic sensor system
  sensorData = "";

  distance = lotA1.ping_cm();
  sensorData += (distance < 4) ? "0|" : "1|";
  
  distance = lotA2.ping_cm();
  sensorData += (distance < 4) ? "0|" : "1|";
  
  distance = lotB1.ping_cm();
  sensorData += (distance < 4) ? "0|" : "1|";
  
  distance = lotB2.ping_cm();
  sensorData += (distance < 4) ? "0" : "1";

  if (sensorData != previousData) {
    Serial.println("Data:: " + sensorData);
    BT.println(sensorData);
    previousData = sensorData;
  }

  delay(1000);
}

// Servo functions
void openServo() {
  servo.write(90);
}

void closeServo() {
  servo.write(0);
}
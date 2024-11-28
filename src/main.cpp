#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <NewPing.h>

// Matlab
String plate;

// Servo
Servo servo;
const int servoPin = 5;
char command;

// Bluetooth
SoftwareSerial BT(2, 3); // RX, TX

// Counter
const int A = A0;
const int B = A1;
const int C = A2;
const int D = A3;
const int E = A4;
const int F = A5;
const int G = 4;
const int N = 7;

int segmentPins[N] = {A, B, C, D, E, F, G};
byte digits[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};
const int OFF = HIGH;

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
void print(int digit);
int countOnes(String data);

void setup() {
  servo.attach(servoPin);
  BT.begin(38400);
  closeServo();

  Serial.begin(9600);

  for (int i = 0; i < N; i++) {
    pinMode(segmentPins[i], OUTPUT);
    digitalWrite(segmentPins[i], OFF);
  }
}

void loop() {
  // Matlab
  if (Serial.available() > 0) {
    plate = Serial.readString();
    BT.print(plate);
  }

  // Servo system
  if(BT.available() > 0) {
    command = BT.read();
  }

  if (command == 'O') {
    openServo();
  } else if (command == 'C') {
    closeServo();
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
    BT.println(sensorData);
    previousData = sensorData;

    int onesCount = countOnes(sensorData);
    print(onesCount);
  }

  delay(1000);
}

// Servo functions
void openServo() {
  servo.write(90);
}

void closeServo() {
  servo.write(170);
}

// counter functions
void print(int digit) {
  for (int i = 0; i < N; i++) {
    digitalWrite(segmentPins[i], digits[digit][i]);
  }
}

int countOnes(String data) {
  int count = 0;
  for (int i = 0; i < data.length(); i++) {
    if (data.charAt(i) == '1') {
      count++;
    }
  }

  return count;
}
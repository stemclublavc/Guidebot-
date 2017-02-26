#include <Wire.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_Sensor.h>
#include <MadgwickAHRS.h>
#include "Constants.h"
#include "Accel.h"

// GLOBAL CONSTANTS IN CONSTANTS.H
// COMPUTATIONS FOR 9-DOF SENSOR ARE IN ACCEL.H

// speed variables for left and right motors
int leftSpeedHold = 203;
int rightSpeedHold = 200;

// distance detected by ultrasonic sensor
float ultrasonicDistance;

// BEGIN FUNCTIONS

/*
Flashes the Arduino Board's LED and causes the program to wait
*/
void initialDelay()
{
  for (int i = 0; i < 5; i++) 
  {
    digitalWrite(BOARD_LED_PIN, LOW);
    delay(1000);
    digitalWrite(BOARD_LED_PIN, HIGH);
    delay(1000);
  }
}

/* note -> both curvature functions have not been modified yet,
   we need to do field testing to modify */
// allows the path of the robot to be curved left
void pathcurvatureLeft()
{
  int leftSpeedHold = 50;  // right should be higher than left
  int rightSpeedHold = 250; // left should be higher than right
}

// allows the path the robot to be curved right
void pathcurvatureRight()
{
   int leftSpeedHold = 220;  // left should be higher than right
   int rightSpeedHold = 30; // right should be higher than left
}

/*
Gets distance reading from ultrasonic sensor
*/
float getDistance() {
  float cm;

  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
  cm = pulseIn(ECHO, HIGH);

  // calculate cm and return its value
  return cm / 5.8 / 10;

  /*
  // *debug* display sensor output
  Serial.print(cm);
  Serial.println(" cm");
  delay(500);
  */

}

void setup() {
  // open serial connection
  Serial.begin(115200);
  
  // Initialize the sensors.
  // Accel.h
  initSensors();

  pinMode(BOARD_LED_PIN, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(INPUT1, OUTPUT);
  pinMode(INPUT2, OUTPUT);
  pinMode(INPUT3, OUTPUT);
  pinMode(INPUT4, OUTPUT);
  pinMode(IR_LEFT_PIN, INPUT);
  pinMode(IR_RIGHT_PIN, INPUT);
  pinMode(CAR_LED, OUTPUT);
  pinMode(IR_FRONT_PIN, INPUT);
  //pinMode(ECHO,INPUT);
  pinMode(TRIGGER, OUTPUT);

  initialDelay();
  analogWrite(ENB, leftSpeedHold);
  analogWrite(ENA, rightSpeedHold);
  digitalWrite(BOARD_LED_PIN, LOW);

}

void loop() {
  float accelHeading = getAccelHeading();
  //Serial.print("Accel heading: ");
  //Serial.println(accelHeading);
  //getMagHeading(turnNum);
  //delay(500);
  //GO_FORWARD;
  //delay(4000);
  
  

}

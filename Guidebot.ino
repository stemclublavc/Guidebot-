#include <Servo.h>
// #include <EEPROM.h> // might not actually need this b/c eeprom burns out
                       // and we should be able to use global variables for the same things

// BEGIN PIN CONSTANTS

// BUILT IN LED
const int BOARD_LED_PIN = 13;

// MOTOR CONSTANTS
const int ENA = 5; // right motor power?
const int ENB = 6; // left motor power?

const int INPUT1 = 7; // motor interface 1 (switched these names from the sample code. might be mixed up, might not)
const int INPUT2 = 8; // motor interface 2 (switched these names from the sample code. might be mixed up, might not)
const int INPUT3 = 12; // motor interface 3
const int INPUT4 = 13; // motor interface 4

// SENSOR PINS
const int ECHO = A0; // ultrasonic echo
const int TRIGGER = A1; // ultrasonic trigger

// INFARED PINS
const int IR_LEFT_PIN = A2;
const int IR_RIGHT_PIN = A3;
const int IR_FRONT_PIN = A4;

// VEHICLE LED
const int CAR_LED = 2;


// END PIN CONSTANTS

// MOVEMENT PREPROCESSOR DIRECTIVES
#define GO_BACKWARD  {digitalWrite(INPUT1,LOW);digitalWrite(INPUT2,HIGH);digitalWrite(INPUT3,LOW);digitalWrite(INPUT4,HIGH);}                              
#define GO_FORWARD {digitalWrite(INPUT1,HIGH);digitalWrite(INPUT2,LOW);digitalWrite(INPUT3,HIGH);digitalWrite(INPUT4,LOW);}
#define GO_LEFT    {digitalWrite(INPUT1,HIGH);digitalWrite(INPUT2,LOW);digitalWrite(INPUT3,LOW);digitalWrite(INPUT4,HIGH);}
#define GO_RIGHT      {digitalWrite(INPUT1,LOW);digitalWrite(INPUT2,HIGH);digitalWrite(INPUT3,HIGH);digitalWrite(INPUT4,LOW);}
#define STOP_MOTOR  {digitalWrite(INPUT1,LOW);digitalWrite(INPUT2,LOW);digitalWrite(INPUT3,LOW);digitalWrite(INPUT4,LOW);}

// RANGE OF MOTOR SPEED VALUES
const int LEFT_SPEED[11]={90,106,122,138,154,170,186,203,218,234,255}; // left
const int RIGHT_SPEED[11]={90,106,122,138,154,170,186,203,218,234,255}; // right

// BEGIN GLOBAL VARIABLES

// servos for camera assembly
Servo servo1;
Servo servo2;

byte angle1 = 70; // servo1 inital value
byte angle2 = 60; // servo2 initial value

int buffer[3]; // buffer to recieve serial data
int rec_flag; // determines whether or not Serial data is being recieved or transmitted
int serialData; // serial data
int uartCount; // not explicitly used in example code (though still declared), included just in case 

int infaredRight; // right infared status
int infaredLeft; // left infared status
int infaredFront; // front infared status

// something to do with driving modes
int cruisingFlag = 0;
int preCruisingFlag = 0;

// speed variables for left and right motors
int leftSpeedHold = 200;
int rightSpeedHold = 200;

// not explicitly used in example, included just in case
unsigned long preTime;
unsigned long nowTime;
unsigned long costTime;

// distance detected by ultrasonic sensor
float ultrasonicDistance;

// END GLOBAL VARIABLES

// BEGIN FUNCTIONS

/*
    Flashes the Arduino Board's LED and causes the program to wait
*/
void initialDelay()
{
  for(int i = 0; i < 20; i++) {
    digitalWrite(BOARD_LED_PIN, LOW);
    delay(1000);
    digitalWrite(BOARD_LED_PIN, HIGH);
    delay(1000);
  }
}

// pretty sure that's what this function does
// don't know why they called it initSteer() though...
void initCameraServos() {
  // will fill this in later when we get to something that requires a camera
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
   return cm/5.8/10;
  
  /*
  // *debug* display sensor output
  Serial.print(cm);
  Serial.println(" cm");
  delay(500);
  */
  
}

void setup() {
   pinMode(BOARD_LED_PIN,OUTPUT); 
   pinMode(ENA,OUTPUT); 
   pinMode(ENB,OUTPUT); 
   pinMode(INPUT1,OUTPUT); 
   pinMode(INPUT2,OUTPUT); 
   pinMode(INPUT3,OUTPUT); 
   pinMode(INPUT4,OUTPUT); 
   pinMode(IR_LEFT_PIN,INPUT);
   pinMode(IR_RIGHT_PIN,INPUT);
   pinMode(CAR_LED, OUTPUT);
   pinMode(IR_FRONT_PIN,INPUT);
   //pinMode(ECHO,INPUT);
   pinMode(TRIGGER,OUTPUT);
    
   initialDelay();
   analogWrite(ENB, leftSpeedHold);
   analogWrite(ENA, rightSpeedHold);
   digitalWrite(BOARD_LED_PIN, LOW);
   
   // servo1.attach(9); // commented for now because the chinese comments contradict the code
   // servo2.attach(10); // will figure out later
   
   Serial.begin(9600);
   //initCameraServos(); // in example code, is called initSteer(). doesn't seem to have anything to do with steering though 
}

void loop() {
  ultrasonicDistance = getDistance();

  /* debug movement code
  GO_FORWARD;
  delay(6000);
  GO_BACKWARD;
  delay(6000);
  GO_RIGHT;
  delay(6000);
  GO_LEFT;
  delay(6000);
  STOP_MOTOR;
  delay(6000);
  */

  // obstacle avoidance
  // to change distance in cm for obstacle avoidance (currently avoids when obstacle is closer than 15cm), change the 15.00 to something else
  // a more robust avoidance could be:
  // if obstacle detected further than 15cm,
  //    turn a direction,
  //    keep going
  if(ultrasonicDistance < 15.00) {
    // stop motor
    STOP_MOTOR;
    delay(200);
    // turn right
    GO_RIGHT;
    delay(1000);
    // go forward a bit
    GO_FORWARD;
    delay(3000);
    // turn left
    GO_LEFT;
    delay(800);// number is less because robot tends to drift
    // continue straight
    GO_FORWARD;
  } else {
    GO_FORWARD;
  }
  
}

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
const int LEFT_SPEED[11] = { 90,106,122,138,154,170,186,203,218,234,255 }; // left
const int RIGHT_SPEED[11] = { 90,106,122,138,154,170,186,203,218,234,255 }; // right

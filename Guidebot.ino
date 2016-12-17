int i = 1;
int INPUT2 = 8;//电机接口1 -- motor interface 1
int INPUT1 = 7;//电机接口2 -- motor interface 2
int INPUT3 = 12;//电机接口3 -- motor interface 3
int INPUT4 = 13;//电机接口4 -- motor interface 4

#define MOTOR_GO_BACK  {digitalWrite(INPUT1,LOW);digitalWrite(INPUT2,HIGH);digitalWrite(INPUT3,LOW);digitalWrite(INPUT4,HIGH);}    //车体前进 -- #define MOTOR_GO_BACK 
#define MOTOR_GO_RIGHT    {digitalWrite(INPUT1,LOW);digitalWrite(INPUT2,HIGH);digitalWrite(INPUT3,HIGH);digitalWrite(INPUT4,LOW);}    //车体前进 -- #define MOTOR_GO_RIGHT
#define MOTOR_GO_LEFT    {digitalWrite(INPUT1,HIGH);digitalWrite(INPUT2,LOW);digitalWrite(INPUT3,LOW);digitalWrite(INPUT4,HIGH);}    //车体前进 -- #define MOTOR_GO_LEFT
#define MOTOR_GO_STOP   {digitalWrite(INPUT1,HIGH);digitalWrite(INPUT2,HIGH);digitalWrite(INPUT3,LOW);digitalWrite(INPUT4,LOW);}    //车体前进 -- #define MOTOR_GO_STOP
#define MOTOR_GO_FORWARD   {digitalWrite(INPUT1,HIGH);digitalWrite(INPUT2,HIGH);digitalWrite(INPUT3,HIGH);digitalWrite(INPUT4,HIGH);}    //车体前进 -- #define MOTOR_GO_FORWARD
void setup()
{
 pinMode(INPUT2, OUTPUT);
 pinMode(INPUT1, OUTPUT);
 pinMode(INPUT3, OUTPUT);
 pinMode(INPUT4, OUTPUT);
}

/*int main()
{
while ( i < 10 )
        {*/
        void loop()
        {
         // MOTOR_GO_STOP;
//          //delay(40000);
        //MOTOR_GO_FORWARD;  // turn the LED on (HIGH is the voltage level) 
         // delay(8000) ;                     // wait for a second
        MOTOR_GO_FORWARD;    // turn the LED off by making the voltage LOW
         // delay(8000);                       // wait for a second
       // MOTOR_GO_STOP;
          //delay(10000);
             //if (i == 2)
                 //break;
          i++;
       }
    //   return 0;
//}

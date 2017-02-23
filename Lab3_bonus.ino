#include <Servo.h>

Servo myservo;
float cm_pos[9],cm_pos1[9]; // for cm measurement at each position of servo

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
myservo.attach(3);
}

float microsecondsToCentimeters(float microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
    return microseconds / 29.0 / 2.0;
}

float measuredistance()
{ 
  //function to return value in cm from the ultrasonic sensor
  
    float duration, inches, cm, cm1,cm2;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    pinMode(A5, OUTPUT);
    digitalWrite(A5, LOW);
    delayMicroseconds(2);
    digitalWrite(A5, HIGH);
    delayMicroseconds(5);
    digitalWrite(A5, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
    pinMode(A4, INPUT);
    duration = pulseIn(A4, HIGH);

    
   // convert the time into a distance
    cm = microsecondsToCentimeters(duration);
    cm1 = constrain(cm, 4.0,300.0); // to constraint value obtained from ultrasonic sensor from 3 to 40 cm
    cm2 = map(cm1,4.0,300.0,0.0,300.0);
    Serial.print(" ");
    Serial.print(cm2);
    Serial.print(" cm");
    Serial.println();
    delay(100);
    return cm2; // returns mapped value to be used as motor speed
}

void servo()
{ 
  const int pi=3.14;
  int pos[9]={30, 45, 60, 75, 90, 105, 120, 135, 150};

  for(int i=0;i<9; i++)
 {
   myservo.write(pos[i]);
   delay(10);
   cm_pos[i]=measuredistance();
  }
} 
void servo1()
{ 
  const int pi=3.14;
  int pos[9]={30, 45, 60, 75, 90, 105, 120, 135, 150};

  for(int i=8;i>=0; i--)
 {
   myservo.write(pos[i]);
   delay(10);
   cm_pos1[i]=measuredistance();
  }
}

void forward()
{
 int in1=6,in2=7,in3=8,in4=9,enA=5,enB=11; 

   
   float cm, speed1,speed2;
   cm=measuredistance();
   speed1=map(cm_pos[4], 0, 300, 0, 255);
      speed2=speed1+5;
   digitalWrite(in3, LOW);
   digitalWrite(in4, HIGH);
   analogWrite(enB, speed1);
   digitalWrite(in1, HIGH);
   digitalWrite(in2, LOW);
   analogWrite(enA, speed2);
   // different speeds to the motors in order to make thr robot go in straight direction
 }

void forward1()
{
 int in1=6,in2=7,in3=8,in4=9,enA=5,enB=11; 

   
   float cm, speed1,speed2;
   cm=measuredistance();
   speed1=map(cm_pos1[4], 0, 300, 0, 255);
   speed2=speed1+5;
   digitalWrite(in3, LOW);
   digitalWrite(in4, HIGH);
   analogWrite(enB, speed1);
   digitalWrite(in1, HIGH);
   digitalWrite(in2, LOW);
   analogWrite(enA, speed2);
   // different speeds to the motors in order to make thr robot go in straight direction
 }


// stop1 function to make robot stop after tracing four sides of square
void forward_left(int b, int a)
{
 int in1=6,in2=7,in3=8,in4=9,enA=5,enB=11; 

   digitalWrite(in3, LOW);
   digitalWrite(in4, HIGH);
   analogWrite(enB, b);
   digitalWrite(in1, HIGH);
   digitalWrite(in2, LOW);
   analogWrite(enA, a);
 }

void forward_right(int b, int a)
{
 int in1=6,in2=7,in3=8,in4=9,enA=5,enB=11; 

   digitalWrite(in3, LOW);
   digitalWrite(in4, HIGH);
   analogWrite(enB, b);
   digitalWrite(in1, HIGH);
   digitalWrite(in2, LOW);
   analogWrite(enA, a);
 }

// left function to move the robot left by 90 degrees
// makes right side motors to run forward at 200 speed and left side to run backward at 200 speed which results in the robot turning in left
void left()
{
 int in1=6,in2=7,in3=8,in4=9,enA=5,enB=11; 

   digitalWrite(in1, HIGH);
   digitalWrite(in2, LOW);
   analogWrite(enA, 200);
   digitalWrite(in3, HIGH);
   digitalWrite(in4, LOW);
   analogWrite(enB, 200);
   
}

void right()
{
 int in1=6,in2=7,in3=8,in4=9,enA=5,enB=11; 

   digitalWrite(in3, LOW);
   digitalWrite(in4, HIGH);
   analogWrite(enB, 180);
   digitalWrite(in1, LOW);
   digitalWrite(in2, HIGH);
   analogWrite(enA, 180);
   
}

void controller(long cm1)
{
  int x = 0, x1=0;
  unsigned long time1;
  forward();
  
  servo();
  float large=cm_pos[0];

    for( int j=0;j<9;j++)
    {
      if(cm_pos[j]>large)
      {
        large = cm_pos[j];
        x = j;
      }
    }
    switch(x1)
    {
      case 0: 
              time1 = millis();
              while(millis()<=time1+200)
              {
              right();
              Serial.print(" Right 30 ");
              Serial.println();
              }
              break;
                
     case 1: 
              time1 = millis();
              while(millis()<=time1+150)
              {
              right();
              Serial.print(" Right 45 ");
              Serial.println();
              }
              break;
      case 2: 
              time1 = millis();
              while(millis()<=time1+200)
              {
              forward_right(70, 100);
              Serial.print(" Right 60 ");
              Serial.println();
              }
              break;
      case 3: 
              time1 = millis();
              while(millis()<=time1+150)
              {
              forward_right(70,90);
              Serial.print(" Right 75 ");
              Serial.println();
              }
              break;
     case 4: 
              Serial.print(" Forward ");
              Serial.println();
              
              break;
      case 5: 
              time1 = millis();
              while(millis()<=time1+150)
              {
              forward_left(90,75);
              Serial.print(" left 75 ");
              Serial.println();
              }
              break;
      case 6: 
              time1 = millis();
              while(millis()<=time1+150)
              {
              forward_left(100,75);
              Serial.print(" Left 60 ");
              Serial.println();
              }
              break;
      case 7: 
              time1 = millis();
              while(millis()<=time1+150)
              {
              left();
              Serial.print(" Left 45 ");
              Serial.println();
              }
              break;
      case 8: 
              time1 = millis();
              while(millis()<=time1+200)
              {
              left();
              Serial.print(" Left 30 ");
              Serial.println();
              }
              break;
 
      default:
              break;        
    }
   forward1();
    servo1();
    float large1=cm_pos1[0];

    for( int j=0;j<9;j++)
    {
      if(cm_pos1[j]>large1)
      {
        large1 = cm_pos1[j];
        x1 = j;
      }
    }
    switch(x1)
    {
      case 0: 
              time1 = millis();
              while(millis()<=time1+200)
              {
              right();
              Serial.print(" Right 30 ");
              Serial.println();
              }
              break;
                
     case 1: 
              time1 = millis();
              while(millis()<=time1+150)
              {
              right();
              Serial.print(" Right 45 ");
              Serial.println();
              }
              break;
      case 2: 
              time1 = millis();
              while(millis()<=time1+200)
              {
              forward_right(70, 100);
              Serial.print(" Right 60 ");
              Serial.println();
              }
              break;
      case 3: 
              time1 = millis();
              while(millis()<=time1+150)
              {
              forward_right(70,90);
              Serial.print(" Right 75 ");
              Serial.println();
              }
              break;
     case 4: 
              Serial.print(" Forward ");
              Serial.println();
              
              break;
      case 5: 
              time1 = millis();
              while(millis()<=time1+150)
              {
              forward_left(90,75);
              Serial.print(" left 75 ");
              Serial.println();
              }
              break;
      case 6: 
              time1 = millis();
              while(millis()<=time1+150)
              {
              forward_left(100,75);
              Serial.print(" Left 60 ");
              Serial.println();
              }
              break;
      case 7: 
              time1 = millis();
              while(millis()<=time1+150)
              {
              left();
              Serial.print(" Left 45 ");
              Serial.println();
              }
              break;
      case 8: 
              time1 = millis();
              while(millis()<=time1+200)
              {
              left();
              Serial.print(" Left 30 ");
              Serial.println();
              }
              break;
 
      default:
              break;        
    }
}   

void loop() {
  // put your main code here, to run repeatedly:
  int cm1;
  cm1 = measuredistance();
  controller(cm1);
    
}

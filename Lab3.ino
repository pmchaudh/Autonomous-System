

#include <Servo.h>

Servo myservo;
int cm_pos[5]; // for cm measurement at each position of servo

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
myservo.attach(3);
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
    return microseconds / 29.0 / 2.0;
}

long measuredistance()
{ 
  //function to return value in cm from the ultrasonic sensor
  
    long duration, inches, cm, cm1,cm2;

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
  int pos[5]={0, 45, 90, 135, 180};

  for(int i=0;i<5; i++)
 {
   myservo.write(pos[i]);
   delay(1000);
   cm_pos[i]=measuredistance();
  }
}

void forward()
{
 int in1=6,in2=7,in3=8,in4=9,enA=5,enB=11; 

   digitalWrite(in3, LOW);
   digitalWrite(in4, HIGH);
   analogWrite(enB, 60);
   digitalWrite(in1, HIGH);
   digitalWrite(in2, LOW);
   analogWrite(enA, 75);
   // different speeds to the motors in order to make thr robot go in straight direction
}

// stop1 function to make robot stop after tracing four sides of square
void reverse()
{
 int in1=6,in2=7,in3=8,in4=9,enA=5,enB=11; 

   digitalWrite(in3, HIGH);
   digitalWrite(in4, LOW);
   analogWrite(enB, 150);
   digitalWrite(in1, LOW);
   digitalWrite(in2, HIGH);
   analogWrite(enA, 150);
 }

void stop1()
{
 int in1=6,in2=7,in3=8,in4=9,enA=5,enB=11; 

   digitalWrite(in3, LOW);
   digitalWrite(in4, HIGH);
   analogWrite(enB, 0);
   digitalWrite(in1, HIGH);
   digitalWrite(in2, LOW);
   analogWrite(enA, 0);
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
  int x = 0;
  unsigned long time1;
  
  if(cm1>5.0)
  { forward();
    Serial.print(" forward ");
    Serial.println();
  }
  else if( cm1<=5.0)
  {
    reverse();
    Serial.print(" reverse ");
    Serial.println();
    delay(400);
    stop1();
    Serial.print(" stop ");
    Serial.println();
    delay(500);
    servo();
    Serial.print(" SERVO SEARCHING ");
    Serial.println();
    int large=cm_pos[0];

    for( int j=1;j<5;j++)
    {
      if(cm_pos[j]>large)
      {
        large = cm_pos[j];
        x = j;
      }
    }
    switch(x)
    {
      case 0: 
              time1 = millis();
              while(millis()<=time1+300)
              {
              right();
              Serial.print(" Right 90 ");
              Serial.println();
              }
              myservo.write(90);
              break;
      case 1: 
              time1 = millis();
              while(millis()<=time1+150)
              {
              right();
              Serial.print(" Right 45 ");
              Serial.println();
              }
              myservo.write(90);
              break;
      case 2: 
              break;        
      case 3: 
              time1 = millis();
              while(millis()<=time1+150)
              {
              left();
              Serial.print(" Left 45 ");
              Serial.println();
              }
              myservo.write(90);
              break;
      case 4: 
              time1 = millis();
              while(millis()<=time1+300)
              {
              left();
              Serial.print(" Left 90 ");
              Serial.println();
              }
              myservo.write(90);
              break; 
      default:
              break;        
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int cm1;
  cm1 = measuredistance();
  controller(cm1);
    
}

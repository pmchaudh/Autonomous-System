void setup() {
  Serial.begin(9600); // Setup Serial port for debugging
}

// forward function to drive the robot forward
// makes both sides of motors to run in forward direction
void forward()
{
 int in1=6,in2=7,in3=8,in4=9,enA=5,enB=11; 

   digitalWrite(in3, LOW);
   digitalWrite(in4, HIGH);
   analogWrite(enB, 100);
   digitalWrite(in1, HIGH);
   digitalWrite(in2, LOW);
   analogWrite(enA, 115);
   // different speeds to the motors in order to make thr robot go in straight direction
}

// stop1 function to make robot stop after tracing four sides of square
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

// function returns modulo function value in order to establish a repeating timer
double timer()
{  unsigned long time1;
   double time2;
   time1 = millis();
   time2 = time1 % 2610;

   // remainder of millis function is found when divided by 2610 as I wanted motion function to repeat after each 2610 milliseconds interval
 
   Serial.print(" Timer : ");
   Serial.print(time2);
   return time2;
}

// function that calls forward or left functions based on the value returned by timer function
// conditions inside the function motion keep on repeating after 2610ms time interval i.e going straight for 1m and turning left in order to complete four sides of a square and finally stopping
void motion(double time2) 
{
  if( time2<=2300) // 2300ms required to travel 1m 
   {
    forward();
    Serial.println(" Forward ");
    }
   else if( time2>2300 && time2<2610) // 310 ms required to make left turn
   {
    left();
    Serial.println(" Left ");
   }
 }

void loop()
{
   double time2; // variable to store repeating timer value
   time2 =timer();
   motion(time2);// timer value fed to motion function which calls forward or left function based on timer value 

   // to stop the robot after tracing 4 sides of the square and returing to original position
   
   if(millis() >= 10440) // 4 multiplied by 2610 ms
   {
   Serial.println(" Stop ");
   stop1();
   }
}

// DRAWBACKS OF USING TIMING BASED APPROACH
// 1. No sensor feedback in order to determine whether we are going on the correct path.
// 2. No method to correct faults in the robot such as misaligned wheels which results in robot going in a curvy path instead of straight line.
// 3. If initial position is not same every time, the robot may go to different directions each time instead of going on desired path.
// 4. Trial and Error method used which takes a lot of time to perfect as it is a matter of milliseconds.
// 5. As there is no feedback involved, the controller doesn't know whether the processes are being executed correctly.
// 6. Robot fails to perform the tasks in similar manner when its environment is changed. eg.: robot was running in different manners on tiles and on carpet.

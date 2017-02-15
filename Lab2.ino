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
   analogWrite(enA, 110); 
   // different speeds to the motors in order to make thr robot go in straight direction
}

// right function to move the robot right by 90 degrees
// makes left side motors to run forward at 180 speed and right side to run backward at 180 speed which results in the robot turning in right direction
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

// function returns modulo function value in order to establish a repeating timer
double timer()
{  unsigned long time1;
   double time2;
   time1 = millis();
   time2 = time1 % 1550; 
   
   // remainder of millis function is found when divided by 1550 as I wanted motion function to repeat after each 1550 milliseconds interval
   
   Serial.print(" Timer : ");
   Serial.print(time2);
   return time2;
}

// function that calls forward or right functions based on the value returned by timer function
// conditions inside the function motion keep on repeating after 1550ms time interval i.e going straight for 0.5m and turning right in order to complete four sides of a square and keeps on drawing the square
void motion(double time2) 
{
   if( time2<=1200)// 1200ms time required to travel 0.5m
   {
    forward();
    Serial.println(" Forward ");
    }
   else if( time2>1200 && time2<1550)// 350ms required to make right turn
   {
    right();
    Serial.println(" Right ");
   }
}

void loop()
{
   double time2; // variable to store repeating timer value
   time2 =timer();
   motion(time2); // timer value fed to motion function which calls forward or right function based on timer value 
  
}

// DRAWBACKS OF USING TIMING BASED APPROACH
// 1. No sensor feedback in order to determine whether we are going on the correct path.
// 2. No method to correct faults in the robot such as misaligned wheels which results in robot going in a curvy path instead of straight line.
// 3. If initial position is not same every time, the robot may go to different directions each time instead of going on desired path.
// 4. Trial and Error method used which takes a lot of time to perfect as it is a matter of milliseconds.
// 5. As there is no feedback involved, the controller doesn't know whether the processes are being executed correctly.
// 6. Robot fails to perform the tasks in similar manner when its environment is changed. eg.: robot was running in different manners on tiles and on carpet.

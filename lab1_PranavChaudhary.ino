
// variables to be used in loop function
  long cm4; // used to store value returned by measuredistance function
  double val4; // used to store value returned by cal_sine function

void setup() {
  // initialize serial communication:
   
    Serial.begin(9600);
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
    Serial.print(" ");
    Serial.print(cm);
    Serial.print(" cm");
    Serial.println();
    delay(100);
    
    cm1=constrain(cm, 3,40); // to constraint value obtained from ultrasonic sensor from 0 to 30 cm
    cm2=map(cm1,3,40,0,255); // Used for converting 0 to 30 range to 0 to 255 which is used for motor speed
    
    return cm2; // returns mapped value to be used as motor speed
}

double cal_sine()
{  
   // function to calculate value of sin(2*pi*f*t) and return the same
    
    const float pi=3.14;
    double val,val1,val2;
    
    val = 100*sin(2*pi*0.2*millis()/1000); // here val is between -100 to 100; frequency is 0.2 hz
    val1 = constrain(val, -100,100); // constraint is used to limit val from -100 to 100. however, it doesnt go out of those limits.
    
    return val1; // returns value of 100*sin(2*pi*f*t) which is from -100 to 100
  }

 void update_motor( double val2, long motB_Speed)
 { 
  //function for running the two motors run in the desired manner 
  
    double motA_Speed;
    int in1=6,in2=7,in3=8,in4=9,enA=5,enB=11;
  
    Serial.print("  motor a ");
    Serial.print(val2);
  
  // For motor following sine pattern
  
//    if(val2>=0) // used when calculated sine is +ve i.e from 0 to 100
//    { 
//      motA_Speed = map(val2,0,100,0,255); // maps 0 to 100 range to 0 to 255 which is used below as motor A speed
//    
//      digitalWrite(in1, HIGH);
//      digitalWrite(in2, LOW);
//      analogWrite(enA, motA_Speed);
//    
//      Serial.print("  +ve sine  ");
//      Serial.print(motA_Speed);
//    }
//  
//    else // used when calculated sine value is from -100 to 0 
//    { 
//      val2 = abs(val2); // taking absolute of the -ve value to get +ve value
//      motA_Speed = map(val2,0,100,0,255); // +ve value obtained above is mapped to 0 to 255 range to be used as motor speed.
//    
//      digitalWrite(in1, LOW); // pins in1 and in2 are opposite than from the if statement above in order to get reverse motion 
//      digitalWrite(in2, HIGH);
//      analogWrite(enA, motA_Speed);
//    
//      Serial.print("  -ve loop sine ");
//      Serial.print(motA_Speed);  
//    }
//    
   // For motor B following Ultrasonic sensor
    
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      analogWrite(enB, motB_Speed);
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(enA, motB_Speed);
      Serial.print(" motB_Speed ");
      Serial.print(motB_Speed);
 
 }


 void loop() 
  {
      cm4 = measuredistance();
      
      val4= cal_sine();
      
      update_motor(val4 , cm4);
  }

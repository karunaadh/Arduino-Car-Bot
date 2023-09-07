/* This program has both motors turn clockwise when
the designated buttons (left button = top motor, right button = bottom motor)
aren't pressed, and turn counterclockwise for 2 seconds when they are pressed). 
*/

//------------------------------variables and constants-----------
//--------------Motor------------
//Top motor
const int motorPin1  = 9;  // input 1
const int motorPin2  = 10;  // input 2
//Bottom motor
const int motorPin3  = 6; // input 3
const int motorPin4  = 5;  // input 4

//----------------Sensor-------------
const int echoPin = 2;
const int trigPin = 3;

//----------------------------------------------------------------------

//-----------------------------------Setup---------------------------
//This will run only one time.
void setup(){
  
  	//Set motor pins as outputs
    pinMode(motorPin1, OUTPUT); //top
    pinMode(motorPin2, OUTPUT); //top
    pinMode(motorPin3, OUTPUT); //bottom
    pinMode(motorPin4, OUTPUT); //bottom
  
    //USS Pins
  	pinMode(trigPin, OUTPUT);
  	pinMode(echoPin, INPUT);
  
  	// initialize serial communication:
  	Serial.begin(9600);
  
}
//-----------------------------------------------------

//-------------------------Loop--------------------------
//This code runs until the program is stopped
void loop(){
  
  //------------------photoresistor------------------
  // reads the input on analog pin A0
  int analogValue = analogRead(A0);
  
  // print out reading
  Serial.print("Analog reading = ");
  Serial.println(analogValue);   // the raw analog reading
  
  //---------------------------------------------------
  
  //--------------------------------------------------
   
  //variables for duration and distance of signal
  long duration, inches, cm;
  
  //trigger ping (high pulse for 5+ microseconds
  digitalWrite(trigPin, LOW);
  delay (0.002);
  digitalWrite(trigPin, HIGH);
  delay(0.005);
  digitalWrite(trigPin, LOW);
  
  //duration of time from sending signal to recieving echoed signal
  duration = pulseIn(echoPin, HIGH);
  
  //convert duration to inch and cm
  inches = duration / 74 / 2;
  cm = duration / 29 / 2;

  //Print out distance
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
    
  //Stop when shade is found
  if (analogValue < 350){
    digitalWrite(motorPin3, LOW); //bottom
    digitalWrite(motorPin4, LOW); //bottom
    digitalWrite(motorPin1, LOW); //top
    digitalWrite(motorPin2, LOW); //top
    
  //if it's not shady...
  } else {
    //if the distance from the sensor to the object is less than 4
    if (cm < 8){    
      //keep turning right
      digitalWrite(motorPin3, LOW); //bottom
      digitalWrite(motorPin4, LOW); //bottom
      digitalWrite(motorPin1, LOW); //top
      digitalWrite(motorPin2, HIGH); //top 
      delay (500);   
    }
    //if it's not shady and cm is no longer < 6 (meaning no longer is the robot colliding with something)
      //----------Move forward------------
      digitalWrite(motorPin3, LOW); //bottom
      digitalWrite(motorPin4, HIGH); //bottom
      digitalWrite(motorPin1, LOW); //top
      digitalWrite(motorPin2, HIGH); //top 
  }
  
  //----------------------------------------------------------
  
}


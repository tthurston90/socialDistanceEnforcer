const int pingPin = 7; 
const int redPin = 6;
const int bluePin = 5;
const int greenPin = 3;
const int switchPin = 2;
const int alarmPin = 4;

void setup()
{
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(switchPin, INPUT);
  pinMode(alarmPin, OUTPUT);
}

void loop(){
   // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:
  long duration, feet, cm;
  int enable = digitalRead(switchPin);
  
  if (enable){
  	// The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  	// Give a short LOW pulse beforehand to ensure a clean HIGH pulse: 	
  	pinMode(pingPin, OUTPUT);
  	digitalWrite(pingPin, LOW);
  	delayMicroseconds(5);
  	digitalWrite(pingPin, HIGH);
  	delayMicroseconds(10);
  	digitalWrite(pingPin, LOW);
  
  	// The same pin is used to read the signal from the PING))): a HIGH pulse
  	// whose duration is the time (in microseconds) from the sending of the ping
  	// to the reception of its echo off of an object.
  	pinMode(pingPin, INPUT);
  	duration = pulseIn(pingPin, HIGH);
    
  	// convert the time into a distance
  	cm = microsecondsToCentimeters(duration);
  	feet = cm / 30.48; 
  
  	if (feet >= 6){
    	digitalWrite(greenPin, HIGH);
    	digitalWrite(redPin, LOW);
    	digitalWrite(bluePin, LOW);
  	}
  
  	else if (feet <= 4){
    	digitalWrite(greenPin, LOW);
    	digitalWrite(redPin, HIGH);
    	digitalWrite(bluePin, LOW);
  	}
  
  	else if (feet < 6 && feet > 4){
    	digitalWrite(greenPin, LOW);
    	digitalWrite(redPin, LOW);
    	digitalWrite(bluePin, HIGH);
  	} 

  	if ( feet < 6){
    	digitalWrite(alarmPin, LOW);
    	delay(100);
  	}
  	else {
  		digitalWrite(alarmPin, HIGH);
    	delay(100);
  	}
  
  	Serial.print(feet);
  	Serial.println("ft");
  	delay(100);
  }
  else{
    digitalWrite(greenPin, LOW);
    digitalWrite(redPin, LOW);
    digitalWrite(bluePin, LOW);
    digitalWrite(alarmPin, HIGH);
  }
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
 
  
  
  
  
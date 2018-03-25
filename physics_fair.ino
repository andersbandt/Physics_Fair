//Physics Fair Project 2018
#include <Servo.h>
#include <CapacitiveSensor.h>

const int reset = 2;
const int indicator = 13;
const int pingPin = 5;
const int trigPin = 6;
const int recPin = 7;
const int rel_hov = 3;
const int rel_vib = 1;
int resetState = 0;
int ballState = 0;
Servo servo1;
Servo servo2;
Servo servo3;
boolean runHovercraft = true;


// the setup routine runs once when you press reset:
void setup() {
  servo1.attach(9);
  servo2.attach(10);
  servo3.attach(12);
  pinMode(indicator,OUTPUT);
  pinMode(rel_vib, OUTPUT);
  pinMode(reset,INPUT);
  pinMode(rel_hov, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  long duration1, duration2, cm1, cm2;
  pinMode(pingPin, OUTPUT); //code for the ball ping sensor pulse
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW); //end of pulse from ball ping sensor
  
  pinMode(pingPin, INPUT);  //code for the duration of the signal 
  duration1 = pulseIn(pingPin, HIGH);
  
  pinMode(trigPin, OUTPUT); //code for the start of the project ping sensor pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW); //end of pulse from start of the project ping sensor
  
  pinMode(recPin, INPUT);  //code for the duration of the signal 
  duration2 = pulseIn(recPin, HIGH);
  
  cm1 = microsecondsToCentimeters(duration1); //final ball ping sensor value in centimeters
  cm2 = microsecondsToCentimeters(duration2); //start of the project sensor final value in centimeters
	
	
	
	resetState = digitalRead(reset); //gets the value of the reset switch
	if (resetState == HIGH) {
    servo1.write(0);
    servo2.write(180);
    digitalWrite(indicator,HIGH);
  }
  else {
  	digitalWrite(indicator,LOW);
  	servo1.write(90);
  	servo2.write(90);
  }
  
  if ((cm1 > 10) && (runHovercraft)) {
  	//pullBack();
  	//cm1 = 0;
  }
  

delay(100);
	
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

void pullBack() {
	servo1.write(180);
	servo2.write(0);
	delay(7000);
	servo1.write(90);
	servo2.write(90);
	runHovercraft = false;
}

void startProj() {
	servo3.write(40);
}

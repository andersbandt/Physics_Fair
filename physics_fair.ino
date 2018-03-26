#include <Servo.h>
#include <CapacitiveSensor.h>

const int reset = 2;
const int prop_car = 11;
const int indicator = 13;
const int pingPin = 5;
const int trigPin = 6;
const int recPin = 7;
const int rel_hov = 3;
const int rel_vib = 4;
int resetState = 0;
int ballState = 0;
int prop_carState = 0;
int time = 0;
Servo servo1;
Servo servo2;
Servo servo3;
boolean runHovercraft = true;
boolean startProject = true;
boolean tenSeconds = false;


// the setup routine runs once when you press reset:
void setup() {
  servo1.attach(9);
  servo2.attach(10);
  //servo3.attach(12);
  pinMode(indicator,OUTPUT);
  pinMode(rel_vib, OUTPUT);
  pinMode(reset,INPUT);
  pinMode(prop_car,INPUT);
  pinMode(rel_hov, OUTPUT);
  Serial.begin(9600);
  //servo3.write(180);
  digitalWrite(rel_hov,HIGH);
  digitalWrite(rel_vib,HIGH);
}

void loop() {
  long duration1, duration2, cm1, cm2;
  time = millis();
  if (time = 15000) {
  	tenSeconds = true;
  }
	
//DISTANCE SENSOR SHIT	
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
	
//RESET BUTTON FOR BLOCK OF WOOD	
	resetState = digitalRead(reset); //gets the value of the reset switch
	if (resetState == HIGH) {
    servo1.write(0);
    servo2.write(180);
    servo3.write(180);
  }
  else {
  	servo1.write(90);
  	servo2.write(90);
  }
//MARBLE TO PAPER IF STATEMENT  
  if ((cm1 > 10) && (runHovercraft)) {
  	pullBack();
  }
  
  if ((cm2 < 2) && (startProject) && (tenSeconds)) {
  	startProj();
  }
	
 prop_carState = digitalRead(prop_car);

  if (prop_carState == 0) {
	  digitalWrite(rel_vib,LOW);
	  delay(2000);
	  digitalWrite(rel_vib,HIGH);
  }
  
delay(75);
}

long microsecondsToCentimeters(long microseconds) { //method for converting pulse into centimeters
  return microseconds / 29 / 2;
}

void pullBack() { //method that pulls the block back to release the hovercraft
	digitalWrite(rel_hov,LOW);
	delay(500);
	servo1.write(180);
	servo2.write(0);
	delay(4300);
	digitalWrite(rel_vib,LOW);
	servo1.write(90);
	servo2.write(90);
	delay(3000);
	digitalWrite(rel_vib,HIGH);
	digitalWrite(rel_hov,HIGH);
	runHovercraft = false;
	
}

void startProj() { //method to tip down the marble at the top of the project
	servo3.attach(12);
	servo3.write(145);
	delay(1000);
	startProject = false;
	digitalWrite(indicator,HIGH);
}

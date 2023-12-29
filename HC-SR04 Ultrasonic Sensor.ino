// Hook up HC-SR04 with Trig to Arduino pin 2, Echo to Arduino pin 10
#define trigPin 2
#define echoPin 10

#include <LiquidCrystal.h>
#include <Wire.h>

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7, BL = 10;

LiquidCrystal lcd_1 (rs, en, d4, d5, d6, d7);

int ena = 3;
int in1 = A0; // right motor
int in2 = A1; // right motor
int in3 = A2; // left motor
int in4 = A3; // left motor
int enb = 11;
int ls = 12; // left IR sensor
int r = 13; // right IR sensor
int duration;
int distance;

void setup() {

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
	Serial.begin(9600);

}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  
  if ((digitalRead(ls)==LOW)&&digitalRead(r)==LOW){
    forward();
  }
  if ((digitalRead(ls)==HIGH)&&digitalRead(r)==LOW){
    turnLeft();
  }
  if ((digitalRead(ls)==LOW)&&digitalRead(r)==HIGH){
    turnRight();
  }
  if ((digitalRead(ls)==HIGH)&&digitalRead(r)==HIGH){
    stop(); 
  }

  if(distance<10){
    stop();
  }
}

void forward (){
  analogWrite(ena,95); 
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(enb,130);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}

void turnLeft (){
  analogWrite(ena,210);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(enb,130);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

void turnRight (){
  analogWrite(ena,155);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  analogWrite(enb,235);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}

void stop (){
  analogWrite(ena,0);
  analogWrite(enb,0);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}

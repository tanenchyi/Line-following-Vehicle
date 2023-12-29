#include <LiquidCrystal.h>

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7, BL = 10;

LiquidCrystal lcd (rs, en, d4, d5, d6, d7);

int ena = 3;
int in1 = A0; // right motor
int in2 = A1; // right motor
int in3 = A2; // left motor
int in4 = A3; // left motor
int enb = 11;
int buzzer = 12;
int trigPin = 10;
int echoPin = 13;
int duration;
int distance;
float time = millis()/1000;
const int BTState = 2;
int state;

void setup()
{
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(BTState, INPUT);
  Serial.begin(9600);
  lcd.begin(16,2);
}

void loop()
{
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
  Serial.print("Distance: ");
  Serial.println(distance);
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("Distance:");
  lcd.print(distance);
  
  if (state == 'F'){forward();}
  if (state == 'L'){turnLeft();}
  if (state == 'R'){turnRight();}
  if (state == 'B'){backward();}
  if (state == 'S'){stop();}
  if (distance<=20){
    digitalWrite(buzzer,HIGH);
  }else digitalWrite(buzzer,LOW);
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
  analogWrite(ena,180);
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

void backward (){
  analogWrite(ena,80); 
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  analogWrite(enb,115);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

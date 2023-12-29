#include <LiquidCrystal.h>
#include <Wire.h>

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7, BL = 10;

LiquidCrystal lcd_1 (rs, en, d4, d5, d6, d7);

int in1 = A0; // right motor
int in2 = A1; // right motor
int in3 = A2; // left motor
int in4 = A3; // left motor
int ena = 3;
int enb = 11;
int ls = 12; // left IR sensor
int r = 13; // right IR sensor
int lre = 10; // left rotary encoder
int rre = 2; // right rotary encoder
int diskslots = 40;
int counter1 = 0;
int counter2 = 0;
int initial1 = 0;
int initial2 = 0;
float distance = 0.0;
float distance1 = 0.0;
float distance2 = 0.0;
float circumference = 6.7*3.142;

void setup() {

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(ls, INPUT);
  pinMode(r, INPUT);
  pinMode(lre, INPUT);
  pinMode(rre, INPUT);
  int initial1 = digitalRead(lre);
  int initial2 = digitalRead(rre);
  lcd_1.begin(16, 2); 

}

void loop() {

  if (digitalRead(ls)==LOW && digitalRead(r)==LOW){
    forward();
    count1();
  }
  if (digitalRead(ls)==HIGH && digitalRead(r)==LOW){
    turnLeft();
    count1();
  }
  if (digitalRead(ls)==LOW && digitalRead(r)==HIGH){
    turnRight();
    count1();
  }
  if (digitalRead(ls)==HIGH && digitalRead(r)==HIGH){
    stop(); 
  }

  distance1=counter1/diskslots*circumference/100;
  distance2=counter2/diskslots*circumference/100;
  float average=(distance1+distance2)/2;
  lcd_1.setCursor(0, 0);
  lcd_1.print("l:");lcd_1.print(distance1,2);
  lcd_1.print("r:");lcd_1.print(distance2,2);
  lcd_1.setCursor(0, 1);
  lcd_1.print("distance:");lcd_1.print(distance,2);

}

void count1(){
  int final1 = digitalRead(lre);
  if (final1 != initial1){
    counter1 ++;
    initial1 = final1;
  }
}

void count2(){
  int final2 = digitalRead(rre);
  if (final2 != initial2){
    counter2 ++;
    initial2 = final2;
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

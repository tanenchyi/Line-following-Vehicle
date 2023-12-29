#include <Wire.h>
#include <MPU6050_light.h> // library for MPU6050 communication
#include <LiquidCrystal.h> // library for LCD display

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7, BL = 10;

LiquidCrystal lcd_1 (rs, en, d4, d5, d6, d7);
MPU6050 mpu (Wire);


int in1 = A0; // right motor
int in2 = A1; // right motor
int in3 = A2; // left motor
int in4 = A3; // left motor
int ena = 3;
int enb = 11;
int ls = 12; // left IR sensor
int r = 13; // right IR sensor
int lre = 10; // left rotary encoder
int diskslots = 40;
int counter1 = 0;
int counter2 = 0;
int initial1 = 0;
int initial2 = 0;
float distance = 0.0;
float distance1 = 0.0;
float distance2 = 0.0;
float circumference = 6.7*3.142;
int N;
int M;
int currentTime = 0;
float time;
    
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
  int initial1 = digitalRead(lre);
  lcd_1.begin(16, 2); 

  Serial.begin(9600);
  Wire.begin();
  mpu.begin();
  mpu.calcGyroOffsets(); // calibrate gyroscope

}

void loop() {
  time = millis()/1000;
  mpu.update(); // get values from MPU6050
  Serial.println(int(mpu.getAngleX()));
  printDistance();

  if (time<4){
    if (time < 3) {
      printAngle();
    }
    forward(160,205);
    count1();  
  }

  if (time>=4 && time<9){
    stop();
  }

  if (time>=9 && time<10.0005){
    turnRight(200,235);
    count1();
  }

  if (time>=10.0005 && time <12){
    stop();
  }

  if (time>=12 && time<14.15) {
      forward(80,115);
      count1();
    if (digitalRead(ls)==HIGH && digitalRead(r)==LOW){
      turnLeft(210,130);
      count1();
    }
    if (digitalRead(ls)==LOW && digitalRead(r)==HIGH){
      turnRight(155,235);
      count1();
    }
  }

  if (time>=14.15){
    if (distance2>=170 && currentTime==0){
       currentTime=time;
    }
    if ((time-currentTime)<=2){
      stop();
    } else{
      if (digitalRead(ls)==LOW && digitalRead(r)==LOW){
        forward(75,110);
        count2();
      }
      if (digitalRead(ls)==HIGH && digitalRead(r)==LOW){
        turnLeft(210,130);
        count2();
      }
      if (digitalRead(ls)==LOW && digitalRead(r)==HIGH){
        turnRight(180,235);
        count2();
      }
      if (digitalRead(ls)==HIGH && digitalRead(r)==HIGH){
        stop(); 
      }
    }
  }
}

void count1(){
  int final1 = digitalRead(lre);
  if (final1 != initial1){
    counter1 ++;
    initial1 = final1;
  }
}

void count2(){
  int final2 = digitalRead(lre);
  if (final2 != initial2){
    counter2 ++;
    initial2 = final2;
  }
}

void printAngle(){
  lcd_1.setCursor(0, 0);
  lcd_1.print("Angle= ");
  if(int(mpu.getAngleX())<10 && int(mpu.getAngleX())>0) lcd_1.print("0");
  lcd_1.print(int(mpu.getAngleX()));
  Serial.println(int(mpu.getAngleX()));
}

void printDistance(){
  distance1=counter1/diskslots*circumference;
  distance2=counter2/diskslots*circumference;
  distance=distance1+distance2;
  lcd_1.setCursor(0, 1);
  lcd_1.print("distance:");lcd_1.print(distance2,1);
}

void forward (int N,int M){
  analogWrite(ena,N); 
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(enb,M);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}

void turnLeft (int N, int M){
  analogWrite(ena,N);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(enb,M);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

void turnRight (int N, int M){
  analogWrite(ena,N);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  analogWrite(enb,M);
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

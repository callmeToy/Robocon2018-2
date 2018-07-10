#include "Omni.h"
#include "motor_old.h"
#include <Wire.h>

#define averageSize 50


#define M1pinA   2
#define M1pinB   4
#define M1pinPWM 3
#define M2pinA   6
#define M2pinB   5
#define M2pinPWM 9
#define M3pinA   12
#define M3pinB   A0
#define M3pinPWM 11
#define M4pinA   8
#define M4pinB   7
#define M4pinPWM 10

const int i2cAddress = 1;
const int CEASETIME_MS = 500;

int slowSpeed = 255/100;
int maxSpeed = 240/7;

int speed_ = slowSpeed;
int frontAngle = 90;

int leftHatX, leftHatY, rightHatX;
bool cross, start;

bool flag;
unsigned long CeaseCounter;

Omni omniFR(45, averageSize), omniFL(135, averageSize);
Omni omniBL(225, averageSize), omniBR(315, averageSize);	//(angle)
motor motorFR(M1pinA, M1pinB, M1pinPWM), motorFL(M2pinA, M2pinB, M2pinPWM); 
motor motorBL(M3pinA, M3pinB, M3pinPWM), motorBR(M4pinA, M4pinB, M4pinPWM);

void setup() {
  delay(2000);
  Serial.begin(115200);
  Wire.begin(i2cAddress);
  Wire.onReceive(receiveEvent);
}

void loop() {
  //stopAll();
  speedSet(cross);
  frontAngleSet(start);
  omniWheelDrive(leftHatX, leftHatY, rightHatX);
  show();
}

void stopAll() {
  if (flag == 0) {
    if ((millis() - CeaseCounter) > CEASETIME_MS) {
      leftHatX = leftHatY = rightHatX = 0;
    }
  } else {
    CeaseCounter = millis();
    flag = false;
  }
}

void speedSet(bool cross) {

  if (cross) {
    speed_ = slowSpeed;
  } else {
    speed_ = maxSpeed;
  }
  omniFR.SetSpeed(speed_);
  omniFL.SetSpeed(speed_);
  omniBL.SetSpeed(speed_);
  omniBR.SetSpeed(speed_);
}

void frontAngleSet(int start) {
  if (start) {
    frontAngle = 90 + 180;
  } else {
    frontAngle = 90 + 0;
  }

  omniFR.setAngle(frontAngle);
  omniFL.setAngle(frontAngle);
  omniBL.setAngle(frontAngle);
  omniBR.setAngle(frontAngle);

}

void omniWheelDrive(int leftHatX, int leftHatY, int rightHatX) {
  motorFR.drive(omniFR.drive(leftHatX, leftHatY, rightHatX));
  motorFL.drive(omniFL.drive(leftHatX, leftHatY, rightHatX));
  motorBL.drive(omniBL.drive(leftHatX, leftHatY, rightHatX));
  motorBR.drive(omniBR.drive(leftHatX, leftHatY, rightHatX));
}



void receiveEvent(int howMany) {
  while (Wire.available()) {
    flag = true;

    leftHatX  = Wire.read();
    leftHatY  = Wire.read();
    rightHatX = Wire.read();
    //cross		  = Wire.read();
    //start		  = Wire.read();
  }
}

void showController() {
  Serial.print(leftHatX);
  Serial.print("\t");
  Serial.print(leftHatY);
  Serial.print("\t");
  Serial.print(rightHatX);
  Serial.print("\t");
  Serial.print(cross);
  Serial.print("\t");
  Serial.println(start);
}

void showOmni() {
  omniFR.show();  omniFL.show();
  omniBL.show();  omniBR.show();
  Serial.println();
}

void showMotor(){
  motorFR.show(); motorFL.show();
  motorBL.show(); motorBR.show();
  Serial.println();
}

void show(){
  //showController();
  //showMortor();
  //showOmni();
  showMotor();
}


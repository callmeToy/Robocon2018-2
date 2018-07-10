#include "slaveReceiver.h"
#include "MovingAverage.h"
#include "motor_old.h"


#define M1pinA   2
#define M1pinB   4
#define M1pinPWM 3
#define M2pinA   6
#define M2pinB   5
#define M2pinPWM 9

#define i2cAddress 2
#define averageSize 50
#define border 30
int maxSpeed = 200;
int turnSpeed = 100;

bool flag;
int CeaseCounter;
int leftHatY;

slaveReceiver i2c(1);
motor motorF(M1pinA, M1pinB, M1pinPWM), motorB(M2pinA, M2pinB, M2pinPWM);
MovingAverage averageF(averageSize), averageB(averageSize);

void setup() {
  delay(2000);
  Serial.begin(115200);
  Wire.begin(i2cAddress);
  Wire.onReceive(receiveEvent);
}

void loop() {
  rollerFB(i2c.getData(1));
  show();
}


void rollerFB(int moveY) {
  moveY = map(moveY, 0, 255, +maxSpeed, -maxSpeed);
  if (abs (moveY) < border)
    moveY = 0;
  averageF.Update(+moveY);
  averageB.Update(-moveY);
  motorF.drive(averageF.GetValue());
  motorB.drive(averageB.GetValue());
}



void receiveEvent(int howMany) {
  i2c.Update();
}

void showMotor() {
  motorF.show();
  motorB.show();
  Serial.println();
}

void show() {
  //i2c.show();
  showMotor();
}

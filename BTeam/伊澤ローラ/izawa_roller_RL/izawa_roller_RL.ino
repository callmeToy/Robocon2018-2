#include "slaveReceiver.h"
#include "MovingAverage.h"
#include "motor_old.h"

#define M1pinA   2
#define M1pinB   4
#define M1pinPWM 3
#define M2pinA   6
#define M2pinB   5
#define M2pinPWM 9
#define M3pinA   12
#define M3pinB   A0
#define M3pinPWM 11

#define i2cAddress 3
#define averageSize 50
#define border 30
int maxSpeed = 200;
int turnSpeed = 100;

slaveReceiver i2c(2);
motor motorR(M1pinA, M1pinB, M1pinPWM);
motor motorLF(M2pinA, M2pinB, M2pinPWM), motorLB(M3pinA, M3pinB, M3pinPWM);
MovingAverage averageR(averageSize);
MovingAverage averageLF(averageSize), averageLB(averageSize);

void setup() {
  delay(2000);
  Serial.begin(115200);
  Wire.begin(i2cAddress);
  Wire.onReceive(receiveEvent);
}

void loop() {
  rollerRL();
  show();
}

void rollerRL() {
  int moveX, turn;
  moveX = map(i2c.getData(1), 0, 255, -maxSpeed, +maxSpeed);
  turn = map(i2c.getData(2), 0, 255, -maxSpeed, +maxSpeed);
  if (abs (moveX) < border)
    moveX = 0;
  if (abs(turn) < border)
    turn = 0;
  if (turn != 0) {
    averageR.Update(0);
    averageLF.Update(map(turn, -maxSpeed, +maxSpeed, -turnSpeed, +turnSpeed));
    averageLB.Update(map(turn, -maxSpeed, +maxSpeed, -turnSpeed, +turnSpeed));
  } else {
    averageR.Update(+moveX);
    averageLF.Update(-moveX);
    averageLB.Update(+moveX);
  }
  motorR.drive(averageR.GetValue());
  motorLF.drive(averageLF.GetValue());
  motorLB.drive(averageLB.GetValue());

}

void receiveEvent(int howMany) {
  i2c.Update();
}

void showMotor() {
  motorR.show();
  motorLF.show();
  motorLB.show();
  Serial.println();
}

void show() {
  //i2c.show();
  showMotor();
}

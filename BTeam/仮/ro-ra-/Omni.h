#pragma once
#include "MovingAverage.h"

#define averageSize 50

//@コンストラクタでモーターの取り付け角度を指定//
//@setMotorPinでピンを指定                     //
//@driveの引数はオムニ操作のスティック         //

class Omni {
  public:
    Omni(double angle);
    Omni(double angle , int AverageSize);
    double caluculateAngle(double joystickHat_R_X, double joystickHat_R_Y);
    double caluculatePower(double joystickHat_R_X, double joystickHat_R_Y);
    void setBorder(int borderValue) {
      border = borderValue;
    }
    void setAngle(int frontAngle) {
      motorAngle = motorAngleData + frontAngle - 90;
    }
    void SetSpeed(int speedVal) {
      Speed = speedVal; //speed:0～255
    }
    int drive(double joystickHat_move_X, double joystickHat_move_Y, double joystickHat_turn_X);
    void show();
  private:
    int border = 20;
    double motorPower;
    int Speed = 200;
    int AverageSize = averageSize;
    double joystickAngle;
    double motorAngleData;
    double motorAngle;
    MovingAverage *averageVal;
};

Omni::Omni(double angle) {
  motorAngleData = angle;
  averageVal = new MovingAverage(averageSize);
}
Omni::Omni(double angle, int AverageSize) {
  motorAngleData = angle;
  averageVal = new MovingAverage(AverageSize);
}


double Omni::caluculatePower(double joystickHat_move_X, double joystickHat_move_Y) {
  motorPower = sqrt( square(joystickHat_move_X) + square(joystickHat_move_Y) );
  //Serial.print(motorPower);  Serial.print("\t");
  motorPower = map(motorPower, 0, 342, 0, 255);
  //Serial.println(motorPower);
  return motorPower;
}

double Omni::caluculateAngle(double joystickHat_move_X, double joystickHat_move_Y) {

  joystickAngle = atan2(joystickHat_move_Y, joystickHat_move_X);

  if (joystickAngle < 0) {
    joystickAngle += 2 * PI;
  }

  return joystickAngle;
}


int Omni::drive(double joystickHat_move_X, double joystickHat_move_Y, double joystickHat_turn_X) {
  joystickHat_move_X = -map(joystickHat_move_X, 0, 255, -255, 255);
  joystickHat_move_Y = map(joystickHat_move_Y, 0, 255, -255, 255);
  joystickHat_turn_X = map(joystickHat_turn_X, 0, 255, -255, 255);

  caluculatePower(joystickHat_move_X, joystickHat_move_Y);
  caluculateAngle(joystickHat_move_X, joystickHat_move_Y);

  /*
    Serial.print(joystickHat_move_X);  Serial.print("\t");
    Serial.print(joystickHat_move_Y);  Serial.print("\t");
    Serial.println(joystickHat_turn_X);
  */
  /*
    Serial.print(caluculatePower(joystickHat_move_X, joystickHat_move_Y));
    Serial.print("\t");
    Serial.println(caluculateAngle(joystickHat_move_X, joystickHat_move_Y) * 360 / 2 / PI);
  */

  if (motorPower < border)
    motorPower = 0;
  else if (motorPower >= border)
    motorPower = sin(joystickAngle - motorAngle * (PI / 180)) * motorPower;

  //旋回//
  if (abs(joystickHat_turn_X ) > border)
    motorPower = motorPower + joystickHat_turn_X / 2;

  //移動平均//
  averageVal->Update(motorPower);
  motorPower = averageVal->GetValue();

  //速度制限//
  motorPower = constrain(motorPower, -255, 255);

  motorPower = map(motorPower, -255, 255, -Speed, Speed);

  motorPower = (int)motorPower;
  /*
    Serial.print(joystickAngle * (180/PI));
    Serial.print("\t");
  */
  return motorPower;
}

void Omni::show() {
  Serial.print(motorPower);
  Serial.print("\t");
}

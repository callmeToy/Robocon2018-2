#include <Wire.h>
#include "ControllerManager.h"
#include "i2cMasterWriter.h"
#include "masterReader.h"
#include"sub.h"


ControllerManager DS3(9);
//masterReader i2cLEDSenser(8, 1); //i2cAddress, arrayNum
i2cMasterWriter i2cMotorBoard(4, 8), i2cOmni(10, 4, 1);
i2cMasterWriter i2cSolenoidValve(5, 1);
i2cMasterWriter i2cIzawaRollerFB(6, 1, 1), i2cIzawaRollerRL(3, 2, 1);
i2cMasterWriter i2cRoller(7, 1);


void setup() {
  Wire.begin();
  Serial.begin(115200);
}

void loop() {
  AllUpdate();
  i2cRoller.setData(1, DS3.GetAnalogR2());
  //omni();
  //senserTest();
  //izawaRoller();
  //motorBoard();
  //solenoiValve();
  show();

  if (DS3.GetPS()) {
    i2cMotorBoard.Reset();
    i2cOmni.Reset();
    i2cIzawaRollerFB.Reset(); i2cIzawaRollerRL.Reset();
    i2cSolenoidValve.Reset();

  }
}

void omni() {

  i2cOmni.setData(1, DS3.GetLeftHatX());
  i2cOmni.setData(2, DS3.GetLeftHatY());
  i2cOmni.setData(3, DS3.GetRightHatX());

  i2cOmni.setBitData(4, 1, DS3.GetStartToggle());
  i2cOmni.setBitData(4, 2, DS3.GetTriangleToggle());

  /*
    if (!DS3.GetSquareToggle()) {
      i2cOmni.setData(1, DS3.GetLeftHatY());

      i2cOmni.setData(2, 127);
      i2cOmni.setData(3, DS3.GetRightHatX());
    } else {
      i2cOmni.setData(1, 127);
      i2cOmni.setData(2, DS3.GetLeftHatX());
      i2cOmni.setData(3, DS3.GetRightHatX());
    }
  */
}

void senserTest() {

  static bool stop = false;
  static bool stop2 = false;
  static bool option = true;

  if (DS3.GetShareClick()) {
    if (stop2) {
      stop = false;
      stop2 = false;
    } else {
      stop = !stop;
    }

  }
  if (DS3.GetUpClick())
    option = true;
  else if (DS3.GetDownClick())
    option = false;

//  if (i2cLEDSenser.getBitData(1, 1))
    stop2 = true;
  /*
      if (i2cLEDSenser.getBitData(1, 1) || stop || stop2)
      i2cIzawaRollerFB.setData(1, DS3.GetLeftHatY());
      else if (option && !stop || stop2)
      i2cIzawaRollerFB.setData(1, 127 - 60);
      else if (!stop || stop2)
      i2cIzawaRollerFB.setData(1, 127 + 60);
  */

  i2cIzawaRollerFB.setData(1, DS3.GetLeftHatY());

  Serial.print(stop); Serial.print("\t");
  Serial.print(stop2); Serial.print("\t");
//  Serial.print(i2cLEDSenser.getBitData(1, 1));  Serial.print("\t");
//  Serial.print(i2cLEDSenser.getBitData(1, 2));  Serial.print("\t");
  Serial.print(option); Serial.println("\t");

}
void motorBoard() {
  static int motorPower;

  if (DS3.GetSelectToggle()) {
    motorPower += DS3.GetRightClick() * 20;
    motorPower -= DS3.GetLeftClick() * 20;
    motorPower = constrain(motorPower , 0, 240);
    i2cMotorBoard.MsetData(1, map(motorPower, 0, 255, 0,  255));
    i2cMotorBoard.MsetData(2, map(motorPower, 0, 255, 0, -255));
  } else {
    i2cMotorBoard.MsetData(1, map(DS3.GetAnalogR2(), 0, 255, 0,  255));
    i2cMotorBoard.MsetData(2, map(DS3.GetAnalogR2(), 0, 255, 0, -255));
    motorPower = 0;
  }
}

void  solenoiValve() {
  i2cSolenoidValve.setBitData(0, 0, DS3.GetSquareToggle());
  i2cSolenoidValve.setBitData(0, 1, DS3.GetSquareToggle());
}

void AllUpdate() {
  DS3.Update();
//  i2cLEDSenser.Update();
//  i2cMotorBoard.Update();
//  i2cIzawaRollerFB.Update();
//  i2cIzawaRollerRL.Update();
//  i2cOmni.Update();
//  i2cSolenoidValve.Update();
  i2cRoller.Update();
}

void show() {
  //Serial.print(moveAngle);  Serial.print("\t");
  //i2cMotorBoard.show();
  //i2cSolenoidValve.Show();
  //i2cIzawaRollerFB.show();
  //i2cIzawaRollerRL.show();
  //i2cOmni.show();
  //i2cLEDSenser.show();
  //Serial.println(i2cLEDSenser.getData(1),BIN);
  i2cRoller.show();
  /*
    Serial.print(DS3.GetLeftHatX());  Serial.print("\t");
    Serial.print(DS3.GetLeftToggle());  Serial.print("\t");
    Serial.println(DS3.GetCircleToggle());
  */
  // Serial.println(DS3.GetPS());
}


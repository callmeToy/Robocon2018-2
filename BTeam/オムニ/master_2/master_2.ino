#include <Wire.h>
#include "ControllerManager.h"
#include "i2cMasterWriter.h"
#include "masterReader.h"
#include "enc_board_mbed.h"
#include "PidController.h"
#include "LoopCycleController.h"


static LoopCycleController loopCtrl(10000);     //ループ周期を100000us(100ms)に設定
static PidController pidCtrlY(0.01, 0, 0.001, loopCtrl.Cycle_us(), 300.0);
static PidController pidCtrlX(0.01, 0, 0.001, loopCtrl.Cycle_us(), 300.0);
static PidController pidCtrlTurn(0.01, 0, 0.001, loopCtrl.Cycle_us(), 300.0);
//比例係数, 積分係数10, 微分係数、ループ周期を100000us、席分量の最大値を300に設定

ControllerManager DS3(9);
i2cMasterWriter i2cOmni(3, 4, 1);
EncoderBoardMbed enc(2);

int move_X = 0, move_Y = 0;

void setup() {
  Wire.begin();
  Wire.setClock(400000UL);
  Serial.begin(115200);

  pidCtrlX.ClearPower();

  pidCtrlY.ClearPower();
  pidCtrlTurn.ClearPower();

  enc.init();

}


void loop() {
  omni();
  show();
  AllUpdate();
  /*
    if (DS3.GetPS()) {
    i2cOmni.Reset();
    }
  */
}

void omni() {

  if (DS3.GetCircleClick()) {
    for (int i = 1; i <= 4; i++)
      enc.resetCount(i);
  }


  if (DS3.GetUpToggle())
    move_Y = -28600;
  else
    move_Y = 0;
  if (DS3.GetRightToggle())
    move_X = 1000;
  else
    move_X = 0;

  pidCtrlX.Update(enc.getCount(2), move_X, 100);
  pidCtrlY.Update(enc.getCount(1), move_Y, 100);
  pidCtrlTurn.Update(enc.getCount(1) + enc.getCount(3), 0, 100);
  /*
    pidCtrlX.Update(move_X - enc.getCount(1), 0, DS3.GetAnalogR2());
    pidCtrlY.Update(move_Y - enc.getCount(2), 0, DS3.GetAnalogR2());
    pidCtrlTurn.Update(enc.getCount(1) - enc.getCount(3), 0, DS3.GetAnalogR2());

  */
  if (DS3.GetCircleClick())
    enc.resetCount();

  if (!DS3.GetSelectToggle()) {
    i2cOmni.setData(1, 127);
    i2cOmni.setData(2, 127);
    i2cOmni.setData(3, 127);
  } else if (DS3.GetStartToggle()) {
    i2cOmni.setData(1, map(pidCtrlX.GetPower(), -255, 255, 255, 0));
    i2cOmni.setData(2, map(pidCtrlY.GetPower(), -255, 255, 0, 255));
    i2cOmni.setData(3, map(pidCtrlTurn.GetPower(), -255, 255, 0, 255));
//    i2cOmni.setData(1, 127);
//    i2cOmni.setData(3, 127);
  } else {
    i2cOmni.setData(1, DS3.GetLeftHatX());
    i2cOmni.setData(2, DS3.GetLeftHatY());
    i2cOmni.setData(3, DS3.GetRightHatX());
  }
  i2cOmni.setBitData(4, 1, DS3.GetCrossToggle());
  i2cOmni.setBitData(4, 2, DS3.GetSquareToggle());

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


void AllUpdate() {
  DS3.Update();
  i2cOmni.Update();
  enc.update();
  loopCtrl.Update();
}

void show() {

  Serial.print(move_X);  Serial.print("\t");
  Serial.print(move_Y);  Serial.print("\t");
  Serial.print(enc.getCount(1) + enc.getCount(3));  Serial.print("\t");
  Serial.print(enc.getCount(1));  Serial.print("\t");
  Serial.print(enc.getCount(2));  Serial.print("\t");
  Serial.print(enc.getCount(3));  Serial.print("\t");
  Serial.print(pidCtrlX.GetPower());  Serial.print("\t");
  Serial.print(pidCtrlY.GetPower());  Serial.print("\t");
  Serial.print(pidCtrlTurn.GetPower());  Serial.print("\t");

  i2cOmni.show();
  //  Serial.print(DS3.GetLeftHatX());  Serial.print("\t");
  //  Serial.println(DS3.GetStartToggle());
}


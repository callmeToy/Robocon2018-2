#include<arduino.h>
#include"ControllerManager.h"
#include"i2cMasterWriter.h"

void izawaRoller() {
  if (!DS3.GetSquareToggle()) {
    i2cIzawaRollerFB.setData(1, DS3.GetLeftHatY());

    i2cIzawaRollerRL.setData(1, 127);
    i2cIzawaRollerRL.setData(2, 127);
  } else {
    i2cIzawaRollerFB.setData(1, 127);

    i2cIzawaRollerRL.setData(1, DS3.GetLeftHatX());
    i2cIzawaRollerRL.setData(2, DS3.GetRightHatX());
  }
}

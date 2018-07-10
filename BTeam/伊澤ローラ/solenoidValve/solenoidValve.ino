#include "slaveReceiver.h"
#include "solenoid.h"

#define i2cAddress 5

slaveReceiver i2c(1);
solenoid valve1(11), valve2(3);

void setup() {
  delay(2000);
  Serial.begin(115200);
  Wire.begin(i2cAddress);
  Wire.onReceive(receiveEvent);
}

void loop() {
  valveDrive();
  show();
}

void valveDrive() {
  valve1.Run(i2c.getBitData(1, 1));
  valve2.Run(i2c.getBitData(1, 2));
}

void receiveEvent(int howMany) {
  i2c.Update();
}

void show() {
  //i2c.show();

  valve1.show();
  valve2.show();
  Serial.println();
}

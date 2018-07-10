#include "slaveSender.h"
#include "lineSenser.h"
#include <SerialDataLogger.h>

#define LEDPIN1 A0
#define LEDPIN2 A1
#define LEDPIN3 A2

#define WHITE_BORDER_1 730
#define WHITE_BORDER_2 730
#define WHITE_BORDER_3 730

SerialDataLogger logger(3);
slaveSender i2cSend(1);

lineSenser senser[3] = {
  lineSenser(LEDPIN1, WHITE_BORDER_1),
  lineSenser(LEDPIN2, WHITE_BORDER_2),
  lineSenser(LEDPIN3, WHITE_BORDER_3)
};

void setup() {
  Wire.begin(8);
  Wire.onRequest(requestEvent);
  Serial.begin(115200);
  i2cSend.Reset();
}

void loop() {
  //setSendData();
  setDataLogger();
  update();
  //show();
}


void setSendData() {
  for (int i = 0; i < 3; i++)
    i2cSend.setBitData(1, i + 1, senser[i].getOnLine());

}

void setDataLogger() {
  float data[3] = {0, 0, 0};
  float time = (float)micros() / 1000000.0f;
  for (int i = 0; i < 3; i++)
    data[i] = (float)senser[i].getSenserValue();

  logger.SetX(time);
  for (int i = 0; i < 3; i++)
    logger.SetSeriesY(i, data[i]);

  logger.Send();
  Serial.flush();

}

void update() {
  i2cSend.Update();
  for (int i = 0; i < 3; i++)
    senser[i].update();
}

void requestEvent() {
  i2cSend.Update();
}

void show() {
  for(int i = 0; i < 3; i++)
    senser[i].show();
  Serial.println();
   
  //i2cSend.show();
}


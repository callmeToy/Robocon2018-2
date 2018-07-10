#include "slaveSender.h"
#include <SerialDataLogger.h>

#define LEDPIN1 A0
#define LEDPIN2 A1

#define WHITE_BORDER_1 730
#define WHITE_BORDER_2 730

SerialDataLogger logger(2);
slaveSender i2cSend(1);

int senserValue[] = {0, 0};
bool sendData[] = {false, false};

void setup() {
  Wire.begin(8);
  Wire.onRequest(requestEvent);
  Serial.begin(115200);
  i2cSend.Reset();
}

void loop() {
  getSenserValue();
  setSendData();
  //setDataLogger();
  i2cSend.Update();
  show();
}

void getSenserValue() {
  senserValue[0] = analogRead(LEDPIN1);
  senserValue[1] = analogRead(LEDPIN2);
}

void setSendData() {
  if (senserValue[0] > WHITE_BORDER_1)
    sendData[0] = true;
  else
    sendData[0] = false;

  if (senserValue[1] > WHITE_BORDER_2)
    sendData[1] = true;
  else
    sendData[1] = false;
  /*
    for (int i = 0; i < 2 + 1; i++) {
      i2cSend.setBitData(1, i+1, sendData[i]);
    }
  */
  i2cSend.setBitData(1, 1, sendData[0]);
  i2cSend.setBitData(1, 2, sendData[1]);

}

void setDataLogger() {
  float time = (float)micros() / 1000000.0f;
  float data1 = (float)senserValue[0];
  float data2 = (float)senserValue[1];

  logger.SetX(time);
  logger.SetSeriesY(0, data1);
  logger.SetSeriesY(1, data2);

  logger.Send();
  Serial.flush();

}

void requestEvent() {
  i2cSend.Update();
}

void show() {
  /*
    for (int i = 0; i < 2 + 1; i++) {
    Serial.print(senserValue[i]);
    Serial.print("\t");
    }
    Serial.println();
  */


      Serial.print(senserValue[0]); Serial.print("\t");
      Serial.print(senserValue[1]); Serial.print("\t");
  /*
    Serial.print(sendData[0]); Serial.print("\t");
    Serial.println(sendData[1]);
  */
  i2cSend.show();
}


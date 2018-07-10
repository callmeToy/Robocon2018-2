#include <SerialDataLogger.h>

#define pin1 A1
#define pin2 A2

SerialDataLogger logger(2);

enum option {
  serialprint,
  serialprintColour,
  serialDataLogger
};



void setup() {
  Serial.begin(115200);
}

int val1 = 0, val2 = 0;
char colour1, colour2;

void loop() {
  enum option option;
  //option = serialprint;
  //option = serialprintColour;
  option = serialDataLogger;

  val1 = analogRead(pin1);
  val2 = analogRead(pin2);



  switch (option) {
    case serialprint:
      Serial.print(val1); Serial.print('\t');
      Serial.println(val2);
      break;

    case serialprintColour:
      printColour(val1);
      printColour(val2);
      Serial.print('\n');
      break;

    case serialDataLogger:
      float time = (float)micros() / 1000000.0f;
      float data1 = (float)val1;
      float data2 = (float)val2;

      logger.SetX(time);
      logger.SetSeriesY(0, data1);
      logger.SetSeriesY(1, data2);

      logger.Send();
      Serial.flush();
      break;
  }
}

void printColour (int val) {
  if (val > 700 && val < 800)
    Serial.print("white");
  else if (val > 800 && val < 850)
    Serial.print("brown");
  else if (val > 900 && val < 970)
    Serial.print("black");
  else
    Serial.print("error");
    
  Serial.print(":");
}

void printColourNo (int val) {
  if (val > 720 && val < 800)
    Serial.print(1);
  else if (val > 800 && val < 850)
    Serial.print(2);
  else if (val > 900 && val < 970)
    Serial.print(3);
  else
    Serial.print(0);
}

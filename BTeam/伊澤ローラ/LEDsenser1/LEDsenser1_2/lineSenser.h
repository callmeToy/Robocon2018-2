#pragma once
#include <arduino.h>

class lineSenser {
  private:
    int senserValue;
    bool onLine = false;
    int highBorder = 1023;
    int lowBorder = 0;
    int senserPin;

  public:
    lineSenser(int pin, int low);
    lineSenser(int pin, int low, int high);
    void update();
    void setOnLine();
    int getSenserValue();
    bool getOnLine();
    void show();
};


lineSenser::lineSenser(int pin, int low) {
  pinMode(pin, INPUT);
  lowBorder = low;
  senserPin = pin;
}
lineSenser::lineSenser(int pin, int low, int high) {
  pinMode(pin, INPUT);
  lowBorder = low;
  highBorder = high;
  senserPin = pin;

}

void lineSenser::update() {
  senserValue = analogRead(senserPin);
  setOnLine();
}

void lineSenser::setOnLine() {
  if (senserValue > lowBorder && senserValue < highBorder)
    onLine = true;
  else
    onLine = false;

}

int lineSenser::getSenserValue() {
  return senserValue;
}

bool lineSenser::getOnLine() {
  return onLine;
}

void lineSenser::show() {
  Serial.print(senserValue);
  Serial.print("\t");
  Serial.print(onLine);
  Serial.print("\t");
}


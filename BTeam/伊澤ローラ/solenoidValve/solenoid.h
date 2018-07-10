#pragma once

class solenoid {
  private:
    bool buttonData;
  	int pin;

  public:
    solenoid(int pin) {
      pinMode(pin, OUTPUT);
      this->pin = pin;
    }

    void Run(bool DATA) {
      buttonData = DATA;
      if (buttonData) {
        digitalWrite(pin, HIGH);
      } else {
        digitalWrite(pin, LOW);
      }
    }

    void show() {
      Serial.print(buttonData);
      Serial.print("\t");
    }
};


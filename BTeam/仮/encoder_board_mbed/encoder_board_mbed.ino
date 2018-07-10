#include <Wire.h>
#include"enc_board_mbed.h"

#define ADDR 2

EncoderBoardMbed enc(ADDR);

void setup() {

  Wire.begin();
  Wire.setClock(400000UL);
  Serial.begin(115200);

}

void loop() {
  
  Serial.println(enc.getCount(4));


  enc.Update();
}


/*
    @Description    Mbedで読み取ったエンコーダの値をArduinoで受け取るクラス
    @Author    Watanabe Rui
    @Date    2018/05/11
*/

#pragma once

#include<Wire.h>

class EncoderBoardMbed {
  
  private:
    int mADDR; //I2Cアドレス

    int mEncBuf[4][4];
    int64_t mEncData[4];
    
  public:

    /*
          コンストラクタ
          @param ADDR MbedとのI2Cアドレス
    */
    EncoderBoardMbed(int ADDR) {
      mADDR = ADDR >> 1; // Mbed->7bit，Arduino->8bitでアドレス指定するので右に一つシフト
    }

    /*
       mbedから全てのエンコーダの値を受信
    */
    void Update() {
      Wire.requestFrom(mADDR, 16);
      while(Wire.available()>=16){
            mEncBuf[0][0] = Wire.read();
            mEncBuf[0][1] = Wire.read();
            mEncBuf[0][2] = Wire.read();
            mEncBuf[0][3] = Wire.read();

            mEncBuf[1][0] = Wire.read();
            mEncBuf[1][1] = Wire.read();
            mEncBuf[1][2] = Wire.read();
            mEncBuf[1][3] = Wire.read();

            mEncBuf[2][0] = Wire.read();
            mEncBuf[2][1] = Wire.read();
            mEncBuf[2][2] = Wire.read();
            mEncBuf[2][3] = Wire.read();

            mEncBuf[3][0] = Wire.read();
            mEncBuf[3][1] = Wire.read();
            mEncBuf[3][2] = Wire.read();
            mEncBuf[3][3] = Wire.read();
      }
      
      mEncData[0] = (mEncBuf[0][0] << 24) | (mEncBuf[0][1] << 16) | (mEncBuf[0][2] << 8) | mEncBuf[0][3];
      mEncData[1] = (mEncBuf[1][0] << 24) | (mEncBuf[1][1] << 16) | (mEncBuf[1][2] << 8) | mEncBuf[1][3];
      mEncData[2] = (mEncBuf[2][0] << 24) | (mEncBuf[2][1] << 16) | (mEncBuf[2][2] << 8) | mEncBuf[2][3];
      mEncData[3] = (mEncBuf[3][0] << 24) | (mEncBuf[3][1] << 16) | (mEncBuf[3][2] << 8) | mEncBuf[3][3];
    
    }

    long getCount(int port) {
      return mEncData[port-1];
    }

};


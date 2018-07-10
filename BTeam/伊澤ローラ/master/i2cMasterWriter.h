#pragma once
#include<arduino.h>
#include<Wire.h>

//option.1:omni,2:motor
class i2cMasterWriter {

  private:
    const int i2c_address;
    byte* data;
    int Size;
    int _option;

  public:
    i2cMasterWriter(int Address, int array_size, bool option = 0) : i2c_address(Address) {

      //���p�ɔz���������
      if (option == 1) {
        data = new byte[array_size];
        memset(data, 127, 3);
        Size = array_size;

      } else {
        data = new byte[array_size];
        for (int i = 0; i < array_size; i++)
          data[i] = 0;
        Size = array_size;

      }
      Size = array_size;
      _option = option;
    }
    
    void MsetData(int array_num, int Data) {
      Data = constrain(Data, -255, 255);
      if(Data == 0){
        data[array_num * 2 - 2] = 0;
      } else if (Data > 0) {
        data[array_num * 2 - 2] = 1;
      } else {
        data[array_num * 2 - 2] = 2;
      }
      data[array_num * 2 - 1] = abs(Data); 
    }

    void show() {
      for (int i = 0; i < Size; i++) {
        Serial.print(data[i]);
        Serial.print("\t");
      }
      //Serial.print(Size);
      Serial.println("");
    }

    //�f�X�g���N�^
    virtual ~i2cMasterWriter() {
      delete[] data;
    }


    void setData(int array_num, int Data) {

      /*
            //MotorBoard//PWM:-255�`255
            if (_option == 2) {
              int PWM = Data;
              byte portNum = array_num;
              byte Mode;
              if (PWM == 0) {
                Mode = 0;
              } else if (PWM > 0) {
                Mode = 1;
              } else {
                Mode = 2;
              }

              PWM = abs(PWM);

              data[portNum * 2 - 2] = Mode;
              data[portNum * 2 - 1] = PWM;
            } else {
      */
      Data = min(Data, 255);
      data[array_num-1] = Data;

    }

    //bitWrite
    void setBitData(int array_num, byte bit_num, bool bit) {
      bitWrite(data[array_num-1], bit_num-1 , bit);
    }

    void Reset() {
      //���p
      if (_option == 1) {
        memset(data, 127, 3);
      }
      else {
        for (int i = 0; i < Size; i++) {
          data[i] = 0;
        }
      }
    }

    // Slave���֑��M
    void Update() {
      Wire.beginTransmission(i2c_address);
      Wire.write(data, Size);
      Wire.endTransmission();
    }
};
extern i2cMasterWriter i2cIzawaRollerFB,i2cIzawaRollerRL;

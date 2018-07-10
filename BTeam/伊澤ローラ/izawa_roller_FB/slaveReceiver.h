#pragma once

#include <Wire.h>

class slaveReceiver {
	private:
		const int i2c_address;
		byte* data;
		//int i2c_address;
		int size;
	
	public:
		slaveReceiver(int array_size);
		byte getData(int array_num);
    bool getBitData(int array_num, byte bit_num);
		void Update();
		void show();
};

slaveReceiver::slaveReceiver(int array_size){
	data = new byte[array_size];
	for (int i = 0; i < array_size; i++)
		data[i] = 0;
	size = array_size;
}

byte slaveReceiver::getData(int array_num){
  return (int)data[array_num - 1];
}

bool slaveReceiver::getBitData(int array_num, byte bit_num){
  return bitRead (data[array_num - 1], bit_num - 1);
}

void slaveReceiver::Update(){
  while(Wire.available() >= size){
    for(int i=0 ; i<size ; i++)
        data[i] = Wire.read();
	}
}
void slaveReceiver::show(){
	for(int i = 0; i < size; i++){
		Serial.print(data[i]);
		Serial.print("\t");
	}
	Serial.println();
}

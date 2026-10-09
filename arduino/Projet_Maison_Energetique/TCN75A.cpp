#include "TCN75A.h"

TCN75A::TCN75A(uint8_t adr){
  _adr = adr;
}

void TCN75A::begin(TwoWire &wire){
  _wire = &wire;
  _wire->begin();
}

float TCN75A::readTemperature(){
  float data[1];
  _wire->beginTransmission(_adr);
  _wire->write(0x00);
  _wire->endTransmission(false);
  _wire->requestFrom(_adr,uint8_t(2)); //need 2 bytes
  //force data to fit with int8_t then convert it to float
  data[0] = float(int8_t(_wire->read()));
  data[1] = float((uint8_t(_wire->read() >> 4)) / 16.0);
  _wire->endTransmission();
  return data[0] + data[1];
}

// set temps
// min: -40; max: 125

void TCN75A::setRangeTemp(float val_down, float val_up){
  setHystTemp(val_down); setLimitTemp(val_up);
}

void TCN75A::setHystTemp(float val){
  setTemp(0x02,val);
}

void TCN75A::setLimitTemp(float val){
  setTemp(0x03,val);
}

void TCN75A::setTemp(uint8_t p, float value){
  if(value < -40.0)
	value = -40.0;
  if(value > 125.0)
	value = 125.0;

  _wire->beginTransmission(_adr);
  _wire->write(p); //choose the config
  if(value - floor(value) < 0.5){ 
    //high school tier else-if statement
    _wire->write(int8_t(floor(value)));
    _wire->write(0x00);
  } else if (value - floor(value) == 0.5){
    _wire->write(int8_t(floor(value)));
    _wire->write(0x80);
  } else if (value - floor(value) > 0.5) {
    _wire->write(int8_t(ceil(value)));
    _wire->write(0x00);
  }
  _wire->endTransmission();
}

//get temp

float TCN75A::getLimitTemp(){
  return getTemp(0x03);
}

float TCN75A::getHystTemp(){
  return getTemp(0x02);
}

float TCN75A::getTemp(uint8_t p){
  int8_t data[1];
  _wire->beginTransmission(_adr);
  _wire->write(p); // THYST pointer
  _wire->endTransmission(false);
  _wire->requestFrom(_adr,uint8_t(2)); //need two bytes
  data[0] = _wire->read(); //get first byte
  data[1] = _wire->read() >> 7; //get second byte
  _wire->endTransmission();
  return float(data[0]) + (data[1] == 0x01 ? 0.5 : 0.0);
}

// configuration

uint8_t TCN75A::readConfig(){
  uint8_t data;
  _wire->beginTransmission(_adr);
  _wire->write(0x01); // CONFIG pointer
  _wire->endTransmission(false);
  _wire->requestFrom(_adr,uint8_t(1)); //SINGLE BYTE
  data = _wire->read();
  _wire->endTransmission();
  return data;
}

void TCN75A::writeConfig(uint8_t data){
  _wire->beginTransmission(_adr);
  _wire->write(0x01);
  _wire->write(data);
  _wire->endTransmission();
}

void TCN75A::setOneShot(bool sw){
  uint8_t rbyte = readConfig();
  bitWrite(rbyte, 7, sw);
  writeConfig(rbyte);
}

void TCN75A::setResolution(uint8_t val){
  uint8_t rbyte = readConfig();
  if(val > 0x03)
    val = 0x03;
  bitWrite(rbyte, 5, val % 2); //bit-5
  bitWrite(rbyte, 6, val > 1 ? 1 : 0); //bit-6, this is stupid
  writeConfig(rbyte);
}

void TCN75A::setFaultQueue(uint8_t val){
  uint8_t rbyte = readConfig();
  if(val > 0x03)
    val = 0x03;
  bitWrite(rbyte, 3, val % 2); //bit-3
  bitWrite(rbyte, 4, val > 1 ? 1 : 0); //bit-4
  writeConfig(rbyte);
}

void TCN75A::setAlertPolarity(bool sw){
  uint8_t rbyte = readConfig();
  bitWrite(rbyte, 2, sw);
  writeConfig(rbyte);
}

void TCN75A::setAlertMode(bool sw){
  uint8_t rbyte = readConfig();
  bitWrite(rbyte, 1, sw);
  writeConfig(rbyte);
}

void TCN75A::setShutdown(bool sw){
  uint8_t rbyte = readConfig();
  bitWrite(rbyte, 0, sw);
  writeConfig(rbyte);
}

int8_t TCN75A::checkConfig(uint8_t op){
  if(op >= 0x06)
    return -1; //invalid option
  uint8_t rbyte = readConfig();
  switch(op){
    case 0x03:
      return bitRead(rbyte,0x03) + (bitRead(rbyte,0x04) << 1);
    case 0x04:
      return bitRead(rbyte,0x05) + (bitRead(rbyte,0x06) << 1);
    default:
      return bitRead(rbyte, op);
  }
}

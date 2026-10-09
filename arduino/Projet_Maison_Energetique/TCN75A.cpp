#include "TCN75A.h"
#include <math.h>

TCN75A::TCN75A(uint8_t adr){
  _adr = adr;
  _wire = 0;
}

void TCN75A::begin(TwoWire &wire){
  _wire = &wire;
  _wire->begin();
}

float TCN75A::readTemperature(){
  return readTemperatureRegister(0x00, 0xF0);
}

float TCN75A::readTemperatureRegister(uint8_t pointer, uint8_t low_mask){
  if (!_wire) return NAN;
  _wire->beginTransmission(_adr);
  _wire->write(pointer);
  if (_wire->endTransmission(false) != 0) return NAN;
  if (_wire->requestFrom(_adr, uint8_t(2)) != 2 || _wire->available() < 2)
    return NAN;
  int high = _wire->read();
  int low = _wire->read();
  if (high < 0 || low < 0) return NAN;
  // Signed, left-aligned fixed-point register; 1 LSB of this word = 1/256 C.
  int32_t raw = (int32_t(uint8_t(high)) << 8) | (uint8_t(low) & low_mask);
  if (raw & 0x8000) raw -= 65536;
  return float(raw) / 256.0f;
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
  return readTemperatureRegister(p, 0x80); // Threshold registers have 0.5 C steps.
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


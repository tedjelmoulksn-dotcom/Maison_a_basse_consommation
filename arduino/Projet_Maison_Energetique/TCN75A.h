#ifndef TCN75A_ft
#define TCN75A_ft

#include "Arduino.h"
#include "Wire.h"

#define ONESHOT 0x05
#define ADC_RESO 0x04
#define F_QUEUE 0x03
#define ALERT_POL 0x02
#define COMP_INT 0x01
#define SHUTDOWN 0x00

#define COMP_MODE false
#define INT_MODE true

/// @brief A TCN75A class
class TCN75A{
  public:
  /// @brief Specify a TCN75A device
  /// @param adr The i2c address of TCN75A
  TCN75A(uint8_t adr);
  /// @brief Initial a TCN75A device
  /// @param wire A TwoWire object, leave blank for default
  void begin(TwoWire &wire = Wire);
  
  /// @brief Read the temperature
  /// @return The temperature value (in celsius)
  float readTemperature(); //read temperature as normal

  /// @brief Set the hysteresis temperature
  /// @param val The hysteresis value (in celsius)
  /// @note Should be lower than limit-set temperature
  void setHystTemp(float val);
  /// @brief Set the limit-set temperature
  /// @param val The limit-set value (in celsius)
  /// @note Should be higher than hysteresis temperature
  void setLimitTemp(float val);
  /// @brief Set the range of hysteresis and limit-set
  /// @param val_down The hysteresis value (in celsius)
  /// @param val_up The limit-set value (in celsius)
  /// @note The 'val_down' parameter should be lower than the 'val_up' parameter
  void setRangeTemp(float val_down, float val_up);
  /// @brief Get the limit-set temperature
  /// @return The limit-set value (in celsius)
  float getLimitTemp();
  /// @brief Get the hysteresis temperature
  /// @return The hysteresis value (in celsius)
  float getHystTemp();
  
  //config registers

  /// @brief Configure One-Shot Mode
  /// @param sw (logic 0 = Disable [Default], logic 1 = Enable)
  void setOneShot(bool sw);
  /// @brief Configure ADC conversion resolution
  /// @param val Configure value (Default: 9-Bit [0x00])
  void setResolution(uint8_t val);
  /// @brief Configure Fault Queue
  /// @param val Configure value (Default: 1 [0x00])
  /// @note https://github.com/FaultyTwo/TCN75A-arduino-lib
  void setFaultQueue(uint8_t val);
  /// @brief Configure Alert Polarity
  /// @param sw (logic 0 = Active-Low [Default], logic 1 = Active-High)
  void setAlertPolarity(bool sw);
  /// @brief Configure Alert Mode
  /// @param sw (logic 0 = Comparator [Default], logic 1 = Interrupt)
  void setAlertMode(bool sw);
  /// @brief Configure Shutdown Mode
  /// @param sw (logic 0 = Disable [Default], logic 1 = Enable)
  void setShutdown(bool sw);
  /// @brief Check a config
  /// @param op Operation code
  /// @return The value of a config
  /// @note https://github.com/FaultyTwo/TCN75A-arduino-lib
  int8_t checkConfig(uint8_t op);
  
  private:
  uint8_t readConfig();
  void writeConfig(uint8_t data);
  float getTemp(uint8_t p); //reducing nuisance
  void setTemp(uint8_t p, float value); //same here
  TwoWire *_wire;
  uint8_t _adr;
};

#endif

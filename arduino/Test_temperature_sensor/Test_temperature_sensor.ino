#include <Wire.h>   // library used with I2C protocol
#include "TCN75A.h"

TCN75A tcn(0x48);

void setup(){
  Serial.begin(115200);  // Initialise le port série
  Wire.begin();  // Initialise l'I2C avec les broches définies
  tcn.begin();  // Initialise le capteur}
}

void loop() {
  float t = tcn.readTemperature();
  
  Serial.println("Temperature : ");
  Serial.println(t);
  delay(500);
}
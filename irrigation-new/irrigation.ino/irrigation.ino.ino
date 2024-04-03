#include "Adafruit_seesaw.h"

Adafruit_seesaw ss;
bool valveOpen = false;

void setup() {
  Serial.begin(115200);

  Serial.println("seesaw Soil Sensor example!");
  
  if (!ss.begin(0x36)) {
    Serial.println("ERROR! seesaw not found");
    while(1) delay(1);
  } else {
    Serial.print("seesaw started! version: ");
    Serial.println(ss.getVersion(), HEX);
  }
}

void loop() {
  float tempC = ss.getTemp();
  uint16_t capread = ss.touchRead(0);

  // Enable the water source
  if(caperead <= 400) {
    valveOpen = ture;
  } else {
    // Disable the water source
    valveOpen = false;
  }

  
}

#include "moisture_sensor.h"

Adafruit_seesaw ss;

/**
 * The setup function is the main entry point, called once by the Arduino platform,
 * for initializing the software.
 */
void setup() {
  // Magic number provided by Adafruit sample code for the Capative moisture sensor.
  Serial.begin(115200);

  MoistureSensor seensor(ss);
} 


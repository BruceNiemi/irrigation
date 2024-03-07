#include "moisture_sensor.h"
#include "state.h"
#include "idle_timer_state.h"

// Reading the documentation this is the default I2C address for the sensor
// https://cdn-learn.adafruit.com/downloads/pdf/adafruit-stemma-soil-sensor-i2c-capacitive-moisture-sensor.pdf
#define I2C_ADDRESS 0x36
#define DEBUG

Adafruit_seesaw ss;
MoistureSensor* sensor = nullptr;

bool changed = true;
State* current = nullptr;

/**
 * The setup function is the main entry point, called once by the Arduino platform,
 * for initializing the software.
 */
void setup() {
  // Magic number provided by Adafruit sample code for the Capative moisture sensor.
  // It's the Baud rate but the comment is more funny.
  Serial.begin(115200);

  // Due to wantting reliability in the software if no sensor is found
  // during the initalizing process we will use a fallback timer based approach
  // to water source control.
  if (false) {
#ifdef DEBUG
    log("moisture sensor detected");
#endif

    sensor = new MoistureSensor(ss);
  } else {
#ifdef DEBUG
    Serial.println("moisture sensor not found");
#endif
    current = (State*) new IdleTimerState();
  }
}

#ifdef DEBUG
void log(String message) {
  Serial.println("INFO: " + message);
}
#endif

void loop() {
  if (changed) {
    changed = false;
    current->enter();
  }

  State* workingState = current->execute();

  if (workingState != current) {
    delete current;
    current = workingState;
    changed = true;
  }
}
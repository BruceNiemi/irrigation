#include "idle_sensor_state.h"
#include "enable_water_source_sensor_state.h"

#define DELAY_IN_MILLIS 60000

void IdleSensorState::enter() {
  this->lastMillis = millis();
}

State* IdleSensorState::execute() {
  if (millis() > this->lastMillis + DELAY_IN_MILLIS) {
    Serial.println("transitioning to enable water source");
    return new EnableWaterSourceSesorState(sensor);
  }

  return this;
}
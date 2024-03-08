#include "idle_sensor_state.h"
#include "poll_sensor_state.h"

#define DELAY_IN_MILLIS 60000

void IdleSensorState::enter() {
  this->lastMillis = millis();
}

State* IdleSensorState::execute() {
  if (millis() > this->lastMillis + DELAY_IN_MILLIS) {
    Serial.println("transitioning to enable water source sensor");
    return new PollSensorState(sensor);
  }

  return this;
}
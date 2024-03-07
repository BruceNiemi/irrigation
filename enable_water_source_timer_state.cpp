#include "enable_water_source_timer.h"
#include "disable_water_source_timer.h"

#define DELAY_IN_MILLIS 30000

void EnableWaterSourceTimer::enter() {
  this->lastMillis = millis();
}

State* EnableWaterSourceTimer::execute() {
  if (millis() > this->lastMillis + DELAY_IN_MILLIS) {
        Serial.println("transitioning to disable water source");
    return new DisableWaterSourceTimer();
  }

  return this;
}
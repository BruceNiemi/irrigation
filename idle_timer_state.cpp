#include "idle_timer_state.h"
#include "enable_water_source_timer.h"

#define DELAY_IN_MILLIS 60000

void IdleTimerState::enter() {
  this->lastMillis = millis();
}

State* IdleTimerState::execute() {
  if (millis() > this->lastMillis + DELAY_IN_MILLIS) {
    Serial.println("transitioning to enable water source");
    return new EnableWaterSourceTimer();
  }

  return this;
}
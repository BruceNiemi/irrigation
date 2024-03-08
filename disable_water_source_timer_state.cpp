#include "disable_water_source_timer_state.h"
#include "idle_timer_state.h"

State* DisableWaterSourceTimer::execute() {
  Serial.println("transitioning to disable water source");
  return new IdleTimerState();
}
#include "disable_water_soure_sensor_state.h"
#include "idle_sensor_state.h"

State* DisableWaterSourceState::execute() {
  Serial.println("transiting to idle state sensor.");
  return new IdleSensorState(sensor);
}
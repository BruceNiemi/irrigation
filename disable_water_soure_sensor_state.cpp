#include "disable_water_soure_sensor_state.h"
#include "idle_sensor_state.h"

State* DisableWaterSourceState::execute() {
  return new IdleSensorState(sensor);
}
#include "poll_sensor_state.h"
#include "enable_water_source_sensor_state.h"
#include "idle_sensor_state.h"

State* PollSensorState::execute() {
  if (this->sensor->GetMoisture() <= 0.5 ||
      this->sensor->GetTemperature() > 27) {
    Serial.println("sensor enable water source");
    return new EnableWaterSourceSesorState(sensor);
  }
  Serial.println("sensor poll back to idle");
  return new IdleSensorState(sensor);
}
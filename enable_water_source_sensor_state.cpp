#include "enable_water_source_sensor_state.h"
#include "disable_water_soure_sensor_state.h"

#define DELAY_IN_MILLIS 45000

void EnableWaterSourceSesorState::enter() {
  this->lastMillis = millis();
}

State* EnableWaterSourceSesorState::execute() {
  if (millis() > this->lastMillis + DELAY_IN_MILLIS ||
      sensor->GetMoisture() > 0.5) {

    Serial.println("transiting to disable water source state sensor.");
    return new DisableWaterSourceState(sensor);
  }

  return this;
}
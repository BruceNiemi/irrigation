#ifndef DISABLE_WATER_SOURCE_SENSOR_STATE_H_
#define DISABLE_WATER_SOURCE_SENSOR_STATE_H_

#include "moisture_sensor.h"
#include "state.h"

class DisableWaterSourceState : public State {
 private:
  MoistureSensor* sensor;

 public:
  DisableWaterSourceState(MoistureSensor* sensor) : sensor(sensor) {}

  virtual State* execute() override;
};

#endif  //DISABLE_WATER_SOURCE_SENSOR_STATE_H_
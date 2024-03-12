#ifndef ENABLE_WATER_SOURCE_SENSOR_STATE_H_
#define ENABLE_WATER_SOURCE_SENSOR_STATE_H_

#include "moisture_sensor.h"
#include "state.h"

class EnableWaterSourceSesorState : public State {
 private:
  MoistureSensor* sensor;
  unsigned long lastMillis = 0;

 public:
  EnableWaterSourceSesorState(MoistureSensor* sensor) : sensor(sensor) {}
  virtual void enter() override;
  virtual State* execute() override;
    virtual const String name() override { return "Enable Water Source"; };
};
#endif  //ENABLE_WATER_SOURCE_SENSOR_STATE_H_
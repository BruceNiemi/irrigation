#ifndef IDLE_SENSOR_STATE_H_
#define IDLE_SENSOR_STATE_H_

#include "moisture_sensor.h"
#include "state.h"

class IdleSensorState : public State {
 private:
  MoistureSensor* sensor;
  unsigned long lastMillis = 0;

 public:
  IdleSensorState(MoistureSensor* sensor) : sensor(sensor) {}
  virtual void enter() override;
  virtual State* execute() override;
};

#endif  //IDLE_SENSOR_STATE_H_
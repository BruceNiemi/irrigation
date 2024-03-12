#ifndef POLL_SENSOR_STATE_H_
#define POLL_SENSOR_STATE_H_

#include "moisture_sensor.h"
#include "state.h"

class PollSensorState : public State {
 private:
  MoistureSensor* sensor;

 public:
  PollSensorState(MoistureSensor* sensor) : sensor(sensor) {}
  virtual State* execute() override;
  virtual const String name() override { return "Poll Sensor"; };
};

#endif  //POLL_SENSOR_STATE_H_
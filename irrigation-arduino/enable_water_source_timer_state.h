#ifndef ENABLE_WATER_SOURCE_TIMER_H_
#define ENABLE_WATER_SOURCE_TIMER_H_
#include "state.h"

class EnableWaterSourceTimer : public State {
 private:
  unsigned long lastMillis = 0;

 public:
  virtual void enter() override;
  virtual State* execute() override;
  virtual const String name() override { return "Enable Water Source"; };
};

#endif  //ENABLE_WATER_SOURCE_TIMER_H_
#ifndef DISABLE_WATER_SOURCE_TIMER_H_
#define DISABLE_WATER_SOURCE_TIMER_H_
#include "state.h"

class DisableWaterSourceTimer : public State {
 public:
  virtual State* execute() override;
  virtual const String name() override { return "Disable Water Source"; };
};
#endif  // DISABLE_WATER_SOURCE_TIMER_H_
#ifndef DISABLE_WATER_SOURCE_TIMER_H_
#define DISABLE_WATER_SOURCE_TIMER_H_
#include "state.h"

class DisableWaterSourceTimer : public State {
 public:
  virtual State* execute() override;
};
#endif  // DISABLE_WATER_SOURCE_TIMER_H_
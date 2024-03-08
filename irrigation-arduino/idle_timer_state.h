#ifndef IDLE_TIMER_STATE_H_
#define IDLE_TIMER_STATE_H_

#include "state.h"

/**
 * Isolate the two state machines into two isolated components.
*/
class IdleTimerState : public State {
 private:
  unsigned long lastMillis = 0;

 public:
  virtual void enter() override;
  virtual State* execute() override;
};

#endif  //IDLE_TIMER_STATE_H_
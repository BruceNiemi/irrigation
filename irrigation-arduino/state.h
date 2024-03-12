#ifndef STATE_H_
#define STATE_H_
#include <Arduino.h>

/**
 *
 */
class State {
  public:
    virtual ~State(){}
    virtual void enter(){};
    virtual State* execute() = 0;
    virtual const String name() = 0;
};

#endif  // STATE_H_
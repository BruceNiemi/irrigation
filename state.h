#ifndef STATE_H_
#define STATE_H_

/**
 *
 */
class State {
 public:
  /**
   *
   */  
  virtual ~State() {
    // NO-OP
  }

  /**
   *
   */  
  virtual void enter(){
      // NO-OP
  };

  /**
   * @return The pointer to the next state or this current state.
   */
  virtual State* execute() = 0;
};

#endif  // STATE_H_
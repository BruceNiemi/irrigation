#ifndef VALVE_H_
#define VALVE_H_
class Valve {
 private:
  bool valveState;

 public:
  /**
    *  Opens the valve
    */
  void open();
  /**
   * Closes the valve
  */
  void close();

  /**
   * The current state of the valve.
  */
  bool state();
};
#endif  //VALVE_H_
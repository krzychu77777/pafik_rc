#ifndef PAFIK_EVENT_LIB
#define PAFIK_EVENT_LIB

#include "Structs.h"

class Event {
  private:
    CurrentState& state;
    Buffer& buffer;
    Logger& logger;

    int give_prior(ControlSource& src);;

  public:
    Event(CurrentState& currentState, Buffer& raw_buffer, Logger& logger): 
      state(currentState), 
      buffer(raw_buffer), 
      logger(logger) {}

    void run_arbitrage();

    void sterring_state_update();
};

#endif
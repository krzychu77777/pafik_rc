#ifndef PAFIK_EVENT_LIB
#define PAFIK_EVENT_LIB

#include <Arduino.h>
#include "CurrentState.h"
#define LED 2
#define BUTTON_1 4
#define BUTTON_2 5

class Event {
  private:
    static const int buffer_size = 5;
    String event_buffer[buffer_size];
    int it = 0;
    CurrentState& state;

  public:
    Event(CurrentState& currentState) : state(currentState) {}

    void testing_setter(const String (&new_buffer)[buffer_size]);

    void copy_buffer_to(String (&output)[buffer_size]);

    bool available() {return event_buffer[0] != "";}

    void look_for_event();

    void run_arbitrage();

    void sterring_state_update();
};

#endif
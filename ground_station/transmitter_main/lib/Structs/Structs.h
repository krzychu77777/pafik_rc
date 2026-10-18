#ifndef PAFIK_STRUCTS_LIB
#define PAFIK_STRUCTS_LIB

#include "Logger.h"
#include <stdint.h>

enum ControlSource {Controller, Joystick, Keyboard, Undefined, Empty};

enum TaskFamily {Throttle, Steering, Lights, Other};


struct CurrentState {
  public:
    int16_t throttle = 0;
    int16_t steering = 0;
    bool lights = 0;
};

struct Command {
  ControlSource source = Empty;
  TaskFamily type = Other;
  int value = 0;

  Command(
    ControlSource source = Empty,
    TaskFamily type = Other,
    int value = 0
  ) : source(source), type(type), value(value) {}
};

class Buffer {
  private:
    Logger& logger;
  public:
    Buffer(Logger& logger) : logger(logger) {}

    static constexpr int size = 5;
    Command commands[size];
    int last_id = 0;

    bool empty() {
      return last_id==0;
    }

    void push(Command cmd) {
      if (last_id < size) {
        commands[last_id] = cmd;
        last_id++;
      }
      else {
        logger.warning(buffer_exceeded);
      }
    }

    Command pop() {
      if(!empty()) {
        Command output = commands[last_id];
        commands[last_id].source = Empty;
        last_id--;
        return output;
      }
      else {
        logger.error(buffer_already_empty);
      }
    }

    void cleanup() {
      for(int i=0; i<size; i++) {commands[i]=Command{};}
      last_id=0;
    }
};

#endif
#ifndef PAFIK_STRUCTS_LIB
#define PAFIK_STRUCTS_LIB

enum ControlSource {Controller, Joystick, Keyboard, Undefined, Empty};

enum TaskFamily {Movement, Lights, Other};

enum Task {Forward, Backward, Stop};

struct CurrentState {
  public:
    int throttle = 0;
    int steering = 0;
    bool lights = 0;
};

struct Command {
  ControlSource source = Empty;
  TaskFamily type = Other;
  Task task = Stop;
  int value = 0;
};

class Buffer {
  public:
    static constexpr int size = 5;
    Command commands[size];
    int last_id = 0;

    bool empty() {
      if (commands[0].source == Empty) {
        return true;
      }
      return false;
    }

    void push(Command cmd) {
      if (last_id < size-1) {
        commands[last_id] = cmd;
        last_id++;
      }
      else {
        // tu trzeba dodać obsługę wyjątków 
      }
    }

    Command pop() {
      Command output = commands[last_id];
      commands[last_id].source = Empty;
      return output;
    }
};

#endif
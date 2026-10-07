#ifndef PAFIK_STATE_LIB
#define PAFIK_STATE_LIB

struct CurrentState {
  public:
    int throttle = 0;
    int steering = 0;
    bool lights = 0;
};

#endif
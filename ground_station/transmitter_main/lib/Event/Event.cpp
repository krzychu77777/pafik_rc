#include "Event.h"

int Event::give_prior(ControlSource& src) {
  #define Controller_prior 3
  #define Joystick_prior 2
  #define Keyboard_prior 1
  int src_prior = 0;

  if (src==Controller) {
    src_prior = Controller_prior;
  }
  else if (src ==Joystick) {
    src_prior = Joystick_prior;
  }
  else if (src==Keyboard) {
    src_prior = Keyboard_prior;
  }
  else {
    logger.warning(no_priority_for_this_source);
  }
  return src_prior;
}

void Event::run_arbitrage() {
    ControlSource leading_throttle_src = Empty;
    ControlSource leading_steering_src = Empty;
    ControlSource leading_light_src = Empty;

  // ustalanie wiodących źródeł
  for (int i=0; i<buffer.size; i++) {
    
    Command& cmd = buffer.commands[i];

    if (cmd.source == Empty) { continue; }

    switch (cmd.type) {
      case Throttle:
        if (give_prior(cmd.source)>give_prior(leading_throttle_src)) {
          leading_throttle_src = cmd.source;
        }
        else cmd.source = Empty;
        break;
      case Steering:
        if (give_prior(cmd.source)>give_prior(leading_steering_src)) {
          leading_steering_src = cmd.source;
        }
        else cmd.source = Empty;
        break;
      case Lights:
        if (give_prior(cmd.source)>give_prior(leading_light_src)) {
            leading_light_src = cmd.source;
          }
        else cmd.source = Empty;
        break;
      default:
        logger.error(unknown_command);
        break;
    }
  }

  // usunięcie komend niższego priorytetu
  for (int i=0; i<buffer.size; i++) {

    Command& cmd = buffer.commands[i];
    if (cmd.source == Empty) { continue; }

    switch (cmd.type) {
      case Throttle:
        if (cmd.source != leading_throttle_src) {
          cmd.source = Empty; }
        break;
      case Steering:
        if (cmd.source != leading_steering_src) {
          cmd.source = Empty; }
        break;
      case Lights:
        if (cmd.source != leading_light_src) {
          cmd.source = Empty; }
        break;
      default:
        logger.error(unknown_command);
        break;
    }
  }
}

void Event::sterring_state_update() {
  bool isMoving = false;
  bool isSteering = false;

  for (int i=0; i<buffer.size; i++) {

    Command& cmd = buffer.commands[i];

    if (cmd.source != Empty) {
      if (cmd.type == Throttle) {
        state.throttle = cmd.value;
        if (cmd.value != 0) {
          isSteering = true;
        }
      }
      else if (cmd.type == Steering) {
        state.steering = cmd.value;
        if (cmd.value != 0) {
          isSteering = true;
        }
      }
      else if (cmd.type == Lights) {
        state.lights = !state.lights;
        isSteering = true;
      }
    }
  }
  buffer.cleanup();
  
  if (! isSteering) state.throttle = 0;

  if(isSteering) state.override = true;
  else state.override = false;
}
#include "Event.h"

int Event::give_prior(ControlSource& src) {
  #define Controller_prior 3
  #define Joystick_prior 2
  #define Keyboard_prior 1
  int src_prior = 0;

  if (src==Controller) {
    src_prior = Controller_prior;
  }
  else if (src = Joystick) {
    src_prior = Joystick_prior;
  }
  else if (src==Keyboard) {
    src_prior = Keyboard_prior;
  }
  else {
    logger.warning(no_priority_for_this_source);
  }
  return src;
}

void Event::run_arbitrage() {
    ControlSource leading_throttle_source = Empty;
    ControlSource leading_light_source = Empty;

  // ustalanie wiodących źródeł
  for (int i=0; i<buffer.size; i++) {
    
    #define cmd buffer.commands[i]

    if (cmd.source == Empty) { continue; }

    switch (cmd.type) {
      case Movement:
        if (give_prior(cmd.source)>give_prior(leading_throttle_source)) {
          leading_throttle_source = cmd.source;
        }
        else cmd.source = Empty;
        break;
      case Lights:
        if (give_prior(cmd.source)>give_prior(leading_light_source)) {
            leading_throttle_source = cmd.source;
          }
        else cmd.source = Empty;
        break;
      default:
        logger.error(unknown_command);
        break;
    }
  }


  /*
  // ustalanie wiodących źródeł
  for(int i=buffer_size-1; i>=0; i--) {
    if (event_buffer[i]=="\0") {continue;}

    // przyciski pilota 
    if (event_buffer[i][0]=='C') { 
      if (event_buffer[i][1]=='F' || event_buffer[i][1]=='B') {
        leading_throttle_source = 'C';
      }
      else if (event_buffer[i][1]=='L') {
        leading_light_source = 'C';
      }
    }
    // joystick
    else if (event_buffer[i][0]=='J') {
      if (event_buffer[i][1]=='F' || event_buffer[i][1]=='B') {
        leading_throttle_source = 'J';
      }
      else if (event_buffer[i][1]=='L') {
        leading_light_source = 'J';
      }
    }
    // klawiatura
    else if (event_buffer[i][0]=='K') {
      if (event_buffer[i][1]=='F' || event_buffer[i][1]=='B') {
        leading_throttle_source = 'K';
      }
      else if (event_buffer[i][1]=='L') {
        leading_light_source = 'K';
      }
    }
    else {
      Serial.print("Err: błąd arbitrażu, nie rozpoznano komendy");
    }
  }

  // usuwanie sprzecznych sterowań
  for(int i=0; i<buffer_size; i++) {
    if (event_buffer[i][1]=='B' || event_buffer[i][1]=='F') {
      if (event_buffer[i][0]!=leading_throttle_source) {
        event_buffer[i]="\0";
      }
    }
    else if (event_buffer[i][1]=='L') {
      if (event_buffer[i][0]!=leading_light_source) {
        event_buffer[i]="\0";
      }
    }
  } */
}
#include <Arduino.h>
#include "CurrentState.cpp"
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

    void testing_setter(const String (&new_buffer)[buffer_size])
    {
      for (int i = 0; i < buffer_size; i++) {
          event_buffer[i] = new_buffer[i];
      }
    }

    void copy_buffer_to(String (&output)[buffer_size]) {
        for (int i = 0; i < buffer_size; i++) {
          output[i] = event_buffer[i];
      }
    }

    bool available() {
      return event_buffer[0] != "";
    }

    void look_for_event() {
      // źródło 0: proste przyciski   | ozn: C
      if (digitalRead(BUTTON_1) == HIGH) {
        event_buffer[it] = "CF100";   // C(ustom)+F(orward)+throttle
        it++;
      }
      else if (digitalRead(BUTTON_2) == HIGH) {
        event_buffer[it] = "CB100";   // C(ustom)+B(ackward)+throttle
        it++;
      }
      /*
      else if (digitalRead(BUTTON_1) == LOW && digitalRead(BUTTON_2) == LOW && state.throttle != 0) {
        event_buffer[it] = "CS000";   // C(ustom)+S(top)+throttle
        it++;
      }*/

      // tutaj pojawi się skanowanie kolejnych źródeł takich jak joystick, klawiatura itd;
      // wtedy zabezbieczy się też iterator przed wyjściem poza zakres;
      // źródła są decydujące o tym samym są ułożone wg malejącej hierarchii czyli źródła 
      // o wyższej hierarchii zawsze będa w buforze pierwsze

      // źródło 1: joystick         | ozn: J
      //(...)

      // źródło 2: klawiatura       | ozn: K
      //(...)
      
      it = 0;
    }

    void run_arbitrage() {
      char leading_throttle_source = 'E'; // E(mpty)
      char leading_light_source = 'E';

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
      }
    }

    void sterring_state_update() {
    }
};
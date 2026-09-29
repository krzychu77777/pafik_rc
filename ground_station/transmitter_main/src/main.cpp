#include <nRF24L01.h> // te dwie są do 
#include <RF24.h>     // obsługi radia
#include <string.h>
#define LED 2
#define BUTTON_1 4
#define BUTTON_2 5

// obsługa radia nRF24L01
int cnsPin = 8;
int cePin = 7;
RF24 radio(7,8);
const byte address[6] = "00001";

// obsługa eventów
class CurrentState {
  public:
    int throttle = 0;
    int steering = 0;
    bool lights = 0;
};

class Event {
  private:
    static const int buffer_size = 5;
    String event_buffer[buffer_size];
    int it = 0;
    CurrentState& state;

  public:
    Event(CurrentState& currentState) : state(currentState) {}

    bool available() {
      return event_buffer[0] != "";
    }

    void look_for_event() {
      if (digitalRead(BUTTON_1) == HIGH && state.throttle != 1) {
        state.throttle = 1;
        event_buffer[it] = "FWD";
        it++;
      }
      else if (digitalRead(BUTTON_2) == HIGH && state.throttle != -1) {
        state.throttle = -1;
        event_buffer[it] = "BWD";
        it++;
      }
      else if (digitalRead(BUTTON_1) == LOW && digitalRead(BUTTON_2) == LOW && state.throttle != 0) {
        state.throttle = 0;
        event_buffer[it] = "STOP";
        it++;
      }
    }
};

CurrentState state;
Event event(state);

void setup() {
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  delay(3000);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  digitalWrite(LED, LOW);
}

void loop() {
  delay(100);

  const char text[32] = "Hello World";
  radio.write(text, sizeof(text));
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  delay(1000);
}

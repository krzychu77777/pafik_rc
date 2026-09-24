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
pinMode(BUTTON_1, INPUT);
pinMode(BUTTON_2, INPUT);

class CurrentState {
  public:
    int throttle = 0;
    int steering = 0;
    bool lights = 0;
};

class event {
  private:
    int buffer_size = 5;
    String event_buffer[buffer_size];
    int it = 0;

  public:
    bool available() {
      if (event_buffer[0] == "") {
        return 0;
      }
    }

    void look_for_event() {
      if (digitalRead(BUTTON_1) == HIGH && CurrentState.throttle != 1) {
        CurrentState.throttle = 1;
        event_buffer[it] = "FWD";
        it++;
      }
      else if (digitalRead(BUTTON_2) == HIGH && CurrentState.throttle != -1) {
        CurrentState.throttle = -1;
        event_buffer[it] = "BWD";
        it++;
      }
      else if (digitalRead(BUTTON_1) == LOW && digitalRead(BUTTON_2) == LOW && CurrentState.throttle != 0) {
        CurrentState.throttle = 0;
        event_buffer[it] = "STOP";
        it++;
      }
    }
};

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  delay(3000);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  digitalWrite(LED, LOW);

  event Event();
  CurrentState state();
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
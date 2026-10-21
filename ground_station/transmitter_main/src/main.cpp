#include "Event.h"
#include "ArduinoIO.h"

#include <nRF24L01.h> // te dwie są do 
#include <RF24.h>     // obsługi radia
#include <string.h>

#define ERROR_LED 2
#define OK_LED 3

// obsługa radia nRF24L01
int cnsPin = 8;
int cePin = 7;
RF24 radio(7,8);
const byte address[6] = "00001";

// główne instacje klas działających w projekcie
DefaultLogSink logSink;
Logger logger(logSink);
CurrentState state;
Buffer buffer(logger);
Input input(buffer);
Event event(state, buffer, logger);
RadioSession RfSession(state, radio);

// deklaracje przydatnych funkcji z dołu skrytpu
enum led_command {on, off, blink, fast_blink};
void led(uint16_t pin, led_command cmd, uint8_t n);

void setup() {
  Serial.begin(9600); 
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  pinMode(OK_LED, OUTPUT);
  led(OK_LED, on);
  delay(3000);

//   szukanie własnego radia i konfiguracja
//============================================
  if (!radio.begin()) {
    Serial.println("Radio not detected!");
    while (true) {
        delay(1000);
        led(ERROR_LED, blink);
    }
  }
  Serial.println("Radio detected");
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  radio.enableAckPayload();   // włączenie payloadu ACK
  led(OK_LED, off);
  Serial.println("Setup done!");

//            ping od pojazdu
//============================================
  bool connection_estabilished = false;
  while (!connection_estabilished) {
    bool success = RfSession.ping();
      if (success && radio.isAckPayloadAvailable()) {
        BackLog status;
        radio.read(&status, sizeof(status));
        logger.car_response(status);

        Serial.println("Radio connection with Pafik estabilished");
        led(OK_LED, fast_blink, 3);
        connection_estabilished = true;
      }
      else{
        Serial.println("Waiting for Pafik response");
        led(ERROR_LED, blink);
        delay(4000);
      }
  }
}

void loop() {
  input.scan_inputs();
  //tutaj jest arbitraż
  event.sterring_state_update();
  RfSession.send();
  delay(100);
}

void led(uint16_t pin, led_command cmd, uint8_t n=1) {
  switch (cmd) {
    case on:
      digitalWrite(pin, HIGH);
      break;
    case off:
      digitalWrite(pin, LOW);
      break;
    case blink:
      for(int i=0;i<n;i++) {
        digitalWrite(pin, HIGH);
        delay(1000);
        digitalWrite(pin, LOW);
        delay(1000);
      }
      break;
    case fast_blink:
      for(int i=0;i<n;i++) {
        digitalWrite(pin, HIGH);
        delay(500);
        digitalWrite(pin, LOW);
        delay(500);
      }
      break;
    default:
      break;
  }
}

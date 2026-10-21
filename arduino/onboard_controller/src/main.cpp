#include <Arduino.h>
#include <nRF24L01.h> // te dwie są do 
#include <RF24.h>     // obsługi radia
#include <string.h>

#include "Vehicle.h"
#include "Logging.h"
#include "CommCenter.h"

#define MODE 2
#define ERROR_LED 3
#define OK_LED 4

// obsługa radia nRF24L01
int cnsPin = 8;
int cePin = 7;
RF24 radio(7,8);
const byte address[6] = "00001";

// deklaracje przydatnych funkcji z dołu skrytpu
enum led_command {on, off, blink, fast_blink};
void led(uint16_t pin, led_command cmd, uint8_t n);

// główne instacje klas działających w projekcie
Vehicle vehicle;
logBuff log_buffer;
Sink receivers(vehicle, log_buffer);
Logger logger(receivers);
ControlInbox inbox;
CommCenter comms(log_buffer, radio, inbox, vehicle.radio_pipe);

void setup() {
  pinMode(MODE, INPUT);
  pinMode(ERROR_LED, OUTPUT);
  pinMode(OK_LED, OUTPUT);

//   szukanie własnego radia i konfiguracja
//============================================
  if (!radio.begin()) {
    digitalWrite(ERROR_LED, HIGH);
    while (!radio.begin()) {
        delay(1000);
    }
  }
  radio.enableAckPayload();
  radio.openReadingPipe(vehicle.radio_pipe, address);
  radio.setPALevel(RF24_PA_MIN);
  
//      wczytanie trybu sterowania 
//============================================
  if (digitalRead(MODE)==HIGH) {
    vehicle.mode = AUTO;
    Serial.begin(9600);
  }

//        ping od stacji naziemnej 
//============================================
  radio.startListening();
  BackLog hello_world {SETUP, OK};  // log wychodzący "status: ok"
  radio.writeAckPayload(vehicle.radio_pipe, &hello_world, sizeof(hello_world));
  
  while(!radio.available()) {
    delay(100);
  }
  BackLog status_request;           // log przychodzący "czy jest ok?"
  radio.read(&status_request, sizeof(status_request));
  led(OK_LED, fast_blink, 3);
  logger.info(im_ready);
}

uint16_t test_iterator = 0;

void loop() {
  comms.update();
  if (test_iterator % 500) {
    logger.info(pinging);
  }
  if (test_iterator<UINT16_MAX) test_iterator++;
  else test_iterator = 0;
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

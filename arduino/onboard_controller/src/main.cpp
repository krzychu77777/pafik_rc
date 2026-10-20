#include <Arduino.h>
#include <nRF24L01.h> // te dwie są do 
#include <RF24.h>     // obsługi radia
#include <string.h>

#include "Vehicle.h"
#include "Logging.h"

#define MODE 2
#define ERROR_LED 3
#define OK_LED 4

// obsługa radia nRF24L01
int cnsPin = 8;
int cePin = 7;
RF24 radio(7,8);
const byte address[6] = "00001";

// główne instacje klas działających w projekcie
Vehicle vehicle;
logBuff log_buffer;
Sink receivers(vehicle, log_buffer);
Logger logger(receivers);

void setup() {
  pinMode(MODE, INPUT);
  pinMode(ERROR_LED, OUTPUT);
  pinMode(OK_LED, OUTPUT);

  // szukanie własnego radia
  if (!radio.begin()) {
    digitalWrite(ERROR_LED, HIGH);
    while (!radio.begin()) {
        delay(1000);
    }
  }
  
  // wczytanie trybu sterowania 
  if (digitalRead(MODE)==HIGH) {
    vehicle.mode = AUTO;
    Serial.begin(9600);
  }

  // ping od stacji naziemnej 
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  while(!radio.available()) {
    delay(100);
  }
  BackLog hello_world {SETUP, OK};
  BackLog status_request;
  radio.read(&status_request, sizeof(status_request));
  radio.writeAckPayload(1, &hello_world, sizeof(hello_world));
  green_blink(3);
  logger.info(im_ready);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void error_blink(uint8_t n) {
    for(int i=0;i<n;i++) {
    digitalWrite(ERROR_LED, HIGH);
    delay(200);
    digitalWrite(ERROR_LED, LOW);
    delay(200);
  }
}

void green_blink(uint8_t n) {
    for(int i=0;i<n;i++) {
    digitalWrite(OK_LED, HIGH);
    delay(200);
    digitalWrite(OK_LED, LOW);
    delay(200);
  }
}

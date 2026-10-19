#include <Arduino.h>
#include <nRF24L01.h> // te dwie są do 
#include <RF24.h>     // obsługi radia
#include <string.h>

#include "Vehicle.h"
#include "Logging.h"

#define MODE 2
#define ERROR_LED 3

// obsługa radia nRF24L01
int cnsPin = 8;
int cePin = 7;
RF24 radio(7,8);
const byte address[6] = "00001";

// główne instacje klas działających w projekcie
Vehicle vehicle;
Sink receivers(vehicle, radio);
Logger logger(receivers);

void setup() {
  pinMode(MODE, INPUT);
  pinMode(ERROR_LED, OUTPUT);

  if (!radio.begin()) {
    digitalWrite(ERROR_LED, HIGH);
    while (!radio.begin()) {
        delay(1000);
    }
  }
  delay(300);
  Serial.begin(9600);
  if (digitalRead(MODE)) {
    receivers.log(SETUP, status_please);
  }
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  while(!radio.available()) {
    delay(100);
  }
  // i tutaj sprawdzanie czy doszło SETUP | OK

}

void loop() {
  // put your main code here, to run repeatedly:
}

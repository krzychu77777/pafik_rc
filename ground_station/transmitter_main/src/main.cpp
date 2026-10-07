#ifndef GROUND_ST_MAIN

#include "Event.h"

#include <nRF24L01.h> // te dwie są do 
#include <RF24.h>     // obsługi radia
#include <string.h>

// obsługa radia nRF24L01
int cnsPin = 8;
int cePin = 7;
RF24 radio(7,8);
const byte address[6] = "00001";

// obsługa eventów

CurrentState state;
Event event(state);

void setup() {
  Serial.begin(9600); 
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

#endif
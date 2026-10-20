#include "Event.h"
#include "ArduinoIO.h"

#include <nRF24L01.h> // te dwie są do 
#include <RF24.h>     // obsługi radia
#include <string.h>

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

void setup() {
  Serial.begin(9600); 
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  delay(3000);

  if (!radio.begin()) {
    Serial.println("Radio not detected!");
    while (true) {
        delay(1000);
    }
  }
  Serial.println("Radio detected");

  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  radio.enableAckPayload();
  digitalWrite(LED, LOW);
  Serial.println("Setup done!");
  
  bool success = RfSession.ping();
  if (success && radio.isAckPayloadAvailable()) {
    BackLog status;
    radio.read(&status, sizeof(status));
    logger.car_response(status);
    Serial.println("Radio connection with Pafik estabilished");
  }
}

void loop() {
  input.scan_inputs();
  //tutaj jest arbitraż
  event.sterring_state_update();
  RfSession.send();
  delay(100);
}

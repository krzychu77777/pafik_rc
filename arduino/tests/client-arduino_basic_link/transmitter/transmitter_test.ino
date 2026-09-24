#include <nRF24L01.h> // te dwie są do 
#include <RF24.h>     // obsługi radia
#define LED 2

// obsługa radia nRF24L01
int cnsPin = 8;
int cePin = 7;
RF24 radio(7,8);
const byte address[6] = "00001";

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  delay(3000);
  radio.begin();
  //radio.setAutoAck(false);
  //radio.setChannel(108);
  //radio.setPayloadSize(32);
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  digitalWrite(LED, LOW);
}

void loop() {
  const char text[32] = "Hello World";
  radio.write(text, sizeof(text));
  digitalWrite(LED, HIGH);  
  delay(1000);                     
  digitalWrite(LED, LOW);   
  delay(1000); 
}

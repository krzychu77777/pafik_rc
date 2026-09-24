#include <SPI.h>
#include <nRF24L01.h> // te dwie są do 
#include <RF24.h>     // obsługi radia 
#define LED 2

// obsługa radia nRF24L01
int cnsPin = 8;
int cePin = 7;
RF24 radio(cePin, cnsPin);
const byte address[6] = "00001";
char text[32] = "";


void setup() {

  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  delay(1000);
  Serial.println("START");

  if (!radio.begin()) {
    Serial.println("RADIO ERROR");
    while (1) {
      digitalWrite(LED, HIGH);
      delay(100);
      digitalWrite(LED, LOW);
      delay(100);
    }
  }
  Serial.println("RADIO OK");
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  Serial.println("LISTENING");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (radio.available()) {
    char text[32] = "";
    radio.read(text, sizeof(text));
    Serial.println(text);
    digitalWrite(LED, HIGH);  
    delay(1000);                     
    digitalWrite(LED, LOW);   
    delay(900);     
  }
}
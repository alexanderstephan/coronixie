#include <Arduino.h>
#include <ESP8266WiFi.h>

uint8_t currentValue = 0;

#define A 4
#define B 20
#define C 19
#define D 18

const char *ssid = "name";
const char *pass = "password";

WiFiClient client;


void nixieWrite(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t value) {
  // D is most siginificant bit
  digitalWrite(d, (value & 0x08) >> 3);
  digitalWrite(c, (value & 0x04) >> 2);
  digitalWrite(b, (value & 0x02) >> 1);
  digitalWrite(a, value & 0x01);
}

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  delay(10);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Initialize control pins for nixie tube
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);

  // Initial state
  nixieWrite(A, B, C, D, 0);
}

void loop() {
  delay(1000);
  currentValue++;

  currentValue = currentValue % 10;

  nixieWrite(A, B, C, D, currentValue);
}

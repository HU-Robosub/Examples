#include <Arduino.h>
#include <Wire.h>

#define SLAVE_ADDRESS 0x04

int accel_data[3] = {
  10,
  20,
  12
};

void onRequestEvent() {
  Serial.println("Recieved a request!");
  for (int i = 0; i < 3; i++) {
    Wire.write(accel_data[i]);
  }
  Serial.println("Request processed!");
}

void setup() {
  Wire.begin(SLAVE_ADDRESS);
  Serial.begin(9600);
  while (!Serial) {
    delay(3000);
  }
  Serial.println("Initialized Serial");
  Wire.onRequest(onRequestEvent);
  Serial.println("Configured I2C");
}

void loop() {}

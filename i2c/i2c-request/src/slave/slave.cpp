#include <Arduino.h>
#include <Wire.h>

#define SLAVE_ADDRESS 0x05

int reg = 0;

int accel_data[3] = {
  10,
  20,
  12
};
void onReceiveEvent(int numBytes) {
  Serial.println("Recieved a byte!");
  while (Wire.available()) {
    reg = Wire.read();
    Serial.print("Register byte: ");
    Serial.println(reg);
  }
  Serial.println("Request processed!");
}

void onRequestEvent() {
  Serial.println("Recieved a request!");
  if (reg == 0) {
    Serial.println("Sending accel data!");
    for (int i = 0; i < 3; i++) {
      Wire.write(accel_data[i]);
    }
  }
  else if (reg == 1) {
    Serial.println("Sending a 55 byte!");
    Wire.write(55);
  }
  else if (reg == 2) {
    Serial.println("Sending a 66 byte!");
    Wire.write(66);
  }
  else {
    Serial.println("Sending a 80 byte!");
    Wire.write(80);
  }
}

void setup() {
  Wire.begin(SLAVE_ADDRESS);
  Serial.begin(9600);
  while (!Serial) {
    delay(3000);
  }
  Serial.println("Initialized Serial");
  Wire.onRequest(onRequestEvent);
  Wire.onReceive(onReceiveEvent);
  Serial.println("Configured I2C");
}

void loop() {}

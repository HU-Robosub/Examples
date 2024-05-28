#include <Arduino.h>
#include <Wire.h>

#define SLAVE_ADDRESS 0x08

byte TxByte = 0;

void I2C_TxHandler(void)
{
  Wire.write(TxByte);
  TxByte++;
}

void setup() {
  Wire.setPins(33, 32);
  Wire.begin(SLAVE_ADDRESS);
  Serial.begin(9600);
  Wire.onRequest(I2C_TxHandler);
  Serial.println("SLAVE is ready!");
}

void loop() {
  // Nothing yet
}
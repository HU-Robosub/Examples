#include <Arduino.h>
#include <Wire.h>

byte RxByte;

void setup() {
  delay(1000);

  Wire.begin(SDA, SCL);
  Serial.begin(9600);

  Serial.println("MASTER STARTED");
}

void loop()
{
  Wire.requestFrom(0x04, 1);
  while(Wire.available()) {  // Read Received Datat From Slave Device
    RxByte = Wire.read();
  }
  Serial.println(RxByte);
  delay(10);
}
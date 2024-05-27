#include <Arduino.h>
#include <Wire.h>

#define SLAVE_ADDRESS 0x04

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial) {
    delay(3000);
  }
}

void loop() {
  int length = 3;
  Serial.println("Initiated a request!");
  Wire.requestFrom(SLAVE_ADDRESS, length);
  byte answer[length];  // Declare an array to hold the received bytes

  int i = 0;
  while (Wire.available()) {    // While there are bytes available to read
    answer[i++] = Wire.read();  // Read a byte and store it in the array
  }

  Serial.print("The answer: ");
  for (byte b : answer) {  // Loop over each byte in the array
    Serial.print(b, DEC);  // Print the byte value in hexadecimal format
    Serial.print(", ");   // Add a space between values for readability
  }
  Serial.println();
  delay(1000);
}

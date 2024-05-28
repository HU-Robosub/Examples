#include <Arduino.h>
#include <Wire.h>

void sendRequest(int slave, int length, int reg) {
  Serial.println("Sending a register byte!");
  Wire.beginTransmission(slave);
  Wire.write(reg);
  Wire.endTransmission();
  Serial.println("Initiated a request!");
  Wire.requestFrom(slave, length);
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
}

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial) {
    delay(3000);
  }
}

void loop() {
  sendRequest(0x05, 1, 0x02);
  delay(2000);
  Serial.println("Request processed!");
}

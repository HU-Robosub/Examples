#include <Arduino.h>
#include <Wire.h>
int readData = 77;


void sendRequest(int slave, int length, int reg) {
  Serial.println("Sending a register byte!");

  Wire.beginTransmission(slave);
  Wire.write(reg);
  Wire.endTransmission();

  Serial.printf("Register byte sent: %d\n", reg);

  Serial.println("Initiated a request!");
  uint8_t a = Wire.requestFrom(slave, length);
  Serial.println("Request sent!");
  Serial.printf("Request status: %d\n", a);

  while (Wire.available())
  {
    readData = Wire.read();
    Serial.print("Data: ");
    Serial.println(readData);
  }
  // byte answer[length];  // Declare an array to hold the received bytes

  // int i = 0;
  // while (Wire.available()) {    // While there are bytes available to read
  //   answer[i++] = Wire.read();  // Read a byte and store it in the array
  // }

  // Serial.print("The answer: ");
  // for (byte b : answer) {  // Loop over each byte in the array
  //   Serial.print(b, DEC);  // Print the byte value in hexadecimal format
  //   Serial.print(", ");   // Add a space between values for readability
  // }
  // Serial.println();
}

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial)
  {
    delay(3000);
  }
  delay(2000);


  Serial.println("Request processed!");
}

void loop() {
  sendRequest(5, 1, 0);
  sendRequest(5, 1, 1);
  Serial.println("");
  // sendRequest(5, 1, 2);
  delay(2000);
}

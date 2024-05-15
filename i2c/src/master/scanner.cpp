// #include <Arduino.h>
// #include <Wire.h>

// void setup() {
//   delay(1000);
//   // put your setup code here, to run once:
//   Wire.begin(SDA, SCL);
//   Serial.begin(9600);

//   Serial.println("Test");
// }

// void loop()
// {
//   byte error, address;
//   int nDevices;
//   Serial.println("Scanning...");
//   nDevices = 0;
//   for(address = 1; address < 127; address++ )
//   {
//     Wire.beginTransmission(address);
//     error = Wire.endTransmission();
//     if (error == 0)
//     {
//       Serial.print("I2C device found at address 0x");
//       if (address<16)
//       { Serial.print("0"); }
//       Serial.print(address,HEX);
//       Serial.println("  !");
//       nDevices++;
//     }
//     else if (error==4)
//     {
//       Serial.print("Unknown error at address 0x");
//       if (address<16)
//       { Serial.print("0"); }
//       Serial.println(address,HEX);
//     }    
//   }
//   if (nDevices == 0)
//   { Serial.println("No I2C devices found\n"); }
//   else
//   { Serial.println("done\n"); }
//   delay(5000);           // wait 5 seconds for next scan
// }
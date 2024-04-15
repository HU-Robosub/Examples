#include  <Arduino.h>
#include  <Wire.h>
#include <temp.h>

// The adress for the mpu9250 sensor
#define   MPU9250_ADDRESS   0x68

// Configs for gyro and accelerometer ranges
#define   ACC_FULL_SCALE    0x00 //0x00 = 2G, 0x08 = 4G, 0x10 = 8G, 0x18 = 16G
#define   GYRO_FULL_SCALE   0x00 //0x00 = 250dps, 0x08 = 500dps, 0x10 = 1000dps, 0x18 = 2000dps

// Function initialization
void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data);
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data);

void setup()
{
  // Arduino initializations
  Wire.begin();
  Serial.begin(115200);

  delay(1000);

  Serial.println("timestamp, pitch, roll, yaw, speedX, speedY, speedZ");
  
  // Configure gyroscope range
  I2CwriteByte(MPU9250_ADDRESS, 27, GYRO_FULL_SCALE);
  // Configure accelerometers range
  I2CwriteByte(MPU9250_ADDRESS, 28, ACC_FULL_SCALE);
}

void loop() {
  // unsigned long currentMillis = millis();
  // Serial.print (currentMillis);
  // Serial.print ("\t");
 
  // Read accelerometer and gyroscope
  // delay(500);
  uint8_t Buf[14];
  I2Cread(MPU9250_ADDRESS, 0x3B, 14, Buf); 
  
  readSample(Buf);
  printSample();


  // // Accelerometer
  // int16_t ax=-(Buf[0]<<8 | Buf[1]);
  // int16_t ay=-(Buf[2]<<8 | Buf[3]);
  // int16_t az=Buf[4]<<8 | Buf[5];

  // // Gyroscope
  // int16_t gx=-(Buf[8]<<8 | Buf[9]);
  // int16_t gy=-(Buf[10]<<8 | Buf[11]);
  // int16_t gz=Buf[12]<<8 | Buf[13];
  
  // // Display values
  // int data[] = {ax, ay, az, gx, gy, gz};

  // // first three lines are the accelerometer values
  // // the last three lines are the gyroscope values
  // for (int i=0; i<6; i++)
  // {
  //   Serial.print (data[i],DEC);
  //   Serial.print (" ");
  // }

  // // End of line
  // Serial.println("");
  // delay(100);   
}

void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data) {
  //Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.endTransmission();

  // Read Nbytes
  Wire.requestFrom(Address, Nbytes); 
  uint8_t index=0;
  while (Wire.available())
    Data[index++]=Wire.read();
}

void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data)
{
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}
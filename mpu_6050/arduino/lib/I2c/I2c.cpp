#include <Arduino.h>
#include <Wire.h>
// #include <I2C.h>

/**
 * @brief Reads a specified number of bytes from a given I2C device and register.
 * 
 * This function initiates an I2C transmission to a specified device address, sets the register
 * from which the data should be read, and reads a specified number of bytes from it.
 * The read data is stored in the provided buffer.
 * 
 * @param address The I2C address of the device to read from.
 * @param reg The register address to start reading from.
 * @param bytes The number of bytes to read.
 * @param data A pointer to the buffer where the read data should be stored.
 */
void I2Cread(uint8_t address, uint8_t reg, uint8_t bytes, uint8_t* data)
{
  Wire.beginTransmission(address);  // Initiate transmission to the given device address
  Wire.write(reg);                  // Set the register address to start reading from
  Wire.endTransmission();           // End the transmission
  Wire.requestFrom(address, bytes); // Request the specified number of bytes from the device
  
  uint8_t index = 0;
  while (Wire.available()) {        // While there is data available from the device
    data[index++] = Wire.read();    // Read a byte and store it in the data buffer
  }
}

/**
 * @brief Writes a single byte to a given I2C device and register.
 * 
 * This function initiates an I2C transmission to a specified device address, sets the register
 * to which the data should be written, and writes a single byte of data to it.
 * 
 * @param address The I2C address of the device to write to.
 * @param reg The register address where the data should be written.
 * @param data The data byte to write.
 */
void I2CwriteByte(uint8_t address, uint8_t reg, uint8_t data)
{
  Wire.beginTransmission(address); // Initiate transmission to the given device address
  Wire.write(reg);                 // Set the register address to write the data to
  Wire.write(data);                // Write the data byte
  Wire.endTransmission();          // End the transmission
}
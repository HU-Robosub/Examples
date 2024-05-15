#ifndef I2c_h
#define I2c_h

// This function read n bytes (bytes) from I2C device at address (address).
// Put read bytes starting at register (register) in an array (data).
void I2Cread(uint8_t address, uint8_t reg, uint8_t bytes, uint8_t* data);

// Write a byte (data) in device (address) at register (reg)
void I2CwriteByte(uint8_t address, uint8_t reg, uint8_t data);

#endif

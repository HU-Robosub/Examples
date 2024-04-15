#include <Arduino.h>
#include <Wire.h>
#include <cmath>

#define G 9.81375
#define INTERVAL_MS_PRINT 10
#define DEADZONE 0.98

// Setup structs
struct gyroscope_raw {
  int16_t x, y, z;
} gyroscope;

struct accelerometer_raw {
  int16_t x, y, z;
} accelerometer;

struct {
  struct{
    float x, y, z;
  } accelerometer, gyroscope;
} normalized;

struct angle {
  float x, y, z = 0;
};

angle position;

unsigned long lastPrintMillis = 0;
unsigned long lastSampleMicros = 0;

// Normalize functions
void normalize_gyro(gyroscope_raw gyroscope)
{
  normalized.gyroscope.x = gyroscope.x / 32.8; // Why 32.8?
  normalized.gyroscope.y = gyroscope.y / 32.8;
  normalized.gyroscope.z = gyroscope.z / 32.8;
}

void normalize_acc(accelerometer_raw accelerometer)
{
  normalized.accelerometer.x = accelerometer.x * G / 16384; // Why 16384?
  normalized.accelerometer.y = accelerometer.y * G / 16384;
  normalized.accelerometer.z = accelerometer.z * G / 16384;
}

// Calculate functions
angle calculateAccelerometerAngles()
{
  angle accelerometer;

  accelerometer.x = atan(normalized.accelerometer.y / sqrt(sq(normalized.accelerometer.x) + sq(normalized.accelerometer.z)));
  accelerometer.y = atan(-1 * normalized.accelerometer.x / sqrt(sq(normalized.accelerometer.y) + sq(normalized.accelerometer.z)));
  accelerometer.z = atan2(accelerometer.y, accelerometer.x);

  return accelerometer;
}

angle calculateGyroscopeAngles(unsigned long sampleMicros)
{
  angle gyroscope;

  gyroscope.x = normalized.gyroscope.x * sampleMicros / 1000000;
  gyroscope.y = normalized.gyroscope.y * sampleMicros / 1000000;
  gyroscope.z = normalized.gyroscope.z * sampleMicros / 1000000;

  return gyroscope;
}

void detectPitch(angle gyroscope, angle accelerometer)
{
  position.x = DEADZONE * (position.x + degrees(gyroscope.x)) + (1 - DEADZONE) * degrees(accelerometer.x);
}

double getPitch()
{
  return position.x;
}

void detectRoll(angle gyroscope, angle accelerometer)
{
  position.y = DEADZONE * (position.y + degrees(gyroscope.y)) + (1 - DEADZONE) * degrees(accelerometer.y);
}

double getRoll()
{
  return position.y;
}

void detectYaw(angle gyroscope, angle accelerometer)
{
  position.z = DEADZONE * (position.z + degrees(gyroscope.z)) + (1 - DEADZONE) * degrees(accelerometer.z);
}

double getYaw(){
  return position.z;
}

void readRaw(uint8_t buff[14])
{
  //   uint8_t buff[14];

  // Read output registers:
  // [59-64] Accelerometer
  // [65-66] Temperature
  // [67-72] Gyroscope
  // I2Cread(MPU6050_IMU_ADDRESS, 59, 14, buff);
  
  // Accelerometer, create 16 bits values from 8 bits data
  accelerometer.x = (buff[0] << 8 | buff[1]);
  accelerometer.y = (buff[2] << 8 | buff[3]);
  accelerometer.z = (buff[4] << 8 | buff[5 ]);

  // Gyroscope, create 16 bits values from 8 bits data
  gyroscope.x = (buff[8] << 8 | buff[9]);
  gyroscope.y = (buff[10] << 8 | buff[11]);
  gyroscope.z = (buff[12] << 8 | buff[13]);
}

bool readSample(uint8_t buff[14]) {
  readRaw(buff);

  unsigned long sampleMicros = (lastSampleMicros > 0) ? micros() - lastSampleMicros : 0;
  lastSampleMicros = micros();

  normalize_gyro(gyroscope);
  normalize_acc(accelerometer);

  angle accelerometerAngles = calculateAccelerometerAngles();
  angle gyroscopeAngles = calculateGyroscopeAngles(sampleMicros);

  detectPitch(gyroscopeAngles, accelerometerAngles);
  detectRoll(gyroscopeAngles, accelerometerAngles);
  detectYaw(gyroscopeAngles, accelerometerAngles);

  return true;
}

void printSample() {
  if (millis() - lastPrintMillis > INTERVAL_MS_PRINT) {
    Serial.print(millis());
    Serial.print(", ");
    Serial.print(getPitch());
    Serial.print(", ");
    Serial.print(getRoll());
    Serial.print(", ");
    Serial.print(getYaw());
    Serial.print(", ");
    Serial.print(normalized.accelerometer.x);
    Serial.print(", ");
    Serial.print(normalized.accelerometer.y);
    Serial.print(", ");
    Serial.print(normalized.accelerometer.z);
    Serial.println();
    // Serial.printf("%f, %f, %f, %f, %f, %f, %f\n", millis(), getPitch(), getRoll(), getYaw(), normalized.accelerometer.x, normalized.accelerometer.y, normalized.accelerometer.z);

    // Serial.print("Pitch:\t");
    // Serial.print(getPitch());
    // Serial.print("\xC2\xB0"); //Print degree symbol
    // Serial.println();

    // Serial.print("Roll:\t");
    // Serial.print(getRoll());
    // Serial.print("\xC2\xB0"); //Print degree symbol
    // Serial.println();

    // Serial.print("Yaw:\t");
    // Serial.print(getYaw());
    // Serial.print("\xC2\xB0"); //Print degree symbol
    // Serial.println();

    // Serial.print("Speed X:\t");
    // Serial.print(normalized.accelerometer.x);

    // Serial.print("\tSpeed Y:\t");
    // Serial.print(normalized.accelerometer.y);

    // Serial.print("\tSpeed Z:\t");
    // Serial.print(normalized.accelerometer.z);

    // Serial.println();
    lastPrintMillis = millis();
  }
}

#pragma once

#define MPU_6050

#include <SPI.h>
#include <Wire.h>

#ifdef MPU_6050

#include <I2Cdev.h>
#include <MPU6050.h>

#else

#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

#endif


class Sensor
{
  public:

#ifdef MPU_6050
    MPU6050 accelgyro;
#else
    /* Assign a unique ID to this sensor at the same time */
    Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);
#endif

    float ax, ay, az;
    float gx, gy, gz;

    void setupSensor(void);
    bool initSensor(void);
    void readSensor(void);

};


#include "Sensor.h"

void Sensor::setupSensor(void)
{
#ifdef MPU_6050
  // join I2C bus (I2Cdev library doesn't do this automatically)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif
#endif
}

bool Sensor::initSensor(void)
{
#ifdef MPU_6050
  accelgyro.initialize();
  return accelgyro.testConnection();
#else
  return accel.begin();
#endif
}

void Sensor::readSensor(void)
{
#ifdef MPU_6050

  int16_t iax, iay, iaz;
  int16_t igx, igy, igz;

  accelgyro.getMotion6(&iax, &iay, &iaz, &igx, &igy, &igz);

  ax = iax / 2000.0;
  ay = -iay / 2000.0;
  az = iaz / 2000.0;

  gx = igx / 2000.0;
  gy = igy / 2000.0;
  gz = igz / 2000.0;

#else

  sensors_event_t event;
  accel.getEvent(&event);
  ax = event.acceleration.x;
  ay = event.acceleration.y;
  az = event.acceleration.z;
  gx = 0;
  gy = 0;
  gz = 0;

#endif
}





 #define MPU_6050

#include <math.h>
#include <NeoPixelBus.h>
#include <Wire.h>

#ifdef MPU_6050

#include "I2Cdev.h"
#include "MPU6050.h"

#else

#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

#endif

#include "AxisControl.h"
#include "Engine.h"

const uint16_t PixelCount = 6; // this example assumes 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin = 7;  // make sure to set this to the correct pin, ignored for Esp8266

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

#ifdef MPU_6050
MPU6050 accelgyro;
#else
/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);
#endif

int16_t iax, iay, iaz;
int16_t igx, igy, igz;

float ax, ay, az;
float gx, gy, gz;

AxisControl xAxisControl;
AxisControl yAxisControl;
AxisControl zAxisControl;

AxisControl rxAxisControl;
AxisControl ryAxisControl;
AxisControl rzAxisControl;

AxisControl *axisControls[] = {&xAxisControl, &yAxisControl, &zAxisControl, &rxAxisControl, &ryAxisControl, &rzAxisControl};

Engine rearEngine(0, strip);
Engine frontEngine(1, strip);

Engine blEngine(2, strip);
Engine brEngine(3, strip);
Engine trEngine(4, strip);
Engine tlEngine(5, strip);

float frontW[] = {-1,  0,  0,   0, 0, 0};
float rearW[]  = { 1,  0,  0,   0, 0, 0};
float blW[]    = { 0,  1,  1,   0.5, 0, 0};
float brW[]    = { 0, -1,  1,  -0.5, 0, 0};
float tlW[]    = { 0,  1, -1,  -0.5, 0, 0};
float trW[]    = { 0, -1, -1,   0.5, 0, 0};

void setup() {
#ifdef MPU_6050
  // join I2C bus (I2Cdev library doesn't do this automatically)
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
      Wire.begin();
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
      Fastwire::setup(400, true);
  #endif
#endif

  Serial.begin(9600);

  strip.Begin();
  strip.Show();

  setupAcc();

  frontEngine.setControlWeights(frontW, 6);
  rearEngine.setControlWeights(rearW, 6);
  blEngine.setControlWeights(blW, 6);
  brEngine.setControlWeights(brW, 6);
  tlEngine.setControlWeights(tlW, 6);
  trEngine.setControlWeights(trW, 6);
}

void loop() {
  loopAcc();

  // 60 fps
  delay(17);
}

void setupAcc(void) {
  HsbColor red(0.0, 1, 0.5);
  HsbColor green(0.25, 1, 0.5);
  blink(red, 1, 50);
  blink(green, 1, 50);
  
  /* Initialise the sensor */
#ifdef MPU_6050
  accelgyro.initialize();

  if (!accelgyro.testConnection())
#else
  if(!accel.begin())
#endif
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1) {
      blink(red, 1, 250);
    }
  } else {
    blink(green, 1, 50);
    delay(500);

    powerUp();
  }
}

void loopAcc(void) {
#ifdef MPU_6050
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

  xAxisControl.updateWithAcc(ax);
  yAxisControl.updateWithAcc(ay);
  zAxisControl.updateWithAcc(az);

  rxAxisControl.updateWithAcc(gx);
  ryAxisControl.updateWithAcc(gy);
  rzAxisControl.updateWithAcc(gz);

  if (xAxisControl.fwAccDiffSmooth > 1) {
    rearEngine.setBoost(1);
  }

  frontEngine.applyControls(axisControls);
  rearEngine.applyControls(axisControls);
  blEngine.applyControls(axisControls);
  brEngine.applyControls(axisControls);
  trEngine.applyControls(axisControls);
  tlEngine.applyControls(axisControls);
  
  strip.Show();

//  dump();
}

void powerUp() {
  rearEngine.setPower(1);
  frontEngine.setPower(1);
  blEngine.setPower(1);
  brEngine.setPower(1);
  trEngine.setPower(1);
  tlEngine.setPower(1);
}

void blink(HsbColor& col, int count, int delayMs) {
  for (int i = 0; i < count; i++) {
    col.B = 0.5;
    setAllPixels(col);
    delay(delayMs);
    col.B = 0;
    setAllPixels(col);
    delay(delayMs);
  }
}

void setAllPixels(HsbColor& col) {
  for (int i = 0; i < PixelCount; i++) {
    strip.SetPixelColor(i, col);
  }
  strip.Show();
}

void dump() {
//    Serial.print(event.acceleration.x);
//  Serial.print(" ");
//  Serial.print(fwAcc);
//  Serial.print(" ");
//  Serial.print(fwAccDif*100);
//  Serial.print(" ");
//  Serial.print(stationary*100);
//  Serial.print(" ");
//  Serial.print(dStationary*100);
//  Serial.print(" ");
//  Serial.print(fwAccDiffSmooth);
////  Serial.print(" ");
////  Serial.print(vel);
//  Serial.print(" ");
//  Serial.print(throttle);
//  Serial.print(" ");
//  Serial.print(boost);
//  Serial.print(" ");
//  Serial.print(boostF);

//  Serial.print(" ");
//  Serial.print(color1.B);
//  Serial.print(" ");
//  Serial.print(color1.H);

//  Serial.print(" ");

  Serial.print(xAxisControl.throttle * 10);
  Serial.print(" ");
  Serial.print(yAxisControl.throttle * 10);
  Serial.print(" ");
  Serial.print(zAxisControl.throttle * 10);
  
  Serial.print(" ");
  Serial.print(rxAxisControl.throttle * 10);
  
  Serial.println();
}



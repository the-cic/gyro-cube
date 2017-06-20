
#include <math.h>
#include <NeoPixelBus.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

#include "AxisControl.h"
#include "Engine.h"

const uint16_t PixelCount = 6; // this example assumes 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin = 7;  // make sure to set this to the correct pin, ignored for Esp8266

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);

AxisControl xAxisControl;
AxisControl yAxisControl;
AxisControl zAxisControl;

Engine rearEngine(0, strip);
Engine frontEngine(1, strip);

//Engine leftEngine(2, strip);
//Engine rightEngine(3, strip);
//Engine topEngine(4, strip);
//Engine bottomEngine(5, strip);

Engine blEngine(2, strip);
Engine brEngine(3, strip);
Engine trEngine(4, strip);
Engine tlEngine(5, strip);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  strip.Begin();
  strip.Show();

  setupAcc();
}

void loop() {
  // put your main code here, to run repeatedly:

  loopAcc();

  // 60 fps
  delay(17);
}

void setupAcc(void) {
  HsbColor red(0.0, 1, 0.5);
  HsbColor green(0.25, 1, 0.5);
  
  /* Initialise the sensor */
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1) {
      blink(red, 1, 250);
    }
  } else {
    blink(green, 5, 50);
    delay(500);

    powerUp();
  }
}

void loopAcc(void) {
  sensors_event_t event;
  accel.getEvent(&event);

  xAxisControl.updateWithAcc(event.acceleration.x);
  yAxisControl.updateWithAcc(event.acceleration.y);
  zAxisControl.updateWithAcc(event.acceleration.z);

  if (xAxisControl.fwAccDiffSmooth > 1) {
    rearEngine.setBoost(1);
  }

  rearEngine.setThrottle(xAxisControl.throttle);
  frontEngine.setThrottle(-xAxisControl.throttle);
  
//  leftEngine.setThrottle(-yAxisControl.throttle);
//  rightEngine.setThrottle(yAxisControl.throttle);
//  topEngine.setThrottle(zAxisControl.throttle);
//  bottomEngine.setThrottle(-zAxisControl.throttle);
  
  blEngine.setThrottle((-yAxisControl.throttle -zAxisControl.throttle) * 0.5);
  brEngine.setThrottle((yAxisControl.throttle - zAxisControl.throttle) * 0.5);
  trEngine.setThrottle((yAxisControl.throttle + zAxisControl.throttle) * 0.5);
  tlEngine.setThrottle((-yAxisControl.throttle + zAxisControl.throttle) * 0.5);
  
  strip.Show();

  //dump();
}

void powerUp() {
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
  Serial.print(xAxisControl.throttle);
  Serial.print(" ");
  Serial.print(yAxisControl.throttle);
  Serial.print(" ");
  Serial.print(zAxisControl.throttle);
  
  Serial.println();
}



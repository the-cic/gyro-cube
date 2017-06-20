
#include <math.h>
#include <NeoPixelBus.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

const uint16_t PixelCount = 6; // this example assumes 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin = 7;  // make sure to set this to the correct pin, ignored for Esp8266

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);

HsbColor engineColor(0.5, 0.8, 0.1);
HsbColor boostColor(0.05, 1, 1);

float hue = 0.5;
HsbColor color1(hue, 0.8, 0.1);
HsbColor color2(hue, 0.8, 0.1);

float vel;
float fwAcc;
float throttle;
float boost;
float fwAccDiffSmooth;
//float stationary;
//float dStationary;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  fwAcc = 0;
  boost = 0;
  fwAccDiffSmooth = 0;
  vel = 0;
//  stationary = 0;
//  dStationary = 0;

  strip.Begin();
  strip.Show();

  setupAcc();
}

void loop() {
  // put your main code here, to run repeatedly:

  loopAcc();

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
  }
}

void loopAcc(void) {
  sensors_event_t event;
  accel.getEvent(&event);

  float oldFwAcc = fwAcc;
  fwAcc += (event.acceleration.x - fwAcc) * 0.05;
  float fwAccDif = fwAcc - oldFwAcc;

  fwAccDiffSmooth += fwAccDif;
  fwAccDiffSmooth *= 0.7;
  
  vel += fwAccDiffSmooth;
  
  if (fwAccDiffSmooth > 1) {
    //fwAccDiffSmooth = 0;
    boost = 1;
  }

  float boostF = 0;
  if (boost > 0) {
    boost -= 0.05;
    boostF = boost > 0.5 ? 1 : boost * 2;
  } else {
    boost = 0;
  }

  throttle = fwAccDiffSmooth * 0.5 /*+ fwAcc * 0.01*/ + 0.01 * vel;

//  float oldStationary = stationary;
//  float aFwAccDif = abs(fwAccDif);// < 0.001 ? 1 : 0;
//  stationary += aFwAccDif;
//  stationary *= 0.99;
//  dStationary = stationary - oldStationary;

//  Serial.print(event.acceleration.x);
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
  
  color1.B = throttle > 0 ? throttle : 0;
  color2.B = throttle < 0 ? -throttle : 0;
  color1.B += 0.01;
  color2.B += 0.01;
  
  color1.B = (color1.B > 1) ? 1 : color1.B;
  color2.B = (color2.B > 1) ? 1 : color2.B;

  engineColor.B = color1.B;
  color1 = HsbColor::LinearBlend<NeoHueBlendShortestDistance>(engineColor, boostColor, boostF);

//  Serial.print(" ");
//  Serial.print(color1.B);
//  Serial.print(" ");
//  Serial.print(color1.H);
  
//  Serial.println();
  
  strip.SetPixelColor(0, color1);
  strip.SetPixelColor(1, color2);
  strip.Show();
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




#include <math.h>
#include <SPI.h>
#include <NeoPixelBus.h>
#include <Wire.h>

#include "Sensor.h"
#include "AxisControl.h"
#include "Engine.h"
#include "Ship.h"

#define DELAY_60_FPS 17

const uint16_t PixelCount = 6;
const uint8_t PixelPin = 7;

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

Sensor sensor;

AxisControl xAxisControl;
AxisControl yAxisControl;
AxisControl zAxisControl;

AxisControl rxAxisControl;
AxisControl ryAxisControl;
AxisControl rzAxisControl;

AxisControl *axisControls[] = {&xAxisControl, &yAxisControl, &zAxisControl, &rxAxisControl, &ryAxisControl, &rzAxisControl};

Ship ship(strip);

void setup()
{
  sensor.setupSensor();

  Serial.begin(9600);

  strip.Begin();
  strip.Show();

  setupAcc();
}

void loop()
{
  loopAcc();

  delay(DELAY_60_FPS);
}

void setupAcc(void)
{
  HsbColor red(0.0, 1, 0.5);
  HsbColor green(0.25, 1, 0.5);

  if (!sensor.initSensor()) {
    while (1) {
      blink(red, 1, 250);
    }
  } else {
    blink(green, 2, 50);
    delay(500);

    ship.powerUp();
  }
}

void loopAcc(void) {
  sensor.readSensor();

  xAxisControl.updateWithAcc(sensor.ax);
  yAxisControl.updateWithAcc(sensor.ay);
  zAxisControl.updateWithAcc(sensor.az);

  rxAxisControl.updateWithAcc(sensor.gx);
  ryAxisControl.updateWithAcc(sensor.gy);
  rzAxisControl.updateWithAcc(sensor.gz);

  if (xAxisControl.throttleAcc > 0.05) {
    ship.boost();
  }

  ship.applyControls(axisControls);

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





#include "Engine.h"

Engine::Engine(int pixel1, NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> &strip1) {
  pixel = pixel1;
  strip = &strip1;
  engineColor = HsbColor(0.5, 0.8, 0.1);
  boostColor = HsbColor(0.05, 1, 1);
  power = 0;
  powerSetting = 0;
}

void Engine::setThrottle(float throttle)
{
  float boostF = 0;
  if (boost > 0) {
    boost -= 0.05;
    boostF = boost > 0.5 ? 1 : boost * 2;
  } else {
    boost = 0;
  }

  float B = throttle > 0 ? throttle : 0;
  B *= power;
  B += 0.01;
  
  B = (B > 1) ? 1 : B;

  power += (powerSetting - power) * 0.01;

  engineColor.B = B;
  HsbColor color = HsbColor::LinearBlend<NeoHueBlendShortestDistance>(engineColor, boostColor, boostF);

  strip->SetPixelColor(pixel, color);
}

void Engine::setBoost(float boost1)
{
  boost = boost1;
}

void Engine::setPower(float power1)
{
  powerSetting = power1;
}


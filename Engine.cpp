
#include "Engine.h"

Engine::Engine(unsigned short pixel1, NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> &strip1) {
  pixel = pixel1;
  strip = &strip1;
  engineColor = HsbColor(0.5, 0.8, 0.1);
  boostColor = HsbColor(0.05, 1, 1);
  power = 0;
  powerSetting = 0;
  coolOff = 0;
  boost = 0;
}

void Engine::setThrottle(float throttle)
{
  float boostF = 0;
  if (boost > 0) {
    boost -= 0.05;
    boostF = boost > 0.5 ? 1 : boost * 2;
    boostF += sin(boost * 180) * 0.3;
    if (boostF > 1) {
      boostF = 1;
    }
  } else {
    boost = 0;
  }

  float B = throttle > 0 ? throttle : 0;
  B *= power;

  if (B > 0.02) {
    coolOff = 5;
  } else {
    coolOff--;
    if (coolOff > 0) {
      B = 0.02;
    } else {
      B = 0;
    }
  }

  B = (B > 1) ? 1 : B;

  power += (powerSetting - power) * 0.01;

  engineColor.B = B;
  HsbColor color = boostF > 0
                   ? HsbColor::LinearBlend<NeoHueBlendShortestDistance>(engineColor, boostColor, boostF)
                   : engineColor;

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

void Engine::applyControls(AxisControl *controls[])
{
  float totalThrottle = 0;

  for (int i = 0; i < weightsCount; i++) {
    float weight = controlWeights[i] * 0.01;
    totalThrottle += controls[i]->throttle * weight;
  }

  totalThrottle = 1 + log10(totalThrottle * 0.9 + 0.1);

  this->setThrottle(totalThrottle);
}

void Engine::setControlWeights(const short weights[], unsigned short count)
{
  controlWeights = weights;
  weightsCount = count;
}



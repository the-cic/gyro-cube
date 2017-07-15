
#include "Engine.h"

Engine::Engine(char pixel1, NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> &strip1) {
  pixel = pixel1;
  strip = &strip1;
  power = 0;
  powerSetting = 0;
  //  coolOff = 0;
  boost = 0;
}

HsbColor Engine::getEngineColor() {
  static HsbColor c(0.5, 0.8, 0.1);
  return c;
}

HsbColor Engine::getBoostColor() {
  static HsbColor c(0.05, 1, 1);
  return c;
}

void Engine::setThrottle(float throttle)
{
  float boostF = 0;
  if (boost > 0) {
    boost -= 5;
    boostF = boost > 50 ? 1 : boost * 0.02;
    boostF += sin(boost * 1.80) * 0.3;
    if (boostF > 1) {
      boostF = 1;
    }
  } else {
    boost = 0;
  }

  float B = throttle > 0 ? throttle : 0;
  B *= power * 0.01;

  if (B > 0.005) {
    //    coolOff = 5;
  } else {
    //    if (coolOff > 0) {
    //      coolOff--;
    //      B = 0.02;
    //    } else {
    //      B = 0.02;
    //    }
  }

  B = (B > 1) ? 1 : B;

  if (powerSetting != power) {
    power += powerSetting > power ? 5 : -5;
  }

  HsbColor engineColor = getEngineColor();
  engineColor.B = B;
  HsbColor color = boostF > 0
                   ? HsbColor::LinearBlend<NeoHueBlendShortestDistance>(engineColor, getBoostColor(), boostF)
                   : engineColor;

  strip->SetPixelColor(pixel, color);
}

void Engine::setBoost(float boost1)
{
  boost = boost1 * 100;
}

void Engine::setPower(float power1)
{
  powerSetting = power1 * 100;
}

void Engine::applyControls(AxisControl *controls[])
{
  float totalThrottle = 0;

  for (int i = 0; i < weightsCount; i++) {
    float weight = controlWeights[i] * 0.01;
    totalThrottle += controls[i]->throttle * weight;
  }

  //  totalThrottle = 1 + log10(totalThrottle * 0.9 + 0.1);

  this->setThrottle(totalThrottle);
}

void Engine::setControlWeights(signed char weights[], char count)
{
  controlWeights = weights;
  weightsCount = count;
}



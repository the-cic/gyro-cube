
#pragma once

#include <NeoPixelBus.h>
#include <Wire.h>
#include "AxisControl.h"

class Engine 
{
  public:

  Engine(char pixel1, NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> &strip1);

  void setThrottle(float throttle1);
  void setBoost(float boost1);
  void setPower(float power1);
  void applyControls(AxisControl *controls[]);
  void setControlWeights(signed char weights[], char count);

  private:
  
  HsbColor getEngineColor();
  HsbColor getBoostColor();
  
  NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> *strip;
  
  char pixel;
  signed char boost;
  signed char power;
  signed char powerSetting;
  signed char* controlWeights;
  char weightsCount;
  signed char coolOff;

};




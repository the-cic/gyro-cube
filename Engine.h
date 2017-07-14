
#pragma once

#include <NeoPixelBus.h>
#include <Wire.h>
#include "AxisControl.h"

class Engine 
{
  public:

  Engine(unsigned short pixel1, NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> &strip1);

  void setThrottle(float throttle1);
  void setBoost(float boost1);
  void setPower(float power1);
  void applyControls(AxisControl *controls[]);
  void setControlWeights(const short weights[], unsigned short count);

  private:
  
  HsbColor engineColor;
  HsbColor boostColor;
  
  NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> *strip;
  
  unsigned short pixel;
  float boost;
  float power;
  float powerSetting;
  const short* controlWeights;
  unsigned short weightsCount;
  int coolOff;

};

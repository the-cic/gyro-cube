
#include "AxisControl.h"

AxisControl::AxisControl()
{
  acc = 0;
  rawAcc = 0;
  avgAcc = 0;
  throttle = 0;
  rawThrottle = 0;
  throttleAcc = 0;
  fwAcc = 0;
  rwAcc = 0;
  fwDecay = 0;
  rwDecay = 0;
}

void AxisControl::updateWithAcc(float a)
{
  const float decayRate = 0.005;
  
  rawAcc = a / 9.8;
  acc += (rawAcc - acc) * 0.2;
  avgAcc += (acc - avgAcc) * 0.5;

  float nAcc = acc - avgAcc * 0.9;

  if (nAcc > fwAcc) {
    fwAcc = nAcc;
    fwDecay = 0;
  }

  if (-nAcc > rwAcc) {
    rwAcc = -nAcc;
    rwDecay = 0;
  }

  if (fwAcc > 0) {
    fwAcc -= fwDecay;
    fwDecay += decayRate;
  } else {
    fwAcc = 0;
  }

  if (rwAcc > 0) {
    rwAcc -= rwDecay;
    rwDecay += decayRate;
  } else {
    rwAcc = 0;
  }

  rawThrottle = fwAcc - rwAcc;
  throttleAcc = (rawThrottle - throttle) * 0.5;
  throttle += throttleAcc;
}

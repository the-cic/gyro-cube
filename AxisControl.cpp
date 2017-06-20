
#include "AxisControl.h"

AxisControl::AxisControl()
{
  vel = 0;
  fwAcc = 0;
  throttle = 0;
  boost = 0;
  fwAccDiffSmooth = 0;
}

void AxisControl::updateWithAcc(float rawAcc)
{
  float oldFwAcc = fwAcc;
  fwAcc += (rawAcc - fwAcc) * 0.05;
  float fwAccDif = fwAcc - oldFwAcc;

  fwAccDiffSmooth += fwAccDif;
  fwAccDiffSmooth *= 0.7;
  
  vel += fwAccDiffSmooth;
  
  throttle = fwAccDiffSmooth * 0.5 /*+ fwAcc * 0.01*/ + 0.005 * vel;
}

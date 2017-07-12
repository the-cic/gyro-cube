#pragma once

class AxisControl
{  
  public:
  float acc;
  float rawAcc;
  float avgAcc;
  float throttle;
  float rawThrottle;
  float throttleAcc;
  float fwAcc;
  float rwAcc;
  float fwDecay;
  float rwDecay;

  AxisControl();

  void updateWithAcc(float rawAcc);

};



class AxisControl
{  
  public:
  float vel;
  float fwAcc;
  float throttle;
  float boost;
  float fwAccDiffSmooth;

  AxisControl();

  void updateWithAcc(float rawAcc);

};

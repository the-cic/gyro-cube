
#include <NeoPixelBus.h>
#include <Wire.h>

class Engine 
{
  public:

  Engine(int pixel1, NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> &strip1);

  void setThrottle(float throttle1);
  void setBoost(float boost1);
  void setPower(float power1);

  private:
  
  HsbColor engineColor;
  HsbColor boostColor;
  
  NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> *strip;
  
  int pixel;
  float boost;
  float power;
  float powerSetting;

};

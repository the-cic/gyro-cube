
#include "Ship.h"

Ship::Ship(NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> &strip)
{
  for (int i = 0; i < ENGINE_COUNT; i++) {
    engines[i] = new Engine(i, strip);
  }
  
  engines[0]->setControlWeights(rearW, AXIS_COUNT);
  engines[1]->setControlWeights(frontW, AXIS_COUNT);
  engines[2]->setControlWeights(blW, AXIS_COUNT);
  engines[3]->setControlWeights(brW, AXIS_COUNT);
  engines[4]->setControlWeights(trW, AXIS_COUNT);
  engines[5]->setControlWeights(tlW, AXIS_COUNT);
}

void Ship::applyControls(AxisControl *axisControls[])
{
  for (int i = 0; i < ENGINE_COUNT; i++) {
    engines[i]->applyControls(axisControls);
  }
}

void Ship::powerUp()
{
  for (int i = 0; i < ENGINE_COUNT; i++) {
    engines[i]->setPower(1);
  }
}

void Ship::boost()
{
  engines[0]->setBoost(1);
}


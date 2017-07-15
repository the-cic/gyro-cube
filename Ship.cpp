
#include "Ship.h"

Ship::Ship(NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> &strip)
{
  for (int i = 0; i < ENGINE_COUNT; i++) {
    engines[i] = new Engine(i, strip);
  }
  
  engines[0]->setControlWeights(w0, AXIS_COUNT);
  engines[1]->setControlWeights(w1, AXIS_COUNT);
  engines[2]->setControlWeights(w2, AXIS_COUNT);
  engines[3]->setControlWeights(w3, AXIS_COUNT);
  engines[4]->setControlWeights(w4, AXIS_COUNT);
  engines[5]->setControlWeights(w5, AXIS_COUNT);
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


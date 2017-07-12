
#include "Ship.h"

Ship::Ship(NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> &strip)
{
  rearEngine = new Engine(0, strip);
  frontEngine = new Engine(1, strip);

  blEngine = new Engine(2, strip);
  brEngine = new Engine(3, strip);
  trEngine = new Engine(4, strip);
  tlEngine = new Engine(5, strip);

  frontEngine->setControlWeights(frontW, 6);
  rearEngine->setControlWeights(rearW, 6);
  blEngine->setControlWeights(blW, 6);
  brEngine->setControlWeights(brW, 6);
  tlEngine->setControlWeights(tlW, 6);
  trEngine->setControlWeights(trW, 6);
}

void Ship::applyControls(AxisControl *axisControls[])
{
  frontEngine->applyControls(axisControls);
  rearEngine->applyControls(axisControls);
  blEngine->applyControls(axisControls);
  brEngine->applyControls(axisControls);
  trEngine->applyControls(axisControls);
  tlEngine->applyControls(axisControls);
}

void Ship::powerUp()
{
  rearEngine->setPower(1);
  frontEngine->setPower(1);
  blEngine->setPower(1);
  brEngine->setPower(1);
  trEngine->setPower(1);
  tlEngine->setPower(1);
}

void Ship::boost()
{
  rearEngine->setBoost(1);
}


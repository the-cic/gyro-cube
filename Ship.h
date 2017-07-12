
#pragma once

#include <NeoPixelBus.h>
#include <Wire.h>
#include "AxisControl.h"
#include "Engine.h"

class Ship
{
  public:

    Ship(NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> &strip1);

    void applyControls(AxisControl *axisControls[]);

    void powerUp();

    void boost();

    Engine *rearEngine;
    Engine *frontEngine;

    Engine *blEngine;
    Engine *brEngine;
    Engine *trEngine;
    Engine *tlEngine;

    float frontW[6] = { -1,  0,  0,   0, 0, 0};
    float rearW[6]  = { 1,  0,  0,   0, 0, 0};
    float blW[6]    = { 0,  1,  1,   0.5, 0, 0};
    float brW[6]    = { 0, -1,  1,  -0.5, 0, 0};
    float tlW[6]    = { 0,  1, -1,  -0.5, 0, 0};
    float trW[6]    = { 0, -1, -1,   0.5, 0, 0};

};

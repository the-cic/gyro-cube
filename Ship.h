
#pragma once

#include <NeoPixelBus.h>
#include <Wire.h>
#include "AxisControl.h"
#include "Engine.h"

#define ENGINE_COUNT 6
#define AXIS_COUNT 6

class Ship
{
  public:

    Ship(NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> &strip1);

    void applyControls(AxisControl *axisControls[]);

    void powerUp();

    void boost();

    Engine *engines[ENGINE_COUNT];

    signed char rearW[AXIS_COUNT]  = {  100,    0,    0,    0,  0, 0};
    signed char frontW[AXIS_COUNT] = { -100,    0,    0,    0,  0, 0};
    signed char blW[AXIS_COUNT]    = {    0,  100,  100,   50, 0, 0};
    signed char brW[AXIS_COUNT]    = {    0, -100,  100,  -50, 0, 0};
    signed char trW[AXIS_COUNT]    = {    0, -100, -100,   50, 0, 0};
    signed char tlW[AXIS_COUNT]    = {    0,  100, -100,  -50, 0, 0};

};

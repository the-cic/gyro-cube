
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

    // x - forward, y - right, z - up

    signed char w0[AXIS_COUNT] = {  70,   0,   0,    0,   0,  50}; // rear R
    signed char w1[AXIS_COUNT] = {  70,   0,   0,    0,   0, -50}; // rear L
    signed char w2[AXIS_COUNT] = { -70,  70,  70,   50, -50,   0}; // f l
    signed char w3[AXIS_COUNT] = { -70, -70,  70,  -50, -50,   0}; // f r
    signed char w4[AXIS_COUNT] = {   0,  70,  70,   50,  50,   0}; // a l
    signed char w5[AXIS_COUNT] = {   0, -70,  70,  -50,  50,   0}; // a r

};

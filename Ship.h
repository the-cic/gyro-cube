
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

    signed char w0[AXIS_COUNT] = {  100,    0,    0,    0,  0,  0}; // rear
    signed char w1[AXIS_COUNT] = { -100,    0,    0,    0,  0,  0}; // front
    signed char w2[AXIS_COUNT] = {    0,  100,  100,   50,  0,  0}; // b l
    signed char w3[AXIS_COUNT] = {    0, -100,  100,  -50,  0,  0}; // b r
    signed char w4[AXIS_COUNT] = {    0, -100, -100,   50,  0,  0}; // t r
    signed char w5[AXIS_COUNT] = {    0,  100, -100,  -50,  0,  0}; // t l

};

#pragma once
#include "object3d.h"
#include "cube.h"
#include "sphere.h"
#include "wheel.h"
#include "carfronts.h"

class car : public object3d
{
public:
    car();

    void show();
    void hide();
    void privateDraw(bool drawMode) override {}

    object3d* base;
    object3d* container;
    object3d* engine;
    carfronts* frontshape;

    wheel* wheels[4];
    sphere* lights[10];

    void moveX(int x, float t, int dir);
    void reverse(int x, float t);
    void accelerate(int x, float t);
};
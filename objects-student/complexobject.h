#pragma once
#include "object3d.h"
#include "cube.h"
#include "sphere.h"
#include "cylinder.h"

class complexobject : public object3d
{
public:
    complexobject();

    void hide();
    void show();
    void privateDraw(bool drawMode) override {}

    // Head parts
    object3d* sheead;
    object3d* hear;
    object3d* h1;
    object3d* h2;
    object3d* h3;
    object3d* h4;
    object3d* crown;
    object3d* eye1;
    object3d* eye2;
    object3d* mouth;

    // Body
    object3d* body;

    // Arms
    object3d* arm1;
    object3d* arm1c;
    object3d* arm2;
    object3d* arm2c;

    // Legs
    object3d* leg1;
    object3d* leg1c;
    object3d* leg2;
    object3d* leg2c;
};

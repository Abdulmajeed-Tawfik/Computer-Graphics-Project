#pragma once
#include "object3d.h"
#include "cube.h"
#include "sphere.h"
#include "cylinder.h"
#include "sweep.h"
#include "extrusion.h"
#include <vector>
using namespace std;

class WaterPumpStation : public object3d
{
public:
    WaterPumpStation();
    ~WaterPumpStation();

    void show();
    void hide();
    void privateDraw(bool drawMode) override {}

    // ---- Structural parts ----
    object3d* mainBody;         // tall rectangular cabinet
    object3d* topPanel;         // flat roof panel
    object3d* controlPanel;     // angled front panel with buttons
    object3d* buttonRed;
    object3d* buttonGreen;
    object3d* indicatorLight;   // status sphere on top

    // ---- Pipe column ----
    object3d* pipeColumn;       // vertical pipe rising from body
    object3d* pipeElbow;        // elbow joint sphere

    // ---- Extrusion: L-shaped dispensing nozzle ----
    extrusion* nozzle;

    // ---- Sweep: decorative octagonal base ring ----
    sweep* baseRing;

    // ---- Shelf where cup sits ----
    object3d* shelf;

    // ---- Cup (cylinder) ¨C detachable, robot takes it ----
    object3d* cup;

    // ---- Water cubes (5 small cubes fall into cup) ----
    static const int NUM_WATER_CUBES = 5;
    object3d* waterCubes[NUM_WATER_CUBES];

private:
    vector<object3d*> parts;
    void rememberPart(object3d* p);
};

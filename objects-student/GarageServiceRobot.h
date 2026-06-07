#pragma once
#include "object3d.h"
#include "cube.h"
#include "sphere.h"
#include "cylinder.h"
#include "sweep.h"
#include "extrusion.h"
#include <vector>
using namespace std;

class GarageServiceRobot : public object3d
{
public:
    GarageServiceRobot();
    ~GarageServiceRobot();

    void show();
    void hide();
    void privateDraw(bool drawMode) override {}

    // Main body parts
    object3d* body;         // main torso
    object3d* head;         // head on top
    object3d* eyeLeft;
    object3d* eyeRight;
    object3d* antenna;      // antenna on head

    // Wheels (4 wheels for movement)
    object3d* wheelFL;
    object3d* wheelFR;
    object3d* wheelBL; 
    object3d* wheelBR;

    // Right arm (delivery arm)
    object3d* shoulderR;
    object3d* upperArmR;
    object3d* lowerArmR;
    object3d* hand;         // gripper - cup attaches here

    // Left arm
    object3d* shoulderL;
    object3d* upperArmL;
    object3d* lowerArmL;

    // Sweep: wrist detail band on right arm
    sweep* wristBandR;
	sweep* wristBandL;

    // Extrusion: chest emblem plate
    extrusion* chestPlate;

    // Screen on body front
    object3d* bscreen;
    object3d* windshield;
    object3d* fscreen;

private:
    vector<object3d*> parts;
    void rememberPart(object3d* p);
};

#ifndef _GarageServiceRobot_H
#define _GarageServiceRobot_H

#include "object3d.h"
#include "cube.h"
#include "sphere.h"
#include "cylinder.h"
#include "torus.h"
#include "texture.h"

#include <vector>

class GarageServiceRobot : public object3d
{
private:
    // Main robot parts
    cube* body;
    cube* head;
    cube* screen;
    cube* windshield;

    // Face
    sphere* leftEye;
    sphere* rightEye;

    // Wheels
    torus* frontLeftWheel;
    torus* frontRightWheel;
    torus* backLeftWheel;
    torus* backRightWheel;

    // Carrying tray and water pump package
    cube* tray;
    cylinder* pumpBody;
    sphere* pumpCapLeft;
    sphere* pumpCapRight;

    // Robot arms
    cylinder* leftArm;
    cylinder* rightArm;
    cylinder* inileftArm;
    cylinder* inirightArm;
    sphere* leftHand;
    sphere* rightHand;

    // Antenna
    cylinder* antennaPole;
    sphere* antennaBall;

    // Store all child objects so hide/show affects every child
    std::vector<object3d*> parts;

    void rememberPart(object3d* part);

public:
    GarageServiceRobot();
    virtual ~GarageServiceRobot();

    // Required by assignment
    virtual void hide(void);
    virtual void show(void);

    // Parent object itself has no visible geometry
    virtual void privateDraw(bool drawMode);

    // Animation methods
    void drive(float time);
    void spinWheels(float time);
    void waveArm(float time);
    void blinkScreen(float time);
    void waveAntenna(float time);

    // Texture helper methods
    void setScreenTexture(texture* t);
    void setCargoTexture(texture* t);
};

#endif
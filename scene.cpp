// *****************************************************************************************
// KXC354 - Computer Graphics & Animation - 2014
// Assignment 1 & 2
// 3D Engine Code
// *****************************************************************************************
//
// Author: Tony Gray
//
// scene.cpp



// -----------------------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------------------
#include "prefix.h"
#include "constants.h"			// system-wide constants
#include "utility.h"			// general utility functions
#include "light.h"
#include "camera.h"
#include "texture.h"
#include "scene.h"
#include "snd.h"
#include "skybox.h"
#include "fog.h"
#include "viewfrustum.h"


// #includes for geometry
#include "sweep.h"
#include "extrusion.h"
#include "cube.h"
#include "sphere.h"
#include "torus.h"
#include "terrain.h"
#include "billboard.h"
#include "plane.h"
#include "tsphere.h"
#include "cylinder.h"
#include "disc.h"
#include "GarageServiceRobot.h"
#include "WaterPumpStation.h"
#include "car.h"
#include "complexobject.h"
#include "Chair.h"
#include "tcube.h"

// -----------------------------------------------------------------------------------------
// global variables
// -----------------------------------------------------------------------------------------
extern ProgramMode		gProgramMode;							// initially, we're not animating

extern cameraClass		gCamera;								// the camera
extern object3d* gSky;									// the global skybox
extern fog* gFog;									// the global fog
extern viewfrustum* gViewFrustum;							// the global view frustum object
extern float			gCurrentFrameTime;						// the time that the current animation frame was started

extern vector<object3d*> gShapeVector;
typedef vector<object3d*>::iterator shapeVectorIterator;






// -----------------------------------------------------------------------------------------
// variables that represent 3D objects being used in the animation
// -----------------------------------------------------------------------------------------
// these are really global variables, but you shouldn't need to access them from anywere
// except in this file 
// -----------------------------------------------------------------------------------------

// pointer of shapes defined here




// some lights
light* ambient, * light0, * light1, * light2;
GarageServiceRobot* robot;
WaterPumpStation* pumpStation;
car* truck;
complexobject* human;
Chair* set;
object3d* garageFloor;
object3d* wallBack;
object3d* wallLeft;
object3d* wallRight;
object3d* hole;
tcube* Boxes[14];
texture* boxTexture;
// -----------------------------------------------------------------------------------------
// constructScene
// -----------------------------------------------------------------------------------------
// This function constructs the objects required for the animation.  It is only called once
// when the program is first run.
// Use this to create child objects and bind them to their parents.
// -----------------------------------------------------------------------------------------

void constructScene()
{
	ambient = new light(GL_LIGHT_MODEL_AMBIENT);
	light0 = new light(GL_LIGHT0);
	light1 = new light(GL_LIGHT1);

	
    // ====== CREATE FULL GARAGE ROOM ======
// 1. Concrete Garage Floor (big ground surface for all objects to stand on)
    // Re-corrected Garage in constructScene()
 /*floor (big full ground for entire garage)*/
    garageFloor = new cube();
    garageFloor->setPosition(0, -0.25f, 0);
    garageFloor->setDeformation(24, 0.5f, 20);
    garageFloor->setColour(0.32f, 0.32f, 0.35f, 1);
    gShapeVector.push_back(garageFloor);        
    // 1. BACK WALL (Z = -10 → closes rear side of garage)
    wallBack = new cube();
	wallBack->setParent(garageFloor); // make back wall a child of the floor
    wallBack->setPosition(0.0f, 7.7f, -19.7f);
    wallBack->setDeformation(24, 7.2f, 0.3f);
    wallBack->setColour(0.82f, 0.80f, 0.75f, 1);
    gShapeVector.push_back(wallBack);

 //   // 2. LEFT WALL (X=-11.8 → left edge garage)
    wallLeft = new cube();
	wallLeft->setParent(garageFloor); // make left wall a child of the floor
    wallLeft->setPosition(-23.7f, 7.7f, 0);
    wallLeft->setDeformation(0.3f, 7.2f, 20);
    wallLeft->setColour(0.82f, 0.80f, 0.75f, 1);
    gShapeVector.push_back(wallLeft);

 //   //3. RIGHT WALL (X=+11.8 → right edge garage)
    wallRight = new cube();
	wallRight->setParent(garageFloor); // make right wall a child of the floor
    wallRight->setPosition(23.7f, 7.7f, 0);
    wallRight->setDeformation(0.3f, 7.2f, 20);
    wallRight->setColour(0.82f, 0.80f, 0.75f, 1);
    gShapeVector.push_back(wallRight);

	boxTexture = new texture("NO1.bmp");

    for (int i = 0; i < 14; i++)
    {
		Boxes[i] = new tcube();
		Boxes[i]->setParent(garageFloor);
		/*Boxes[i]->setPosition(-10 + i * 1.5f, 0.25f, -5);*/
		Boxes[i]->setDeformation(1.5f, 1.5f, 1.5f);
        Boxes[i]->setTexture(boxTexture);   
    }

	Boxes[0]->setPosition(21.9, 2.0f, -17.9);
    Boxes[1]->setPosition(21.9, 2.0f, -14.9);
    Boxes[2]->setPosition(21.9, 2.0f, -11.9);
    Boxes[3]->setPosition(18.8, 2.0f, -17.9);
    Boxes[4]->setPosition(18.8, 2.0f, -14.9);
    Boxes[5]->setPosition(18.8, 2.0f, -11.9);
    Boxes[6]->setPosition(15.7, 2.0f, -17.9);
    Boxes[7]->setPosition(15.7, 2.0f, -14.9);
    Boxes[8]->setPosition(15.7, 2.0f, -11.9);
    Boxes[9]->setPosition(21.9, 5.0f, -17.9);
    Boxes[10]->setPosition(21.9, 5.0f, -14.9);
    Boxes[11]->setPosition(18.8, 5.0f, -17.9);
    Boxes[12]->setPosition(18.8, 5.0f, -14.9);
    Boxes[13]->setPosition(21.7, 8.0f, -17.9);

	hole = new cube();
	hole->setParent(garageFloor);
	hole->setPosition(-16.1, 0.55f, -3);
	hole->setDeformation(1.5, 0.05f, 10);
	hole->setColour(0.82f, 0.80f, 0.75f, 1);
       
    // NEW: FRONT WALL (add this to fully close garage box, positive Z side)
    /*object3d* wallFront = new cube();
    wallFront->setPosition(0, 3.6f, 9.5f);
    wallFront->setDeformation(24, 7.2f, 0.3f);
    wallFront->setColour(0.82f, 0.80f, 0.75f, 1);
    gShapeVector.push_back(wallFront);*/


    robot = new GarageServiceRobot();
	robot->setParent(garageFloor);
	robot->setPosition(8, 1.0, 15);
	robot->setRotation('y', 180.0f); // Rotate robot to face forward (Z-axis)
    pumpStation = new WaterPumpStation();
	pumpStation->setParent(garageFloor);
	pumpStation->setPosition(21.3, 1.0, -5);
	pumpStation->setRotation('y', 90.0f); // Rotate pump station to face forward (Z-axis)
    truck = new car();
    truck->setParent(garageFloor);
    truck->setPosition(-16, 2.6, 18);
    truck->setRotation('y', 90.0f); // Rotate truck to face forward (Z-axis)
    human = new complexobject();
	human->setParent(garageFloor);
    human->setPosition(-10.0, 0.36, -12.0);
    human->setRotation('y', -45.0);
    set = new Chair();
    set->setParent(garageFloor);    
    set->setPosition(22.1,1.5,17.0);
    set->setRotation('y', -90.0f);

}




// -----------------------------------------------------------------------------------------
// resetScene
// -----------------------------------------------------------------------------------------
// This function is called whenever the animation is restarted.  Use it to reset objects
// to their starting position or size, or to reset any aspects of the objects that
// might have been altered during an animation sequence.
// -----------------------------------------------------------------------------------------

void resetScene()
{
    // Camera
    gCamera.setPosition(0, 15, 60);
    gCamera.setTarget(0.0, 0.0, 2.0);

    // Lights
    ambient->setColour(0.5, 0.5, 0.5, 1.0);

    light0->turnOn();
    light0->setPosition(-10, 10, 5);
    light0->setColour(0.7, 0.7, 0.7, 1.0);
    light0->setSpecularColour(0.7, 0.7, 0.7, 1.0);
    light0->makePositional();
    light0->setLinearAttenuation(0.1);

    light1->turnOn();
    light1->setPosition(10, 10, -5);
    light1->setColour(0.7, 0.7, 0.7, 1.0);
    light1->setSpecularColour(0.7, 0.7, 0.7, 1.0);
    light1->makePositional();
    light1->setLinearAttenuation(0.1);

    // ✅ ROBOT STARTS AT THE BACK (Z-axis) to drive forward
    /*robot->setPosition(0.0f, 0.0f, 8.0f);
    robot->show();

    pumpStation->setPosition(0, 0, -4);
    pumpStation->show();*/


    //// 1: Pump station stays at back wall side
    //pumpStation->setPosition(0, 0, -7);

    ////2: Truck parked left side near left wall
   // truck->setPosition(-7, 0, 2);

    ////3: Chair next to truck
    //set->setPosition(-5.2f, 0, 2.2f);

    ////4: Human start standing beside truck (0s will walk to chair)
    //human->setPosition(-6.5f, 0, 2);

    ////5: Robot starting idle position (middle garage space far from pump)
    //robot->setPosition(0, 0, 7);
}



// -----------------------------------------------------------------------------------------
// animateForNextFrame
// -----------------------------------------------------------------------------------------
// This function is called to animate objects ready for the next frame
// -----------------------------------------------------------------------------------------

void animateForNextFrame(float time, long frame)
{
    //Activate all robot animation logic
    robot->drive(time);
    robot->spinWheels(time);
    robot->waveArm(time);
    robot->blinkScreen(time);
    robot->waveAntenna(time);

    pumpStation->moveScanner(time);
    pumpStation->openCover(time);
    pumpStation->rotateImpeller(time);
    pumpStation->flashWarningLight(time);

    if (time < 12)
    {
        float t = time / 12.0f; // normalize time 0→1 over 12s

        // Z axis movement: original camera Z (from 15 →7 as before)
        float camZ = 20 - t * 8.0f;
        // X axis movement: swing camera RIGHT then LEFT (or gradual right→left)
        // Option A: Start on RIGHT(X=4) → slowly move to LEFT(X=-4) over 12s
        float camX = 4.0f - t * 8.0f;
        // Camera position: X(changing left/right), Y fixed=4, Z(changing forward/back)
        gCamera.setPosition(camX, 4, camZ);
        // Keep target fixed at robot final spot (machine position Z=-2), always look at robot
        gCamera.setTarget(0, 1, -1.2);
    }
    else if (time >= 16 && time < 28)
    {
        // Zoom in on the test station
        float camX = 0 + sin_d((time - 16) * 45) * 1.5;
        float camY = 4 - ((time - 16) / 12.0f) * 2;
        float camZ = 2;
        gCamera.setPosition(camX, camY, camZ);
        gCamera.setTarget(0, 1, -4);
    }
    else if (time >= 35)
    {
        // Pull back to show the celebration
        float camZ = 2 + ((time - 35) / 5.0f) * 3;
        gCamera.setPosition(0, 2, camZ);
        gCamera.setTarget(0, 1, -2);
    }
    /* [keep all your original scene animation code here if any]
     Stop animation at 40 seconds*/
    if (time < 12)
    {
        float t = time / 12.0f; // normalize time 0→1 over 12s

        // Z axis movement: original camera Z (from 15 →7 as before)
        float camZ = 20 - t * 8.0f;
        // X axis movement: swing camera RIGHT then LEFT (or gradual right→left)
        // Option A: Start on RIGHT(X=4) → slowly move to LEFT(X=-4) over 12s
        float camX = 4.0f - t * 8.0f;
        // Camera position: X(changing left/right), Y fixed=4, Z(changing forward/back)
        gCamera.setPosition(camX, 4, camZ);
        // Keep target fixed at robot final spot (machine position Z=-2), always look at robot
        gCamera.setTarget(0, 1, -1.2);
    }
    else if (time >= 16 && time < 28)
    {
        // Zoom in on the test station
        float camX = 0 + sin_d((time - 16) * 45) * 1.5;
        float camY = 4 - ((time - 16) / 12.0f) * 2;
        float camZ = 2;
        gCamera.setPosition(camX, camY, camZ);
        gCamera.setTarget(0, 1, -4);
    }
    else if (time >= 35)
    {
        // Pull back to show the celebration
        float camZ = 2 + ((time - 35) / 5.0f) * 3;
        gCamera.setPosition(0, 2, camZ);
        gCamera.setTarget(0, 1, -2);
    }
    /* [keep all your original scene animation code here if any]
     Stop animation at 40 seconds*/


    if (time >= 40.0f)
    {
        gProgramMode = kpmFinished;
    }
}





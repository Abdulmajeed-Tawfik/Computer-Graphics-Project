// *****************************************************************************************
// KXC354 - Computer Graphics & Animation
// scene.cpp  –  Garage / Auto-Repair Service Story
// *****************************************************************************************

#include "prefix.h"
#include "constants.h"
#include "utility.h"
#include "light.h"
#include "camera.h"
#include "texture.h"
#include "scene.h"
#include "snd.h"
#include "skybox.h"
#include "fog.h"
#include "viewfrustum.h"

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
#include "car.h"          // car, wheel, carfronts all declared here
#include "complexobject.h"// all child parts (arm1, leg1 etc) declared public here
#include "Chair.h"
#include "tcube.h"

// -----------------------------------------------------------------------------------------
// Externals
// -----------------------------------------------------------------------------------------
extern ProgramMode      gProgramMode;
extern cameraClass      gCamera;
extern object3d* gSky;
extern fog* gFog;
extern viewfrustum* gViewFrustum;
extern float            gCurrentFrameTime;
extern vector<object3d*> gShapeVector;
typedef vector<object3d*>::iterator shapeVectorIterator;

// -----------------------------------------------------------------------------------------
// Scene objects
// -----------------------------------------------------------------------------------------
//light* ambient, * light0, * light1;

// Environment
object3d* garageFloor;
object3d* wallBack;
object3d* wallLeft;
object3d* wallRight;
object3d* hole;
tcube* Boxes[14];
texture* boxTexture;

// Characters / props
GarageServiceRobot* robot;
WaterPumpStation* pumpStation;
car* truck;
complexobject* human;
Chair* chairObj;  
// -----------------------------------------------------------------------------------------
// Animation state variables
// -----------------------------------------------------------------------------------------

// --- Truck ---
// Truck starts outside (large +Z) and drives to stop over hole at Z≈-3
// In garage space the truck is rotated 90° Y so its local X maps to world Z
static const float TRUCK_START_Z = 40.0f;   // world Z start (outside garage)
static const float TRUCK_STOP_Z = -3.0f;   // world Z stop  (over hole)
static const float TRUCK_X = -16.0f;   // world X lane (matches hole X)

// --- Human walk ---
// Human appears at truck cab door position, walks to chair
static const float HUMAN_START_X = -13.5f;
static const float HUMAN_START_Z = 16.0f;
static const float HUMAN_END_X = 22.1f;   // chair X (world)
static const float HUMAN_END_Z = 17.0f;   // chair Z (world)

// --- Robot drive to pump ---
// Robot starts at (8, ?, 15) world, pump at (21.3, ?, -5) world
static const float ROBOT_START_X = 8.0f;
static const float ROBOT_START_Z = 15.0f;
static const float ROBOT_PUMP_X = 17.3f;   // stop in front of pump shelf
static const float ROBOT_PUMP_Z = -3.0f;

// --- Robot carry cup to human ---
static const float ROBOT_HUMAN_X = 20.5f;   // stop in front of chair
static const float ROBOT_HUMAN_Z = 17.0f;

// Cup transfer flag
static bool cupAttachedToRobot = false;
static bool cupDelivered = false;
static bool humanHiding = true;          // human hidden until truck stops

// -----------------------------------------------------------------------------------------
// Helpers
// -----------------------------------------------------------------------------------------
static float smoothStep(float t)
{
    // classic cubic smoothstep 0→1
    if (t <= 0.0f) return 0.0f;
    if (t >= 1.0f) return 1.0f;
    return t * t * (3.0f - 2.0f * t);
}

static float lerp(float a, float b, float t)
{
    return a + (b - a) * t;
}

// -----------------------------------------------------------------------------------------
// constructScene
// -----------------------------------------------------------------------------------------




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
tcube* cb;
texture* box;


// some lights
light* ambient, * light0, * light1, * light2;



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

    // ------------------------------------------------------------------
    // GARAGE FLOOR  (parent of all environment pieces)
    // ------------------------------------------------------------------
    garageFloor = new cube();
    garageFloor->setPosition(0.0f, -0.25f, 0.0f);
    garageFloor->setDeformation(24.0f, 0.5f, 20.0f);
    garageFloor->setColour(0.30f, 0.30f, 0.32f, 1.0f);
    gShapeVector.push_back(garageFloor);

    // BACK WALL
    wallBack = new cube();
    wallBack->setParent(garageFloor);
    wallBack->setPosition(0.0f, 7.7f, -19.7f);
    wallBack->setDeformation(24.0f, 7.2f, 0.3f);
    wallBack->setColour(0.82f, 0.80f, 0.75f, 1.0f);
    gShapeVector.push_back(wallBack);

    // LEFT WALL
    wallLeft = new cube();
    wallLeft->setParent(garageFloor);
    wallLeft->setPosition(-23.7f, 7.7f, 0.0f);
    wallLeft->setDeformation(0.3f, 7.2f, 20.0f);
    wallLeft->setColour(0.82f, 0.80f, 0.75f, 1.0f);
    gShapeVector.push_back(wallLeft);

    // RIGHT WALL
    wallRight = new cube();
    wallRight->setParent(garageFloor);
    wallRight->setPosition(23.7f, 7.7f, 0.0f);
    wallRight->setDeformation(0.3f, 7.2f, 20.0f);
    wallRight->setColour(0.82f, 0.80f, 0.75f, 1.0f);
    gShapeVector.push_back(wallRight);

    // SERVICE PIT / HOLE
    hole = new cube();
    hole->setParent(garageFloor);
    hole->setPosition(-16.1f, 0.55f, -7.0f);
    hole->setDeformation(1.5f, 0.05f, 6.0f);
    hole->setColour(0.10f, 0.10f, 0.10f, 1.0f);  // dark pit
    gShapeVector.push_back(hole);

    // STORAGE BOXES (right-back corner)
    boxTexture = new texture("NO1.bmp");
    for (int i = 0; i < 14; i++)
    {
        Boxes[i] = new tcube();
        Boxes[i]->setParent(garageFloor);
        Boxes[i]->setDeformation(1.5f, 1.5f, 1.5f);
        Boxes[i]->setTexture(boxTexture);
    }
    Boxes[0]->setPosition(21.9f, 2.0f, -17.9f);
    Boxes[1]->setPosition(21.9f, 2.0f, -14.9f);
    Boxes[2]->setPosition(21.9f, 2.0f, -11.9f);
    Boxes[3]->setPosition(18.8f, 2.0f, -17.9f);
    Boxes[4]->setPosition(18.8f, 2.0f, -14.9f);
    Boxes[5]->setPosition(18.8f, 2.0f, -11.9f);
    Boxes[6]->setPosition(15.7f, 2.0f, -17.9f);
    Boxes[7]->setPosition(15.7f, 2.0f, -14.9f);
    Boxes[8]->setPosition(15.7f, 2.0f, -11.9f);
    Boxes[9]->setPosition(21.9f, 5.0f, -17.9f);
    Boxes[10]->setPosition(21.9f, 5.0f, -14.9f);
    Boxes[11]->setPosition(18.8f, 5.0f, -17.9f);
    Boxes[12]->setPosition(18.8f, 5.0f, -14.9f);
    Boxes[13]->setPosition(21.7f, 8.0f, -17.9f);

    // ------------------------------------------------------------------
    // CHARACTERS & PROPS
    // ------------------------------------------------------------------

    // TRUCK  (starts outside the garage, will drive in during animation)
    truck = new car();
    truck->setParent(garageFloor);
    truck->setPosition(TRUCK_X, 2.6f, TRUCK_START_Z);
    truck->setRotation('y', 90.0f);

    // HUMAN  (hidden until truck stops)
    human = new complexobject();
    human->setParent(garageFloor);
    human->setPosition(HUMAN_START_X, 0.36f, HUMAN_START_Z);
    human->setRotation('y', -90.0f);
    human->hide();

    //// CHAIR
    chairObj = new Chair();
    chairObj->setParent(garageFloor);
    chairObj->setPosition(22.1f, 1.5f, 17.0f);
    chairObj->setRotation('y', -90.0f);

    //// ROBOT  (starts mid-garage, facing front)
    robot = new GarageServiceRobot();
    robot->setParent(garageFloor);
    robot->setPosition(ROBOT_START_X, 1.0f, ROBOT_START_Z);
    robot->setRotation('y', 180.0f);

    //// PUMP STATION  (right wall, facing inward)
    pumpStation = new WaterPumpStation();
    pumpStation->setParent(garageFloor);
    pumpStation->setPosition(21.3f, 1.0f, -5.0f);
    pumpStation->setRotation('y', -90.0f);

    
}

// -----------------------------------------------------------------------------------------
// resetScene
// -----------------------------------------------------------------------------------------
void resetScene()
{
    // Camera: wide exterior shot looking into garage entrance
    gCamera.setPosition(0.0f, 5.0f, -8.0f);
    gCamera.setTarget(ROBOT_START_X, 1.0f, ROBOT_START_Z);
    
   /*gCamera.setPosition(TRUCK_X, 6.0f, 55.0f);
    gCamera.setTarget(TRUCK_X, 2.0f, 0.0f);*/

    // Lights
    ambient->setColour(0.40f, 0.40f, 0.40f, 1.0f);

    light0->turnOn();
    light0->setPosition(-8.0f, 12.0f, 5.0f);
    light0->setColour(0.75f, 0.75f, 0.75f, 1.0f);
    light0->setSpecularColour(0.75f, 0.75f, 0.75f, 1.0f);
    light0->makePositional();
    light0->setLinearAttenuation(0.04f);

    light1->turnOn();
    light1->setPosition(14.0f, 12.0f, -5.0f);
    light1->setColour(0.65f, 0.65f, 0.65f, 1.0f);
    light1->setSpecularColour(0.65f, 0.65f, 0.65f, 1.0f);
    light1->makePositional();
    light1->setLinearAttenuation(0.04f);

    // Reset truck position to outside
    truck->setPosition(TRUCK_X, 2.6f, TRUCK_START_Z);
    truck->setRotation('y', 90.0f);

    // Reset human
    human->setPosition(HUMAN_START_X, 0.36f, HUMAN_START_Z);
    human->setRotation('y', -90.0f);
    human->hide();
    humanHiding = true;

    // Reset robot
    robot->setPosition(ROBOT_START_X, 1.0f, ROBOT_START_Z);
    robot->setRotation('y', 180.0f);
    robot->upperArmR->setRotation('x', 0.0f);
    robot->lowerArmR->setRotation('x', 0.0f);
    robot->upperArmL->setRotation('x', 0.0f);
    robot->lowerArmL->setRotation('x', 0.0f);

    // Reset cup to pump shelf
    if (cupAttachedToRobot)
    {
        pumpStation->cup->setParent(pumpStation->shelf);
        pumpStation->cup->setPosition(0.0f, 0.32f, 0.0f);
    }
    cupAttachedToRobot = false;
    cupDelivered = false;

    // Hide water cubes
    for (int i = 0; i < WaterPumpStation::NUM_WATER_CUBES; i++)
        pumpStation->waterCubes[i]->hide();
}

// -----------------------------------------------------------------------------------------
// animateForNextFrame
// -----------------------------------------------------------------------------------------
void animateForNextFrame(float time, long frame)
{

   

   /*  ================================================================
     PHASE 1:  0 – 10s   Truck drives into garage and stops over hole
     ================================================================*/
    if (time >= 0.0f && time < 10.0f)
    {
        float t = smoothStep(time / 10.0f);
        float tz = lerp(TRUCK_START_Z, TRUCK_STOP_Z, t);
        truck->setPosition(TRUCK_X, 2.6f, tz);

        // Wheel spin: rotate wheels proportional to distance covered
        float dist = (TRUCK_START_Z - TRUCK_STOP_Z);
        float travelled = dist * t;
        float wheelAng = fmodf(travelled * 40.0f, 360.0f);
        // Wheels are children of base which is child of truck
        // We animate by adding a per-frame spin offset
        truck->wheels[0]->setRotation('y', 90.0f + wheelAng);
        truck->wheels[1]->setRotation('y', 90.0f + wheelAng);
        truck->wheels[2]->setRotation('y', 90.0f + wheelAng);
        truck->wheels[3]->setRotation('y', 90.0f + wheelAng);

        // CAMERA: dolly behind/beside truck as it enters
        float camZ = lerp(55.0f, 22.0f, t);
        float camX = lerp(TRUCK_X - 6.0f, TRUCK_X + 8.0f, t);
        gCamera.setPosition(camX, 7.0f, camZ);
        gCamera.setTarget(TRUCK_X, 2.5f, tz - 4.0f);
    }

    // ================================================================
    // PHASE 2:  10 – 14s   Human gets out, walks to chair
    // ================================================================
    if (time >= 10.0f && time < 14.0f)
    {
        // Show human the moment truck stops
        if (humanHiding)
        {
            human->show();
            humanHiding = false;
        }

        float t = smoothStep((time - 10.0f) / 4.0f);
        float hx = lerp(HUMAN_START_X, HUMAN_END_X, t);
        float hz = lerp(HUMAN_START_Z, HUMAN_END_Z, t);
        human->setPosition(hx, 0.36f, hz);

        // Turn human toward destination
        // Direction from start to end is mostly +X, slight +Z → ~90°
        human->setRotation('y', -90.0f);

        // Arm swing walk cycle
        float swing = sin_d(time * 280.0f) * 22.0f;
        human->arm1->setRotation('x', swing);
        human->arm2->setRotation('x', -swing);
        human->leg1->setRotation('x', -swing * 0.7f);
        human->leg2->setRotation('x', swing * 0.7f);
        human->sheead->setRotation('y', 180);
        
        // CAMERA: pan to follow human walking
        gCamera.setPosition(12.0f, 6.0f, 28.0f);
        gCamera.setTarget(hx, 2.0f, hz);
    }

    // Human sits down (after walk ends)
    if (time >= 14.0f && !cupDelivered)
    {
        human -> leg1 -> hide();
        human->leg2 -> hide();
        human -> leg1c -> hide();
        human -> leg2c -> hide();

        // Seat position: chair is at (22.1, 1.5, 17.0) world
        // Human sits slightly in front of backrest
        human->setPosition(22.1f, 1.2f, 17.0f);
        human->setRotation('y', 90.0f);   // face left (into garage)
        // Reset limb rotations to idle
        human->arm1->setRotation('x', 0.0f);
        human->arm2->setRotation('x', 0.0f);
        human->leg1->setRotation('x', 0.0f);
        human->leg2->setRotation('x', 0.0f);
    }

    // ================================================================
    // PHASE 3:  14 – 20s   Robot turns and drives to pump station
    // ================================================================
    if (time >= 14.0f && time < 20.0f)
    {
        float t = smoothStep((time - 14.0f) / 6.0f);

        float rx = lerp(ROBOT_START_X, ROBOT_PUMP_X, t);
        float rz = lerp(ROBOT_START_Z, ROBOT_PUMP_Z, t);
        robot->setPosition(rx, 1.0f, rz);

        // Face pump (pump is to the +X side, slightly -Z → rotate ~-90° Y)
        robot->setRotation('y', -180.0f);

        // Wheel roll
        float dist = sqrtf(powf(ROBOT_PUMP_X - ROBOT_START_X, 2) +
            powf(ROBOT_PUMP_Z - ROBOT_START_Z, 2));
        float rolled = dist * t;
        float wAngle = fmodf(rolled * 55.0f, 360.0f);
        robot->wheelFL->setRotation('y', 90.0f + wAngle);
        robot->wheelFR->setRotation('y', 90.0f - wAngle);
        robot->wheelBL->setRotation('y', 90.0f + wAngle);
        robot->wheelBR->setRotation('y', 90.0f - wAngle);
       
        // CAMERA: wide shot showing robot leaving its start spot toward pump
        float camX = lerp(12.0f, 18.0f, t);
        float camZ = lerp(25.0f, 10.0f, t);
        gCamera.setPosition(camX, 8.0f, camZ);
        gCamera.setTarget(rx, 1.5f, rz);
    }

    // ================================================================
    // PHASE 4:  20 – 26s   Pump dispenses water into cup
    // ================================================================
    if (time >= 20.0f && time < 26.0f)
    {
        float phase = time - 20.0f;  // 0 → 6
        robot->setRotation('y', 
            90);
        // Indicator light flashes green during dispensing
        float flash = (sin_d(phase * 180.0f) > 0.0f) ? 1.0f : 0.3f;
        pumpStation->indicatorLight->setColour(0.0f, flash, 0.0f, 1.0f);

        // Animate water cubes falling one by one
        // Cube i appears at t = i * 1.0s, falls 1.2 units in 0.8s
        for (int i = 0; i < WaterPumpStation::NUM_WATER_CUBES; i++)
        {
            float startT = (float)i * 1.1f;
            float localT = phase - startT;
            
            if (localT >= 0.0f && localT < 1.0f)
            {
                pumpStation->waterCubes[i]->show();
                // fall from nozzle (Y=0 relative to pipeElbow) down to cup (Y≈-1.2)
                float fallY = lerp(0.0f, -1.2f, smoothStep(localT));
                pumpStation->waterCubes[i]->setPosition(0.2f, fallY, 0.0f);
            }
            else if (localT >= 1.0f)
            {
                // settled in cup – hide (cup looks full)
                pumpStation->waterCubes[i]->hide();
            }
        }

        // CAMERA: close-up on pump nozzle and cup
        gCamera.setPosition(14.0f, 6.5f, 0.0f);
        gCamera.setTarget(21.0f, 4.5f, -5.0f);
    }

    // ================================================================
    // PHASE 5:  26 – 28s   Robot arm reaches down, grabs cup
    // ================================================================
    if (time >= 26.0f && time < 28.0f)
    {
        float t = smoothStep((time - 26.0f) / 2.0f);

        // Extend right arm downward toward shelf
        float armAngle = lerp(0.0f, 55.0f, t);
        robot->upperArmR->setRotation('x', armAngle);
        robot->lowerArmR->setRotation('x', armAngle * 0.5f);

        // At t=1 attach cup to robot hand
        if (t >= 1.0f && !cupAttachedToRobot)
        {
            cupAttachedToRobot = true;
            pumpStation->cup->setParent(robot->hand);
            pumpStation->cup->setPosition(0.0f, -0.28f, 0.0f);
            // Indicator back to red (idle)
            pumpStation->indicatorLight->setColour(1.0f, 0.0f, 0.0f, 1.0f);
        }
    }

    // ================================================================
    // PHASE 6:  28 – 35s   Robot carries cup across garage to human
    // ================================================================
    if (time >= 28.0f && time < 35.0f)
    {
        float t = smoothStep((time - 28.0f) / 7.0f);

        float rx = lerp(ROBOT_PUMP_X, ROBOT_HUMAN_X, t);
        float rz = lerp(ROBOT_PUMP_Z, ROBOT_HUMAN_Z, t);
        robot->setPosition(rx, 1.0f, rz);

        // Face the human (human is at ~X=22, Z=17, robot coming from X=19.5, Z=-5)
        // Direction is +Z roughly → face +Z → rotation 0°
        robot->setRotation('y', 0.0f);

        // Keep arm raised holding cup
        robot->upperArmR->setRotation('x', 45.0f);
        robot->lowerArmR->setRotation('x', -20.0f);

        // Left arm swings naturally
        float swing = sin_d(time * 200.0f) * 18.0f;
        robot->upperArmL->setRotation('x', swing);

        // Wheel roll
        float dist = sqrtf(powf(ROBOT_HUMAN_X - ROBOT_PUMP_X, 2) +
            powf(ROBOT_HUMAN_Z - ROBOT_PUMP_Z, 2));
        float rolled = dist * t;
        float wAngle = fmodf(rolled * 55.0f, 360.0f);
        robot->wheelFL->setRotation('z', 90.0f + wAngle);
        robot->wheelFR->setRotation('z', 90.0f - wAngle);
        robot->wheelBL->setRotation('z', 90.0f + wAngle);
        robot->wheelBR->setRotation('z', 90.0f - wAngle);

        // CAMERA: medium shot following robot with human in frame
        float camX = lerp(14.0f, 18.0f, t);
        float camZ = lerp(5.0f, 22.0f, t);
        gCamera.setPosition(camX, 6.0f, camZ);
        gCamera.setTarget(rx, 2.0f, rz);
    }

    // ================================================================
    // PHASE 7:  35 – 38s   Human drinks – cup handed over
    // ================================================================
    if (time >= 35.0f && time < 38.0f)
    {
        float t = smoothStep((time - 35.0f) / 3.0f);

        // Robot arm extends toward human
        float armAngle = lerp(45.0f, 75.0f, t);
        robot->upperArmR->setRotation('x', armAngle);
        robot->lowerArmR->setRotation('x', lerp(-20.0f, 20.0f, t));

        // Human raises arm to take cup
        human->arm1->setRotation('x', lerp(0.0f, -60.0f, t));  // raise right arm

        // At midpoint transfer cup to human hand
        if (t >= 0.5f && !cupDelivered)
        {
            cupDelivered = true;
            pumpStation->cup->setParent(human->arm1c);
            pumpStation->cup->setPosition(0.0f, 0.3f, 0.0f);

            // Reset robot arm
            robot->upperArmR->setRotation('x', 0.0f);
            robot->lowerArmR->setRotation('x', 0.0f);
        }

        // CAMERA: close-up on the handoff
        gCamera.setPosition(14.0f, 10.0f, 20.0f);
        gCamera.setTarget(20.5f, 3.5f, 17.0f);
    }

    // After delivery lower human arm with cup (drinking pose)
    if (time >= 37.0f && time < 38.5f)
    {
        float t = smoothStep((time - 37.0f) / 1.5f);
        human->arm1->setRotation('x', lerp(-60.0f, -30.0f, t));
    }

    // Cup disappears (drunk) at 38.5s
    if (time >= 38.5f && cupDelivered)
    {
        pumpStation->cup->hide();
    }

    // ================================================================
    // PHASE 8:  38 – 50s   Robot happy dance / celebration
    // ================================================================
    if (time >= 38.0f && time < 50.0f)
    {
        float dt = time - 38.0f;   // 0 → 12

        // Body bob up and down
        float bobY = 1.0f + sin_d(dt * 180.0f) * 0.25f;
        robot->setPosition(ROBOT_HUMAN_X - 2.0f, bobY, ROBOT_HUMAN_Z - 2.0f);

        // Spin on Y axis
        float spinY = fmodf(dt * 72.0f, 360.0f);  // 1 full spin per 5s
        robot->setRotation('y', spinY);

        // Both arms wave energetically
        float waveR = sin_d(dt * 270.0f) * 65.0f;
        float waveL = -sin_d(dt * 270.0f) * 65.0f;
        robot->upperArmR->setRotation('x', waveR);
        robot->upperArmL->setRotation('x', waveL);
        robot->lowerArmR->setRotation('x', sin_d(dt * 270.0f + 45.0f) * 40.0f);
        robot->lowerArmL->setRotation('x', sin_d(dt * 270.0f - 45.0f) * 40.0f);

        // Antenna sways
        robot->antenna->setRotation('z', sin_d(dt * 360.0f) * 20.0f);

        // Screen flashes colours (cycle through RGB)
        float cr = (sin_d(dt * 120.0f) + 1.0f) * 0.5f;
        float cg = (sin_d(dt * 120.0f + 120.0f) + 1.0f) * 0.5f;
        float cb = (sin_d(dt * 120.0f + 240.0f) + 1.0f) * 0.5f;
        robot->bscreen->setColour(cr, cg, cb, 1.0f);

        // Eye flash
        robot->eyeLeft->setColour(cr, cg, cb, 1.0f);
        robot->eyeRight->setColour(cr, cg, cb, 1.0f);

        // CAMERA: pull back wide for the celebration
        float camDist = lerp(10.0f, 22.0f, smoothStep(dt / 12.0f));
        float camAngle = dt * 15.0f;   // slowly orbit
        float camX = ROBOT_HUMAN_X + sin_d(camAngle) * camDist;
        float camZ = ROBOT_HUMAN_Z + cos_d(camAngle) * camDist;
        gCamera.setPosition(17.0,sin_d(dt * 60.0f) * 1.5f, camZ);
        gCamera.setTarget(ROBOT_HUMAN_X - 1.0f, 2.5f, ROBOT_HUMAN_Z);
    }

    // ================================================================
    // END: 50s+
    // ================================================================
    if (time >= 50.0f)
    {
        gProgramMode = kpmFinished;
    }
}

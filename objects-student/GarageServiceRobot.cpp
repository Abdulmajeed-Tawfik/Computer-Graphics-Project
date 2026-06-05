#include "prefix.h"
#include "GarageServiceRobot.h"
#include "utility.h"

#include <cmath>

// -------------------------------------------------
// Constructor
// -------------------------------------------------
GarageServiceRobot::GarageServiceRobot()
{
    // -------------------------------------------------
    // Main body
    // Body is the main visible parent of the robot.
    // The whole robot is moved by moving "this".
    // -------------------------------------------------
    body = new cube();
    body->setParent(this);
    body->setPosition(0.0f, 0.8f, 0.0f);
    body->setDeformation(1.4f, 0.65f, 0.9f);
    body->setColour(0.65f, 0.65f, 0.62f);
    rememberPart(body);

    // -------------------------------------------------
    // Head
    // Parent is body, so position is relative to body.
    // -------------------------------------------------
    head = new cube();
    head->setParent(body);
    head->setPosition(0.0f, 1.2f, 0.05f);
    head->setDeformation(0.75f, 0.55f, 0.55f);
    head->setColour(0.78f, 0.78f, 0.75f);
    rememberPart(head);

    // -------------------------------------------------
    // Front screen
    // -------------------------------------------------
    screen = new cube();
    screen->setParent(head);
    screen->setPosition(0.0f, 0.0f, 0.59f);
    screen->setDeformation(0.55f, 0.32f, 0.04f);
    screen->setColour(0.02f, 0.04f, 0.05f);
    screen->setEmissiveColour(0.0f, 0.15f, 0.2f, 1.0f);
    rememberPart(screen);

    // -------------------------------------------------
    // Eyes
    // -------------------------------------------------
    leftEye = new sphere(24);
    leftEye->setParent(screen);
    leftEye->setPosition(-0.2f, 0.17f, 0.12f);
    leftEye->setScale(0.08f);
    leftEye->setColour(0.0f, 0.9f, 1.0f);
    leftEye->setEmissiveColour(0.0f, 0.7f, 0.9f, 1.0f);
    rememberPart(leftEye);

    rightEye = new sphere(24);
    rightEye->setParent(screen);
    rightEye->setPosition(0.2f, 0.17f, 0.12f);
    rightEye->setScale(0.08f);
    rightEye->setColour(0.0f, 0.9f, 1.0f);
    rightEye->setEmissiveColour(0.0f, 0.7f, 0.9f, 1.0f);
    rememberPart(rightEye);

    // -------------------------------------------------
    // Transparent windshield / face shield
    // -------------------------------------------------
    windshield = new cube();
    windshield->setParent(head);
    windshield->setPosition(0.0f, 0.0f, 0.59f);
    windshield->setDeformation(0.65f, 0.42f, 0.04f);
    windshield->setColour(0.2f, 0.8f, 1.0f, 0.28f);
    windshield->makeTransparent();
    rememberPart(windshield);

    // -------------------------------------------------
    // Wheels
    // If the wheel direction looks wrong, change 'y', 90.0f to 'z', 90.0f
    // in both constructor and spinWheels().
    // -------------------------------------------------
    frontLeftWheel = new torus(24, 16, 1.0f, 0.35f);
    frontLeftWheel->setParent(body);
    frontLeftWheel->setPosition(-0.95f, -0.98f, 0.45f);
    frontLeftWheel->setScale(0.25f);
    frontLeftWheel->setRotation('z', 90.0f);
    frontLeftWheel->setColour(1.0f, 0.82f, 0.15f);
    rememberPart(frontLeftWheel);

    frontRightWheel = new torus(24, 16, 1.0f, 0.35f);
    frontRightWheel->setParent(body);
    frontRightWheel->setPosition(0.95f, -0.98f, 0.45f);
    frontRightWheel->setScale(0.25f);
    frontRightWheel->setRotation('z', 90.0f);
    frontRightWheel->setColour(1.0f, 0.82f, 0.15f);
    rememberPart(frontRightWheel);

    backLeftWheel = new torus(24, 16, 1.0f, 0.35f);
    backLeftWheel->setParent(body);
    backLeftWheel->setPosition(-0.95f, -0.98f, -0.45f);
    backLeftWheel->setScale(0.25f);
    backLeftWheel->setRotation('z', 90.0f);
    backLeftWheel->setColour(1.0f, 0.82f, 0.15f);
    rememberPart(backLeftWheel);

    backRightWheel = new torus(24, 16, 1.0f, 0.35f);
    backRightWheel->setParent(body);
    backRightWheel->setPosition(0.95f, -0.98f, -0.45f);
    backRightWheel->setScale(0.25f);
    backRightWheel->setRotation('z', 90.0f);
    backRightWheel->setColour(1.0f, 0.82f, 0.15f);
    rememberPart(backRightWheel);

    // -------------------------------------------------
    // Delivery tray
    // -------------------------------------------------
    tray = new cube();
    tray->setParent(body);
    tray->setPosition(0.0f, 0.20f, 1.45f);
    tray->setDeformation(0.85f, 0.08f, 0.55f);
    tray->setColour(0.18f, 0.18f, 0.18f);
    rememberPart(tray);

    // -------------------------------------------------
    // Water pump package on tray
    // -------------------------------------------------
    pumpBody = new cylinder();
    pumpBody->setParent(tray);
    pumpBody->setPosition(0.0f, 0.4f, 0.0f);
    pumpBody->setDeformation(0.32f, 0.32f, 0.32f);
    pumpBody->setColour(0.6f, 0.6f, 0.58f);
    rememberPart(pumpBody);

    pumpCapLeft = new sphere(24);
    pumpCapLeft->setParent(pumpBody);
    pumpCapLeft->setPosition(-0.48f, 0.0f, 0.0f);
    pumpCapLeft->setScale(0.16f);
    pumpCapLeft->setColour(0.5f, 0.5f, 0.48f);
    rememberPart(pumpCapLeft);

    pumpCapRight = new sphere(24);
    pumpCapRight->setParent(pumpBody);
    pumpCapRight->setPosition(0.48f, 0.0f, 0.0f);
    pumpCapRight->setScale(0.16f);
    pumpCapRight->setColour(0.5f, 0.5f, 0.48f);
    rememberPart(pumpCapRight);

    // -------------------------------------------------
    // Arms
    // setOffset moves the geometry down from the shoulder pivot,
    // so the arm rotates from the top.
    // -------------------------------------------------
    inileftArm = new cylinder();
    inileftArm->setParent(head);
    inileftArm->setPosition(-1.0f, -0.3f, 0.15f);
    //leftArm->setOffset(0.0f, -0.28f, 0.0f);
    inileftArm->setDeformation(0.07f, 0.25f, 0.07f);
    inileftArm->setRotation('z', -90.0f);
    inileftArm->setColour(0.55f, 0.55f, 0.55f);
    rememberPart(inileftArm);
    
    leftArm = new cylinder();
    leftArm->setParent(head);
    leftArm->setPosition(-1.18f, -0.3f, 0.621f);
    //leftArm->setOffset(0.0f, -0.28f, 0.0f);
    leftArm->setDeformation(0.07f, 0.4f, 0.07f);
    leftArm->setRotation('x', -90.0f);
    leftArm->setColour(0.55f, 0.55f, 0.55f);
    rememberPart(leftArm);

    inirightArm = new cylinder();
    inirightArm->setParent(head);
    inirightArm->setPosition(1.0f, -0.3f, 0.15f);
    //rightArm->setOffset(0.0f, -0.28f, 0.0f);
    inirightArm->setDeformation(0.07f, 0.25f, 0.07f);
    inirightArm->setRotation('z', 90.0f);
    inirightArm->setColour(0.55f, 0.55f, 0.55f);
    rememberPart(inirightArm);

    rightArm = new cylinder();
    rightArm->setParent(head);
    rightArm->setPosition(1.18f, -0.3f, 0.621f);
    //rightArm->setOffset(0.0f, -0.28f, 0.0f);
    rightArm->setDeformation(0.07f, 0.4f, 0.07f);
    rightArm->setRotation('x', -90.0f);
    rightArm->setColour(0.55f, 0.55f, 0.55f);
    rememberPart(rightArm);

    // Hands are children of arms.
    leftHand = new sphere(24);
    leftHand->setParent(leftArm);
    leftHand->setPosition(0.0f, -0.5f, 0.0f);
    leftHand->setScale(0.11f);
    leftHand->setColour(0.95f, 0.7f, 0.1f);
    rememberPart(leftHand);

    rightHand = new sphere(24);
    rightHand->setParent(rightArm);
    rightHand->setPosition(0.0f, -0.5f, 0.0f);
    rightHand->setScale(0.11f);
    rightHand->setColour(0.95f, 0.7f, 0.1f);
    rememberPart(rightHand);

    // -------------------------------------------------
    // Antenna
    // antennaPole rotates from the bottom because of offset.
    // antennaBall follows antennaPole.
    // -------------------------------------------------
    antennaPole = new cylinder();
    antennaPole->setParent(head);
    antennaPole->setPosition(0.0f, 1.0f, 0.05f);
    //antennaPole->setOffset(0.0f, 0.35f, 0.0f);
    antennaPole->setDeformation(0.035f, 0.45f, 0.035f);
    antennaPole->setColour(0.15f, 0.15f, 0.15f);
    rememberPart(antennaPole);

    antennaBall = new sphere(24);
    antennaBall->setParent(antennaPole);
    antennaBall->setPosition(0.0f, 0.54f, 0.0f);
    antennaBall->setScale(0.09f);
    antennaBall->setColour(1.0f, 0.0f, 0.0f);
    antennaBall->setEmissiveColour(0.6f, 0.0f, 0.0f, 1.0f);
    rememberPart(antennaBall);
}

// -------------------------------------------------
// Destructor
// -------------------------------------------------
GarageServiceRobot::~GarageServiceRobot()
{
    // Do not manually delete children here.
    // This base engine usually manages created objects through its global object list.
}

// -------------------------------------------------
// Store child object pointer for hide/show
// -------------------------------------------------
void GarageServiceRobot::rememberPart(object3d* part)
{
    parts.push_back(part);
}

// -------------------------------------------------
// Hide all child objects
// -------------------------------------------------
void GarageServiceRobot::hide(void)
{
    object3d::hide();

    for (unsigned int i = 0; i < parts.size(); i++)
        parts[i]->hide();
}

// -------------------------------------------------
// Show all child objects
// -------------------------------------------------
void GarageServiceRobot::show(void)
{
    object3d::show();

    for (unsigned int i = 0; i < parts.size(); i++)
        parts[i]->show();
}

// -------------------------------------------------
// Parent object has no direct visible geometry
// -------------------------------------------------
void GarageServiceRobot::privateDraw(bool drawMode)
{
    // All visible geometry is made from child objects.
}

// -------------------------------------------------
// Animation 1: drive into the scene (0每12s only)
// -------------------------------------------------
// -------------------------------------------------

// -------------------------------------------------
// Animation 1: Drive ALONG Z-AXIS (back ↙ front)
// -------------------------------------------------
void GarageServiceRobot::drive(float time)
{
    float z;

    // Drive forward with smooth acceleration (0每12s)
    if (time < 12.0f)
    {
        float t = time / 12.0f;
        float smooth = 1 - cos_d(t * 90.0f); // Slow start, fast middle, slow end
        z = 8.0f - 10.0f * smooth;
    }
    else
    {
        z = -1.20f; // Stop in front of station
    }

    setPosition(0.0f, 0.0f, z);
}

// -------------------------------------------------
// Animation 2: Wheels spin WHILE DRIVING FORWARD
// -------------------------------------------------
void GarageServiceRobot::spinWheels(float time)
{
    float angle;

    if (time < 12.0f)
    {
        // Speed matches drive acceleration
        float t = time / 12.0f;
        float speedFactor = sin_d(t * 90.0f);
        angle = -time * 500.0f * speedFactor;
    }
    else
    {
        angle = -12.0f * 500.0f; // Stop when robot stops
    }

    frontLeftWheel->setRotation('z', 90.0f, 'x', angle);
    frontRightWheel->setRotation('z', 90.0f, 'x', angle);
    backLeftWheel->setRotation('z', 90.0f, 'x', angle);
    backRightWheel->setRotation('z', 90.0f, 'x', angle);
}

// -------------------------------------------------
// Animation 3: WAVE BOTH ARMS (left + right together)
// -------------------------------------------------
void GarageServiceRobot::waveArm(float time)
{
    // Default resting angles (matches YOUR model)
    float L_shoulder = -90.0f;
    float R_shoulder = 90.0f;
    float forearm = -90.0f;

    // Slow wave when arriving (12每16s)
    if (time > 12.0f && time < 16.0f)
    {
        float wave = sin_d(time * 360.0f);
        L_shoulder = -90.0f + (25.0f * wave);
        R_shoulder = 90.0f - (25.0f * wave);
        forearm = -90.0f + (35.0f * wave);
    }

    // Fast celebration wave (35每40s)
    else if (time > 35.0f && time < 40.0f)
    {
        float fastWave = sin_d(time * 720.0f);
        L_shoulder = -90.0f + (35.0f * fastWave);
        R_shoulder = 90.0f - (35.0f * fastWave);
        forearm = -90.0f + (50.0f * fastWave);
    }

    // Idle movement (16每35s)
    else if (time >= 16.0f && time <= 35.0f)
    {
        float idle = sin_d(time * 120.0f);
        L_shoulder = -90.0f + (6.0f * idle);
        R_shoulder = 90.0f - (6.0f * idle);
        forearm = -90.0f + (8.0f * idle);
    }

    // Apply to LEFT ARM
    inileftArm->setRotation('z', L_shoulder);
    leftArm->setRotation('x', forearm);

    // Apply to RIGHT ARM
    inirightArm->setRotation('z', R_shoulder);
    rightArm->setRotation('x', forearm);
}
// -------------------------------------------------
// Animation 4: blink screen and eyes (faster at end)
// -------------------------------------------------
void GarageServiceRobot::blinkScreen(float time)
{
    float blinkSpeed;

    // Fast blink during celebration
    if (time > 35.0f && time < 40.0f)
        blinkSpeed = fmod(time, 0.3f);
    // Normal blink otherwise
    else
        blinkSpeed = fmod(time, 1.0f);

    if (blinkSpeed < 0.15f)
    {
        // Bright glow
        screen->setEmissiveColour(0.0f, 0.4f, 0.5f, 1.0f);
        leftEye->setEmissiveColour(0.0f, 0.9f, 1.0f, 1.0f);
        rightEye->setEmissiveColour(0.0f, 0.9f, 1.0f, 1.0f);
    }
    else
    {
        // Dim glow
        screen->setEmissiveColour(0.0f, 0.08f, 0.12f, 1.0f);
        leftEye->setEmissiveColour(0.0f, 0.3f, 0.4f, 1.0f);
        rightEye->setEmissiveColour(0.0f, 0.3f, 0.4f, 1.0f);
    }
}

// -------------------------------------------------
// Animation 5: antenna waving (smooth, natural)
// -------------------------------------------------
void GarageServiceRobot::waveAntenna(float time)
{
    float sway = 10.0f * sin_d(time * 200.0f);
    antennaPole->setRotation('z', sway);
}

// -------------------------------------------------
// Texture helper: robot screen
// -------------------------------------------------
void GarageServiceRobot::setScreenTexture(texture* t)
{
    screen->setTexture(t);
}

// -------------------------------------------------
// Texture helper: cargo / pump package
// -------------------------------------------------
void GarageServiceRobot::setCargoTexture(texture* t)
{
    pumpBody->setTexture(t);
}
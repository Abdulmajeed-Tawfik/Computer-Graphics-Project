// GarageServiceRobot.cpp
#include "prefix.h"
#include "GarageServiceRobot.h"
#include "utility.h"

extern vector<object3d*> gShapeVector;

GarageServiceRobot::GarageServiceRobot()
{
    setName("GarageServiceRobot");

    // ---------------------------------------------------------------
    // BODY  (root of the robot hierarchy, parent = this)
    // ---------------------------------------------------------------
    body = new cube();
    body->setParent(this);
    body->setDeformation(1.1f, 1.4f, 0.8f);
    body->setPosition(0.0f, 1.8f, 0.0f);
    //body->setColour(0.20f, 0.22f, 0.28f, 1.0f);   // dark grey
    body->setColour(0.65f, 0.65f, 0.62f, 1.0f);   // dark grey
    rememberPart(body);

    // ---------------------------------------------------------------
    // CHEST PLATE  (extrusion ¨C hexagonal emblem, clearly visible)
    // ---------------------------------------------------------------
    //chestPlate = new extrusion("robot_chest_profile.txt", "robot_chest_path.txt");
    //chestPlate->setParent(body);
    //chestPlate->setPosition(0.0f, 0.2f, 1.05f);    // front face of body
    //chestPlate->setDeformation(1.0f, 1.0f, 1.0f);
    //chestPlate->setColour(0.0f, 0.75f, 1.0f, 1.0f); // bright cyan
    //rememberPart(chestPlate);

    // ---------------------------------------------------------------
    // SCREEN  (small glowing rectangle on body front)
    // ---------------------------------------------------------------
    bscreen = new cube();
    bscreen->setParent(body);
    bscreen->setPosition(0.0f, -0.2f, 1.05f);
    bscreen->setDeformation(0.55f, 0.3f, 0.05f);
    bscreen->setColour(0.02f, 0.04f, 0.05f, 1.0f);     // green display
	bscreen->setEmissiveColour(0.0f, 0.15f, 0.2f, 1.0f); // cyan glow
    rememberPart(bscreen);

    

    // ---------------------------------------------------------------
    // HEAD
    // ---------------------------------------------------------------
    head = new cube();
    head->setParent(body);
    head->setPosition(0.0f, 2.1f, 0.0f);
    head->setDeformation(0.85f, 0.7f, 0.7f);
    //head->setColour(0.25f, 0.27f, 0.33f, 1.0f);
    head->setColour(0.65f, 0.65f, 0.62f, 1.0f);
    rememberPart(head);


    fscreen = new cube();
    fscreen->setParent(head);
    fscreen->setPosition(0.0f, 0.0f, 0.74f);
    fscreen->setDeformation(0.65f, 0.52f, 0.04f);
    fscreen->setColour(0.02f, 0.04f, 0.05f, 1.0f);
    fscreen->setEmissiveColour(0.0f, 0.15f, 0.2f, 1.0f);
    rememberPart(fscreen);


    eyeLeft = new sphere(20);
    eyeLeft->setParent(fscreen);
    eyeLeft->setPosition(-0.28f, 0.1f, 0.1f);
    eyeLeft->setDeformation(0.18f, 0.18f, 0.06f);
    eyeLeft->setColour(0.0f, 0.9f, 1.0f, 1.0f);    // orange glow
    rememberPart(eyeLeft);

    eyeRight = new sphere(20);
    eyeRight->setParent(fscreen);
    eyeRight->setPosition(0.28f, 0.1f, 0.1f);
    eyeRight->setDeformation(0.18f, 0.18f, 0.06f);
   // eyeRight->setColour(1.0f, 0.3f, 0.0f, 1.0f);
    eyeRight->setColour(0.0f, 0.9f, 1.0f, 1.0f);
    rememberPart(eyeRight);




    windshield = new cube();
    windshield->setParent(head);
    windshield->setPosition(0.0f, 0.0f, 0.74f);
    windshield->setDeformation(0.75f, 0.62f, 0.04f);
    windshield->setColour(0.2f, 0.8f, 1.0f, 0.28f);
    windshield->makeTransparent();
    rememberPart(windshield);


    // ---------------------------------------------------------------
    // ANTENNA
    // ---------------------------------------------------------------
    antenna = new cylinder(12);
    antenna->setParent(head);
    antenna->setPosition(0.0f, 1.25f, 0.0f);
    antenna->setDeformation(0.08f, 0.55f, 0.08f);
    antenna->setColour(0.6f, 0.6f, 0.6f, 1.0f);
    rememberPart(antenna);

    // Antenna tip ball
    object3d* antennaTip = new sphere(12);
    antennaTip->setParent(antenna);
    antennaTip->setPosition(0.0f, 0.65f, 0.0f);
    antennaTip->setDeformation(0.22f, 0.22f, 0.22f);
    antennaTip->setColour(1.0f, 0.0f, 0.0f, 1.0f); // red tip
    rememberPart(antennaTip);

    // ---------------------------------------------------------------
    // WHEELS  (four flat cylinders)
    // ---------------------------------------------------------------
    wheelFL = new cylinder(16);
    wheelFL->setParent(body);
    wheelFL->setPosition(-1.35f, -1.35f, 0.55f);
    wheelFL->setDeformation(0.55f, 0.22f, 0.55f);
    wheelFL->setRotation('z', 90.0f);
    wheelFL->setColour(0.02f, 0.04f, 0.05f, 1.0f);
    wheelFL->setEmissiveColour(0.0f, 0.15f, 0.2f, 1.0f); // cyan glow
    rememberPart(wheelFL);

    wheelFR = new cylinder(16);
    wheelFR->setParent(body);
    wheelFR->setPosition(1.35f, -1.35f, 0.55f);
    wheelFR->setDeformation(0.55f, 0.22f, 0.55f);
    wheelFR->setRotation('z', 90.0f);
    wheelFR->setColour(0.02f, 0.04f, 0.05f , 1.0f);
    wheelFR->setEmissiveColour(0.0f, 0.15f, 0.2f, 1.0f); // cyan glow
    rememberPart(wheelFR);

    wheelBL = new cylinder(16);
    wheelBL->setParent(body);
    wheelBL->setPosition(-1.35f, -1.35f, -0.55f);
    wheelBL->setDeformation(0.55f, 0.22f, 0.55f);
    wheelBL->setRotation('z', 90.0f);
    wheelBL->setColour(0.02f, 0.04f, 0.05f, 1.0f);
    wheelBL->setEmissiveColour(0.0f, 0.15f, 0.2f, 1.0f); // cyan glow
    rememberPart(wheelBL);

    wheelBR = new cylinder(16);
    wheelBR->setParent(body);
    wheelBR->setPosition(1.35f, -1.35f, -0.55f);
    wheelBR->setDeformation(0.55f, 0.22f, 0.55f);
    wheelBR->setRotation('z', 90.0f);
    wheelBR->setColour(0.02f, 0.04f, 0.05f, 1.0f);
	wheelBL->setEmissiveColour(0.0f, 0.15f, 0.2f, 1.0f); // cyan glow
    rememberPart(wheelBR);

    // ---------------------------------------------------------------
    // RIGHT ARM  (delivery arm ¨C holds the cup)
    // ---------------------------------------------------------------
    shoulderR = new sphere(14);
    shoulderR->setParent(body);
    shoulderR->setPosition(1.35f, 0.55f, 0.0f);
    shoulderR->setDeformation(0.28f, 0.28f, 0.28f);
    shoulderR->setColour(0.35f, 0.37f, 0.42f, 1.0f);
    rememberPart(shoulderR);

    upperArmR = new cube();
    upperArmR->setParent(shoulderR);
    upperArmR->setPosition(0.45f, -0.4f, 0.0f);
    upperArmR->setDeformation(0.22f, 0.55f, 0.22f);
    upperArmR->setColour(0.02f, 0.04f, 0.05f, 1.0f);
	upperArmR->setEmissiveColour(0.0f, 0.15f, 0.2f, 1.0f); // cyan glow
    rememberPart(upperArmR);

    lowerArmR = new cube();
    lowerArmR->setParent(upperArmR);
    lowerArmR->setPosition(0.0f, -0.9f, 0.0f);
    lowerArmR->setDeformation(0.20f, 0.35f, 0.20f);
    lowerArmR->setColour(0.65f, 0.65f, 0.62f, 1.0f);
    rememberPart(lowerArmR);

    // SWEEP: wrist band ring on right lower arm (clearly visible)
    wristBandR = new sweep("robot_wrist_profile.txt", 16);
    wristBandR->setParent(lowerArmR);
    wristBandR->setPosition(0.0f, -0.41f, 0.0f);
    wristBandR->setDeformation(1.5f, 0.5f, 1.5f);
    wristBandR->setColour(0.0f, 0.75f, 1.0f, 1.0f); // bright cyan matches chest
    rememberPart(wristBandR);

	

    // HAND / GRIPPER  ¨C cup will be parented here
    hand = new cube();
    hand->setParent(lowerArmR);
    hand->setPosition(0.0f, -0.62f, 0.0f);
    hand->setDeformation(0.28f, 0.15f, 0.28f);
    hand->setColour(0.50f, 0.52f, 0.55f, 1.0f);    // light metal
    rememberPart(hand);

    // ---------------------------------------------------------------
    // LEFT ARM  (non-delivery, for dance animation)
    // ---------------------------------------------------------------
    shoulderL = new sphere(14);
    shoulderL->setParent(body);
    shoulderL->setPosition(-1.35f, 0.55f, 0.0f);
    shoulderL->setDeformation(0.28f, 0.28f, 0.28f);
    shoulderL->setColour(0.35f, 0.37f, 0.42f, 1.0f);
    rememberPart(shoulderL);

    upperArmL = new cube();
    upperArmL->setParent(shoulderL);
    upperArmL->setPosition(-0.45f, -0.4f, 0.0f);
    upperArmL->setDeformation(0.22f, 0.55f, 0.22f);
    //upperArmL->setColour(0.20f, 0.22f, 0.28f, 1.0f);
    upperArmL->setColour(0.02f, 0.04f, 0.05f, 1.0f);
	upperArmL->setEmissiveColour(0.0f, 0.15f, 0.2f, 1.0f); // cyan glow
    rememberPart(upperArmL);

    lowerArmL = new cube();
    lowerArmL->setParent(upperArmL);
    lowerArmL->setPosition(0.0f, -0.9f, 0.0f);
    lowerArmL->setDeformation(0.20f, 0.35f, 0.20f);
    lowerArmL->setColour(0.65f, 0.65f, 0.62f, 1.0f);
    //lowerArmL->setColour(0.20f, 0.22f, 0.28f, 1.0f);
    rememberPart(lowerArmL);

    wristBandL = new sweep("robot_wrist_profile.txt", 16);
    wristBandL->setParent(lowerArmL);
	wristBandL->setPosition(0.0f, -0.41f, 0.0f);
	wristBandL->setDeformation(1.5f, 0.5f, 1.5f);
	wristBandL->setColour(0.0f, 0.75f, 1.0f, 1.0f); // bright cyan matches chest
	rememberPart(wristBandL);

    gShapeVector.push_back(this);
}

GarageServiceRobot::~GarageServiceRobot() {}

void GarageServiceRobot::rememberPart(object3d* p)
{
    parts.push_back(p);
}

void GarageServiceRobot::show()
{
    object3d::show();
    for (auto p : parts) p->show();
}

void GarageServiceRobot::hide()
{
    object3d::hide();
    for (auto p : parts) p->hide();
}

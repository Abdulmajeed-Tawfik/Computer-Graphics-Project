// WaterPumpStation.cpp
#include "prefix.h"
#include "WaterPumpStation.h"
#include "utility.h"

extern vector<object3d*> gShapeVector;

WaterPumpStation::WaterPumpStation()
{
    setName("WaterPumpStation");

   

    // ---------------------------------------------------------------
    // SWEEP: octagonal decorative base ring (clearly visible at bottom)
    // ---------------------------------------------------------------
    baseRing = new sweep("pump_base_profile.txt", 10);
    baseRing->setParent(this);
    baseRing->setPosition(0.0f, 0.0f, 0.0f);
    baseRing->setDeformation(3.5f, 0.4f, 2.5f);
    baseRing->setColour(0.70f, 0.72f, 0.10f, 1.0f);  // yellow-gold accent
    rememberPart(baseRing);


    // ---------------------------------------------------------------
   // MAIN BODY CABINET  (tall upright unit, parent = this)
   // ---------------------------------------------------------------
    mainBody = new cube();
    mainBody->setParent(baseRing);
    mainBody->setDeformation(1.4f, 3.0f, 1.0f);
    mainBody->setPosition(0.0f, 3.21f, 0.0f);
    mainBody->setColour(0.18f, 0.38f, 0.55f, 1.0f);  // steel blue
    rememberPart(mainBody);

    // ---------------------------------------------------------------
    // TOP PANEL
    // ---------------------------------------------------------------
    topPanel = new cube();
    topPanel->setParent(mainBody);
    topPanel->setPosition(0.0f, 3.12f, 0.0f);
    topPanel->setDeformation(1.55f, 0.12f, 1.12f);
    topPanel->setColour(0.12f, 0.28f, 0.42f, 1.0f);
    rememberPart(topPanel);

    // ---------------------------------------------------------------
    // STATUS / INDICATOR LIGHT on top
    // ---------------------------------------------------------------
    indicatorLight = new sphere(14);
    indicatorLight->setParent(topPanel);
    indicatorLight->setPosition(0.0f, 0.33f, 0.0f);
    indicatorLight->setDeformation(0.22f, 0.22f, 0.22f);
    indicatorLight->setColour(1.0f, 0.0f, 0.0f, 1.0f); // red = idle
    rememberPart(indicatorLight);

    // ---------------------------------------------------------------
    // CONTROL PANEL (front face of cabinet)
    // ---------------------------------------------------------------
    controlPanel = new cube();
    controlPanel->setParent(mainBody);
    controlPanel->setPosition(0.0f, 0.0f, 1.08f);
    controlPanel->setDeformation(1.1f, 1.6f, 0.08f);
    controlPanel->setColour(0.10f, 0.10f, 0.14f, 1.0f); // near-black face
    rememberPart(controlPanel);

    buttonGreen = new sphere(10);
    buttonGreen->setParent(controlPanel);
    buttonGreen->setPosition(-0.35f, 0.55f, 0.12f);
    buttonGreen->setDeformation(0.12f, 0.12f, 0.08f);
    buttonGreen->setColour(0.0f, 1.0f, 0.2f, 1.0f);
    rememberPart(buttonGreen);

    buttonRed = new sphere(10);
    buttonRed->setParent(controlPanel);
    buttonRed->setPosition(0.35f, 0.55f, 0.12f);
    buttonRed->setDeformation(0.12f, 0.12f, 0.08f);
    buttonRed->setColour(1.0f, 0.1f, 0.0f, 1.0f);
    rememberPart(buttonRed);

    // ---------------------------------------------------------------
    // PIPE COLUMN  (vertical pipe rising from top of cabinet)
    // ---------------------------------------------------------------
    pipeColumn = new cylinder(12);
    pipeColumn->setParent(mainBody);
    pipeColumn->setPosition(1.8f, 1.8f, 0.0f);
    pipeColumn->setDeformation(0.18f, 1.0f, 0.18f);
    pipeColumn->setColour(0.55f, 0.58f, 0.60f, 1.0f);  // silver pipe
    rememberPart(pipeColumn);

    pipeElbow = new sphere(12);
    pipeElbow->setParent(pipeColumn);
    pipeElbow->setPosition(0.0f, 1.15f, 0.0f);
    pipeElbow->setDeformation(0.22f, 0.22f, 0.22f);
    pipeElbow->setColour(0.55f, 0.58f, 0.60f, 1.0f);
    rememberPart(pipeElbow);

    // ---------------------------------------------------------------
    // EXTRUSION: L-shaped nozzle head (clearly visible, dispensing tip)
    // ---------------------------------------------------------------
    //nozzle = new extrusion("pump_nozzle_profile.txt", "pump_nozzle_path.txt");
    //nozzle->setParent(pipeElbow);
    //nozzle->setPosition(0.0f, 0.12f, 0.0f);
    //nozzle->setDeformation(0.9f, 0.9f, 0.9f);
    //nozzle->setColour(0.70f, 0.72f, 0.10f, 1.0f);  // gold matches base ring
    //rememberPart(nozzle);

    // ---------------------------------------------------------------
    // SHELF  (small platform where cup rests under nozzle)
    // ---------------------------------------------------------------
    shelf = new cube();
    shelf->setParent(mainBody);
    shelf->setPosition(1.8f, -0.35f, 0.0f);
    shelf->setDeformation(0.55f, 0.08f, 0.55f);
    shelf->setColour(0.35f, 0.37f, 0.40f, 1.0f);   // dark metal shelf
    rememberPart(shelf);

    // ---------------------------------------------------------------
    // CUP  (cylinder sitting on shelf ¨C robot will pick this up)
    // ---------------------------------------------------------------
    cup = new cylinder(16);
    cup->setParent(shelf);
    cup->setPosition(0.0f, 0.43f, 0.0f);
    cup->setDeformation(0.22f, 0.35f, 0.22f);
    cup->setColour(0.95f, 0.95f, 0.95f, 1.0f);     // white paper cup
    rememberPart(cup);

    // ---------------------------------------------------------------
    // WATER CUBES  (5 small blue cubes, animated to fall into cup)
    // Start hidden, shown and animated during dispense phase
    // All positioned at nozzle tip initially, fall into cup
    // ---------------------------------------------------------------
    for (int i = 0; i < NUM_WATER_CUBES; i++)
    {
        waterCubes[i] = new cube();
        waterCubes[i]->setParent(pipeElbow);           // near nozzle tip
        waterCubes[i]->setPosition(0.35f, -0.1f, 0.0f); // nozzle exit point
        waterCubes[i]->setDeformation(0.12f, 0.12f, 0.12f);
        waterCubes[i]->setColour(0.10f, 0.55f, 1.0f, 0.85f); // semi-transparent blue
        waterCubes[i]->hide();
        rememberPart(waterCubes[i]);
    }

    gShapeVector.push_back(this);
}

WaterPumpStation::~WaterPumpStation() {}

void WaterPumpStation::rememberPart(object3d* p)
{
    parts.push_back(p);
}

void WaterPumpStation::show()
{
    object3d::show();
    for (auto p : parts) p->show();
    // keep water cubes hidden until animation triggers them
    for (int i = 0; i < NUM_WATER_CUBES; i++)
        waterCubes[i]->hide();
}

void WaterPumpStation::hide()
{
    object3d::hide();
    for (auto p : parts) p->hide();
}

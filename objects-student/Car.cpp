// *****************************************************************************************
// KXC354 - Computer Graphics & Animation
// Assignment 1 & 2
// Student Letter Implementation
// *****************************************************************************************

#include "prefix.h"
#include "utility.h"
#include "car.h"
#include "carfronts.h"   // ADD THIS

extern vector<object3d*> gShapeVector;

car::car()
{
    setName("car");

    base = new cube;
    base->setColour(1.0, 0.0, 2.5, 1.0);
    base->setParent(this);
    base->setDeformation(6.0, 0.2, 3.0);
    base->setPosition(3.0, 0.0, 0.0);

    container = new cube;
    container->setColour(1.0, 1.0, 1.0, 1.0);
    container->setParent(base);
    container->setDeformation(4.0, 3.0, 3.0);
    container->setPosition(-2.0, 3.2, 0.0);

    engine = new cube;
    engine->setColour(1.0, 1.0, 1.0, 1.0);
    engine->setParent(base);
    engine->setDeformation(2.0, 1.5, 3.0);
    engine->setPosition(4.0, 1.7, 0.0);

    frontshape = new carfronts;
    frontshape->setColour(1.0, 0.0, 2.5, 1.0);
    frontshape->setParent(base);
    frontshape->setDeformation(2.0, 1.0, 4.0);
    frontshape->setPosition(4.0, 4.2, -1.0);   // YOUR ORIGINAL POSITION

    for (int i = 0; i < 4; i++)
    {
        wheels[i] = new wheel(1.0, 20);
    }

    wheels[0]->setColour(0.3, 0.3, 0.3, 1.0);
    wheels[0]->setParent(base);
    wheels[0]->setDeformation(1.0, 0.5, 1.0);
    wheels[0]->setRotation('x', 90.0);
    wheels[0]->setPosition(4.0, -1.1, 2.5);

    wheels[1]->setColour(0.3, 0.3, 0.3, 1.0);
    wheels[1]->setParent(base);
    wheels[1]->setDeformation(1.0, 0.5, 1.0);
    wheels[1]->setRotation('x', 90.0);
    wheels[1]->setPosition(-4.0, -1.1, 2.5);

    wheels[2]->setColour(0.3, 0.3, 0.3, 1.0);
    wheels[2]->setParent(base);
    wheels[2]->setDeformation(1.0, 0.5, 1.0);
    wheels[2]->setRotation('x', 90.0);
    wheels[2]->setPosition(4.0, -1.1, -2.5);

    wheels[3]->setColour(0.3, 0.3, 0.3, 1.0);
    wheels[3]->setParent(base);
    wheels[3]->setDeformation(1.0, 0.5, 1.0);
    wheels[3]->setRotation('x', 90.0);
    wheels[3]->setPosition(-4.0, -1.1, -2.5);

    for (int i = 0; i < 10; i++)
    {
        lights[i] = new sphere(20);
    }

    // Front light 
    lights[0]->setColour(0.8, 0.8, 0.0, 1.0);
    lights[0]->setParent(engine);
    lights[0]->setDeformation(0.3, 0.3, 0.3);
    lights[0]->setPosition(2.3, 1.0, 2.7);

    lights[1]->setColour(0.8, 0.8, 0.0, 1.0);
    lights[1]->setParent(engine);
    lights[1]->setDeformation(0.3, 0.3, 0.3);
    lights[1]->setPosition(2.3, 1.0, -2.7);

    lights[2]->setColour(0.8, 0.8, 0.0, 1.0);
    lights[2]->setParent(engine);
    lights[2]->setDeformation(0.3, 0.3, 0.3);
    lights[2]->setPosition(2.3, 1.0, 2.2);

    lights[3]->setColour(0.8, 0.8, 0.0, 1.0);
    lights[3]->setParent(engine);
    lights[3]->setDeformation(0.3, 0.3, 0.3);
    lights[3]->setPosition(2.3, 1.0, -2.2);

    //back lights
    lights[4]->setColour(1.0, 0.0, 0.0, 1.0);
    lights[4]->setParent(container);
    lights[4]->setDeformation(0.3, 0.3, 0.3);
    lights[4]->setPosition(-4.3, -1.5, 2.7);

    lights[6]->setColour(1.0, 0.0, 0.0, 1.0);
    lights[6]->setParent(container);
    lights[6]->setDeformation(0.3, 0.3, 0.3);
    lights[6]->setPosition(-4.3, -2.0, 2.7);

    lights[8]->setColour(1.0, 0.0, 0.0, 1.0);
    lights[8]->setParent(container);
    lights[8]->setDeformation(0.3, 0.3, 0.3);
    lights[8]->setPosition(-4.3, -2.5, 2.7);

    lights[5]->setColour(1.0, 0.0, 0.0, 1.0);
    lights[5]->setParent(container);
    lights[5]->setDeformation(0.3, 0.3, 0.3);
    lights[5]->setPosition(-4.3, -1.5, -2.7);

    lights[7]->setColour(1.0, 0.0, 0.0, 1.0);
    lights[7]->setParent(container);
    lights[7]->setDeformation(0.3, 0.3, 0.3);
    lights[7]->setPosition(-4.3, -2.0, -2.7);

    lights[9]->setColour(1.0, 0.0, 0.0, 1.0);
    lights[9]->setParent(container);
    lights[9]->setDeformation(0.3, 0.3, 0.3);
    lights[9]->setPosition(-4.3, -2.5, -2.7);

    gShapeVector.push_back(this);
}

// FIXED show() and hide()
void car::show()
{
    base->show();
    container->show();
    engine->show();
    frontshape->show();
    for (int i = 0; i < 4; i++) wheels[i]->show();
    for (int i = 0; i < 10; i++) lights[i]->show();
}

void car::hide()
{
    base->hide();
    container->hide();
    engine->hide();
    frontshape->hide();
    for (int i = 0; i < 4; i++) wheels[i]->hide();
    for (int i = 0; i < 10; i++) lights[i]->hide();
}
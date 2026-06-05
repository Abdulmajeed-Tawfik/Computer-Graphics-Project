#include "prefix.h"
#include "Chair.h"
#include "cube.h"

Chair::Chair()
{
    // Seat
    seat = new cube();
    seat->setParent(this);
    seat->setPosition(0.0f, 0.9f, 0.0f);
    seat->setDeformation(1.3f, 0.12f, 1.1f);
    seat->setColour(0.45f, 0.28f, 0.15f); // brown wood
    rememberPart(seat);

    // Backrest
    backrest = new cube();
    backrest->setParent(seat);
    backrest->setPosition(0.0f, 1.2f, -1.0f);
    backrest->setDeformation(1.25f, 1.2f, 0.11f);
    backrest->setColour(0.45f, 0.28f, 0.15f);
    rememberPart(backrest);

    // Four legs
    legFrontLeft = new cube();
    legFrontLeft->setParent(seat);
    legFrontLeft->setPosition(-1.2f, -1.0f, 1.0f);
    legFrontLeft->setDeformation(0.11f, 0.9f, 0.11f);
    legFrontLeft->setColour(0.35f, 0.20f, 0.10f);
    rememberPart(legFrontLeft);

    legFrontRight = new cube();
    legFrontRight->setParent(seat);
    legFrontRight->setPosition(1.2f, -1.0f, 1.0f);
    legFrontRight->setDeformation(0.11f, 0.9f, 0.11f);
    legFrontRight->setColour(0.35f, 0.20f, 0.10f);
    rememberPart(legFrontRight);

    legBackLeft = new cube();
    legBackLeft->setParent(seat);
    legBackLeft->setPosition(-1.2f, -1.0f, -1.0f);
    legBackLeft->setDeformation(0.11f, 0.9f, 0.11f);
    legBackLeft->setColour(0.35f, 0.20f, 0.10f);
    rememberPart(legBackLeft);

    legBackRight = new cube();
    legBackRight->setParent(seat);
    legBackRight->setPosition(1.2f, -1.0f, -1.0f);
    legBackRight->setDeformation(0.11f, 0.9f, 0.11f);
    legBackRight->setColour(0.35f, 0.20f, 0.10f);
    rememberPart(legBackRight);
}

Chair::~Chair()
{
}

void Chair::rememberPart(object3d* part)
{
    parts.push_back(part);
}

void Chair::privateDraw(bool drawMode)
{
    // all geometry is child objects
}

void Chair::show()
{
    object3d::show();
    for (auto p : parts) p->show();
}

void Chair::hide()
{
    object3d::hide();
    for (auto p : parts) p->hide();
}
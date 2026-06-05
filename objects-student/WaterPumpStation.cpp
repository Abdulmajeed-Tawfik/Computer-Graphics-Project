#include "prefix.h"
#include "WaterPumpStation.h"
#include "utility.h"
#include <cmath>

// -------------------------------------------------
// Constructor 每 Builds the full station
// -------------------------------------------------
WaterPumpStation::WaterPumpStation()
{
	// Base
	base = new cube();
	base->setParent(this);
	base->setPosition(0, 0, 0);
	base->setDeformation(3, 0.5f, 2);
	base->setColour(0.2f, 0.2f, 0.22f, 1);
	addPart(base);

	// Left Pillar
	leftPillar = new cube();
	leftPillar->setParent(base);
	leftPillar->setPosition(-1.2f, 1.5f, 0);
	leftPillar->setDeformation(0.3f, 1.5f, 0.3f);
	leftPillar->setColour(0.18f, 0.18f, 0.2f, 1);
	addPart(leftPillar);

	// Right Pillar
	rightPillar = new cube();
	rightPillar->setParent(base);
	rightPillar->setPosition(1.2f, 1.5f, 0);
	rightPillar->setDeformation(0.3f, 1.5f, 0.3f);
	rightPillar->setColour(0.18f, 0.18f, 0.2f, 1);
	addPart(rightPillar);

	// Top Beam (parented to base, so it moves with the station)
	topBeam = new cube();
	topBeam->setParent(base);
	topBeam->setPosition(0, 3.0f, 0); // Adjusted height to sit on pillars
	topBeam->setDeformation(2.8f, 0.4f, 0.4f);
	topBeam->setColour(0.15f, 0.15f, 0.17f, 1);
	addPart(topBeam);

	// Control Panel
	controlPanel = new cube();
	controlPanel->setParent(base);
	controlPanel->setPosition(0, 1.2f, 0.8f);
	controlPanel->setDeformation(1.2f, 0.8f, 0.08f);
	controlPanel->setColour(0.1f, 0.1f, 0.15f, 1);
	addPart(controlPanel);

	// Scanner Arm
	scannerArm = new cylinder();
	scannerArm->setParent(topBeam);
	scannerArm->setPosition(0, -0.5f, 0);
	scannerArm->setDeformation(0.12f, 2.0f, 0.12f);
	scannerArm->setColour(0.25f, 0.25f, 0.3f, 1);
	addPart(scannerArm);

	// Scanner Head
	scannerHead = new sphere(20);
	scannerHead->setParent(scannerArm);
	scannerHead->setPosition(0, -1.2f, 0);
	scannerHead->setScale(0.22f);
	scannerHead->setColour(1, 0.2f, 0.2f, 1);
	addPart(scannerHead);

	// Transparent Safety Cover
	transparentCover = new cube();
	transparentCover->setParent(base);
	transparentCover->setPosition(0, 0.8f, 0);
	transparentCover->setDeformation(1.8f, 1.0f, 1.2f);
	transparentCover->setColour(0.7f, 0.85f, 1.0f, 0.25f);
	transparentCover->makeTransparent();
	addPart(transparentCover);

	// Test Pump Inside
	testPump = new cylinder();
	testPump->setParent(base);
	testPump->setPosition(0, 0.8f, 0);
	testPump->setDeformation(0.4f, 0.5f, 0.4f);
	testPump->setColour(0.6f, 0.6f, 0.55f, 1);
	addPart(testPump);

	// Impeller (rotating blade)
	impeller = new sweep("impeller.txt", 20);
	impeller->setParent(testPump);
	impeller->setPosition(0, 0, 0);
	impeller->setScale(0.3f);
	impeller->setColour(0.2f, 0.2f, 0.25f, 1);
	addPart(impeller);

	// Warning Light
	warningLight = new sphere(20);
	warningLight->setParent(topBeam);
	warningLight->setPosition(0, 0.4f, 0);
	warningLight->setScale(0.25f);
	warningLight->setColour(1, 0.1f, 0.1f, 1);
	warningLight->setEmissiveColour(0.5f, 0.0f, 0.0f, 1);
	addPart(warningLight);
}

// -------------------------------------------------
// Destructor
// -------------------------------------------------
WaterPumpStation::~WaterPumpStation()
{
}

// -------------------------------------------------
// Add part to list
// -------------------------------------------------
void WaterPumpStation::addPart(object3d* part)
{
	parts.push_back(part);
}

// -------------------------------------------------
// Show / Hide
// -------------------------------------------------
void WaterPumpStation::show()
{
	for (auto p : parts) p->show();
}

void WaterPumpStation::hide()
{
	for (auto p : parts) p->hide();
}

// -------------------------------------------------
// No direct draw
// -------------------------------------------------
void WaterPumpStation::privateDraw(bool drawMode)
{
}

// -------------------------------------------------
// ANIMATION 1: Scanner moves down (16每22s)
// -------------------------------------------------
void WaterPumpStation::moveScanner(float time)
{
	float yOffset = 0;

	if (time >= 16 && time < 22)
	{
		float t = (time - 16) / 6.0f;
		// Smooth slow-in/slow-out using sine curve
		float smooth = sin_d(t * 90.0f); // t=0↙0, t=1↙1
		yOffset = -2.0f * smooth;
	}
	else if (time >= 22)
	{
		yOffset = 0;
	}

	scannerArm->setPosition(0, -0.5f + yOffset, 0);
}

// -------------------------------------------------
// ANIMATION 2: Cover lifts up (22每28s)
// -------------------------------------------------
void WaterPumpStation::openCover(float time)
{
	float y = 0.8f;

	if (time >= 22 && time < 28)
	{
		float t = (time - 22) / 6.0f;
		float smooth = sin_d(t * 90.0f); // Smooth rise
		y = 0.8f + 1.8f * smooth;
	}

	transparentCover->setPosition(0, y, 0);
}

// -------------------------------------------------
// ANIMATION 3: Impeller spins (28每35s)
// -------------------------------------------------
void WaterPumpStation::rotateImpeller(float time)
{
	if (time >= 28 && time < 35)
	{
		float speed = 720.0f;
		// Slow down at the end of the test
		if (time > 33)
		{
			float t = (time - 33) / 2.0f;
			speed *= (1.0f - t);
		}
		impeller->setRotation('y', time * speed);
	}
	else
	{
		impeller->setRotation('y', 0); // Reset rotation when not spinning
	}
}

// -------------------------------------------------
// ANIMATION 4: Warning light flashes (28每40s)
// -------------------------------------------------
void WaterPumpStation::flashWarningLight(float time)
{
	if (time < 28 || time >= 40)
	{
		warningLight->setEmissiveColour(0, 0, 0, 1);
		return;
	}

	float flashRate = 0.2f;
	// Faster flash during celebration (35-40s)
	if (time > 35) flashRate = 0.1f;

	float f = fmod(time, flashRate);
	if (f < flashRate / 2)
		warningLight->setEmissiveColour(1, 0.2f, 0.2f, 1);
	else
		warningLight->setEmissiveColour(0.2f, 0.05f, 0.05f, 1);
}
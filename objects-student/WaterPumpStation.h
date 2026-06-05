#ifndef _WaterPumpStation_H
#define _WaterPumpStation_H

#include "object3d.h"
#include "cube.h"
#include "cylinder.h"
#include "sphere.h"
#include "sweep.h"
#include "texture.h"
#include <vector>

class WaterPumpStation : public object3d
{
private:
	// Main structure
	cube* base;
	cube* leftPillar;
	cube* rightPillar;
	cube* topBeam;
	cube* controlPanel;

	// Moving parts
	cylinder* scannerArm;
	sphere* scannerHead;
	cube* transparentCover;
	cylinder* testPump;
	sweep* impeller;
	sphere* warningLight;

	// Store parts for show/hide
	std::vector<object3d*> parts;
	void addPart(object3d* part);

public:
	WaterPumpStation();
	virtual ~WaterPumpStation();

	virtual void hide(void);
	virtual void show(void);
	virtual void privateDraw(bool drawMode);

	// ANIMATION FUNCTIONS
	void moveScanner(float time);
	void openCover(float time);
	void rotateImpeller(float time);
	void flashWarningLight(float time);
};

#endif
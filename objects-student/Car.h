#ifndef _CAR_H
#define _CAR_H



// -----------------------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------------------
#include "face.h"
#include "object3d.h"
#include "sphere.h"
#include "carfronts.h"
#include "cube.h"
#include "wheel.h"


// -----------------------------------------------------------------------------------------
// class declaration
// -----------------------------------------------------------------------------------------

class car : public object3d
{
private:
	cube* base, * container, * engine;
	carfronts* frontshape;
	wheel* wheels[4];
	sphere* lights[10];

public: 
	car();
	virtual void hide(void);
	virtual void show(void);
	virtual void moveX(int x, float t, int dir);
	virtual void reverse(int x, float t);
	virtual void accelerate(int x, float t);

	/*virtual void accelerateFB(double,int);
	virtual void accelerateB(double,int);*/
	//virtual void turnRL(double);
};


#endif // _CUBE_H


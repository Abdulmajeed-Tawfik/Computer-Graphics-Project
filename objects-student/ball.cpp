// *****************************************************************************************
// KXC354 - Computer Graphics & Animation - 2014
// Assignment 1 & 2
// 3D Engine Code
// *****************************************************************************************
//
// Author: Tony Gray
//
// sphere.cpp
//
// This file defines the class for sphere objects



// -----------------------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------------------
#include "prefix.h"
#include "ball.h"
#include "utility.h"



// -----------------------------------------------------------------------------------------
// globals
// -----------------------------------------------------------------------------------------
extern vector<object3d*> gShapeVector;



// -----------------------------------------------------------------------------------------
// default constructor
// -----------------------------------------------------------------------------------------

ball::ball(int density)
{

	setColour(1.0, 0.0, 0.0);					// default colour (red)
	setName("ball");
	s = new sphere(50);

	
	/*c = new cube;
	c->setDeformation(0.5, 4.0, 1.0);
	c->setOffset(0.0, -4.0, 0.0);
	c->setPosition(0.0, 4.0, 0.0);
	gShapeVector.push_back(this);*/
}



void ball::kick(int x, int y, float t, int dirX, int dirY) {


	
	s->setPosition(x + (dirX * t), y + abs((dirY * sin(t))), 0);

}


//void ball::walk(float t) {
//
//
//	//float x = sin(t)*90.0;
//	float angle = 30.0 * sin_d(t * 180.0);
//	c->setRotation('z', angle);
//
//}



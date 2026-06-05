// *****************************************************************************************
// KXC354 - Computer Graphics & Animation - 2014
// Assignment 1 & 2
// 3D Engine Code
// *****************************************************************************************
//
// Author: Tony Gray
//
// cube.cpp
//
// This file defines the class for cube objects



// -----------------------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------------------
#include "prefix.h"
#include "simplecomposite.h"
#include "utility.h"



// -----------------------------------------------------------------------------------------
// globals
// -----------------------------------------------------------------------------------------
extern vector<object3d*> gShapeVector;



// -----------------------------------------------------------------------------------------
// constructor
// -----------------------------------------------------------------------------------------

simplecomposite::simplecomposite()
{
	// Initialise the object's state
	setName("simplecomposite");
	setColour(1.0, 0.0, 0.0, 1.0);					// default colour

	py = new pyramid;
	py->setParent(this);
	py->setPosition(0.0, 0.0, 0.0);

	to1 = new torus(50, 50, 0.2, 0.1);
	to1->setParent(py);
	to1->setPosition(-0.9, -1.3, 1.0);
	to1->setRotation('z', 90);
	
	to2 = new torus(50, 50, 0.2, 0.1);
	to2->setParent(py);
	to2->setPosition(0.9, -1.3, 1.0);
	to2->setRotation('z', 90);

	to3 = new torus(50, 50, 0.2, 0.1);
	to3->setParent(py);
	to3->setPosition(0.9, -1.3, -1.0);
	to3->setRotation('z', 90);

	to4 = new torus(50, 50, 0.2, 0.1);
	to4->setParent(py);
	to4->setPosition(-0.9, -1.3, -1.0);
	to4->setRotation('z', 90);

	sp1 = new sphere(50);
	sp1->setColour(0.1, 1.0, 1.0, 1.0);
	sp1->setDeformation(.1, .5, .5);
	sp1->setRotation('z', -180 * atan(2.0));
	sp1->setPosition(-0.7, -0.2, 0.0);
	sp1->setParent(py);
	

	sp2 = new sphere(50);
	sp2->setColour(0.1, 1.0, 1.0, 1.0);
	sp2->setDeformation(.1, .5, .5);
	sp2->setRotation('z', 180 * atan(2.0));
	sp2->setPosition(0.7, -0.2, 0.0);
	sp2->setParent(py);

	ex1 = new extrusion("profilesample.txt", "sample_path.txt");
	ex1->setColour(0.5, 1.0, 0.0, 1.0);
	ex1->setDeformation(.5, .5, .1);
	ex1->setRotation('x', 125);
	ex1->setPosition(0.0, 0.8, 0.0);
	ex1->setParent(py);

	sw1 = new sweep("profileSweep.txt", 50);
	sw1->setParent(py);
	sw1->setColour(2.0, 0.0, 3.0, 1.0);	
	sw1->setDeformation(.3, .3, .1);
	sw1->setRotation('y', 90);
	sw1->setRotation('z', 90);
	sw1->setPosition(0.0, 1.6, 0.0);
	sw1	->setParent(py);

	// calculate the face and vertex normal
	
	
	// put the shape onto the shapeVector so it gets draw messages
	gShapeVector.push_back(this);
}

void simplecomposite::hide() {
	py->hide();
	to1->hide();
	to2->hide();
	to3->hide();
	to4->hide();
	sp1->hide();
	sp2->hide();
	ex1->hide();
	sw1->hide();
}
void simplecomposite::show() {
	py->show();
	to1->show();
	to2->show();
	to3->show();
	to4->show();
	sp1->show();
	sp2->show();
	ex1->show();
	sw1->show();

}


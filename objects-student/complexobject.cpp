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
#include "complexobject.h"
#include "utility.h"



// -----------------------------------------------------------------------------------------
// globals
// -----------------------------------------------------------------------------------------
extern vector<object3d*> gShapeVector;



// -----------------------------------------------------------------------------------------
// constructor
// -----------------------------------------------------------------------------------------

complexobject::complexobject()
{
	// Initialise the object's state
	setName("complexobject");
	sheead = new cube;
	sheead->setParent(this);
	sheead->setColour(1.0, 1.0, 1.0, 1.0);
	sheead->setDeformation(.6,.5,.5);
	sheead->setPosition(0.0, 4.2, 0.0);

	hear = new cube;
	hear->setParent(sheead);
	hear->setColour(1.0, 1.0, 0.0, 1.0);
	hear->setDeformation(.6, .2, .5);
	hear->setPosition(0.0, 0.6, 0.0);
	
	h1 = new cube;
	h1->setParent(hear);
	h1->setColour(1.0, 1.0, 0.0, 1.0);
	h1->setDeformation(.1, .1, .5);
	h1->setPosition(0.5, 0.3, 0.0);
	h1->setRotation('z', 90);

	h2 = new cube;
	h2->setParent(hear);
	h2->setColour(1.0, 1.0, 0.0, 1.0);
	h2->setDeformation(.1, .1, .5);
	h2->setPosition(0.2, 0.3, 0.0);
	h2->setRotation('z', 90);

	h3 = new cube;
	h3->setParent(hear);
	h3->setColour(1.0, 1.0, 0.0, 1.0);
	h3->setDeformation(.1, .1, .5);
	h3->setPosition(-0.2, 0.3, 0.0);
	h3->setRotation('z', 90);

	h4 = new cube;
	h4->setParent(hear);
	h4->setColour(1.0, 1.0, 0.0, 1.0);
	h4->setDeformation(.1, .1, .5);
	h4->setPosition(-0.5, 0.3, 0.0);
	h4->setRotation('z', 90);

	crown = new sphere(50);
	crown->setParent(hear);
	crown->setColour(0.8, 0.8, 2.0, 1.0);
	crown->setDeformation(0.05, 0.1, 0.00011);
	crown->setPosition(0.0, 0.0, 0.52);
	crown->setRotation('y', 180);	

	eye1 = new sphere(50);
	eye1->setParent(sheead);
	eye1->setColour(1.0, 0.0, 1.0,1.0);
	eye1->setDeformation(0.1, 0.1, 0.00011);
	eye1->setPosition(0.3, 0.25,0.52);
	eye1->setRotation('y', 180);
	

	mouth = new sphere(50);
	mouth->setParent(sheead);
	mouth->setColour(1.0, 0.0, 1.0, 1.0);
	mouth->setDeformation(0.25, 0.1, 0.00011);
	mouth->setPosition(0.0, -0.2, 0.52);
	mouth->setRotation('y', 180);

	eye2 = new sphere(50);
	eye2->setParent(sheead);
	eye2->setColour(1.0, 0.0, 1.0, 1.0);
	eye2->setDeformation(0.1, 0.1, 0.00011);
	eye2->setPosition(-0.3, 0.25, 0.52);
	eye2->setRotation('y', 180);

	body = new cube;
	body->setParent(sheead);
	body->setColour(0.0, 0.0, 1.0, 1.0);
	body->setDeformation(0.6, 0.8, 0.3);
	body->setPosition(0.0, -1.5, 0.0);
	

	arm1 = new cube;
	arm1->setParent(body);
	arm1->setColour(0.0, 1.0, 1.0, 1.0);
	arm1->setDeformation(0.2, 0.7, 0.3);
	arm1->setPosition(1.0, 0.1, 0.0);

	arm1c = new cube;
	arm1c->setParent(arm1);
	arm1c->setColour(1.0, 1.0, 1.0, 1.0);
	arm1c->setDeformation(0.2, 0.1, 0.3);
	arm1c->setPosition(0.0, -0.8, 0.0);

	arm2 = new cube;
	arm2->setParent(body);
	arm2->setColour(0.0, 1.0, 1.0, 1.0);
	arm2->setDeformation(0.2, 0.7, 0.3);
	arm2->setPosition(-1.0, 0.1, 0.0);

	arm2c = new cube;
	arm2c->setParent(arm2);
	arm2c->setColour(1.0, 1.0, 1.0, 1.0);
	arm2c->setDeformation(0.2, 0.1, 0.3);
	arm2c->setPosition(0.0, -0.8, 0.0);

	leg1 = new cube;
	leg1->setParent(body);
	leg1->setColour(0.0, 1.0, 1.0, 1.0);
	leg1->setDeformation(0.2, 0.7, 0.3);
	leg1->setPosition(0.4, -1.6, 0.0);

	leg1c = new cube;
	leg1c->setParent(leg1);
	leg1c->setColour(1.0, 1.0, 1.0, 1.0);
	leg1c->setDeformation(0.2, 0.1, 0.3);
	leg1c->setPosition(0.0, -0.8, 0.0);

	leg2 = new cube;
	leg2->setParent(body);
	leg2->setColour(0.0, 1.0, 1.0, 1.0);
	leg2->setDeformation(0.2, 0.7, 0.3);
	leg2->setPosition(-0.4, -1.6, 0.0);

	leg2c = new cube;
	leg2c->setParent(leg2);
	leg2c->setColour(1.0, 1.0, 1.0, 1.0);
	leg2c->setDeformation(0.2, 0.1, 0.3);
	leg2c->setPosition(0.0, -0.8, 0.0);

	/*e1 = new extrusion("profilesample_sharp.txt", "sample_pathsharp.txt");
	e1->setParent(sheead);
	e1->setColour(1.0, 0.0, 1.0, 1.0);
	e1->setPosition(2.5, -1.5, 0.5);

	s1 = new sweep("profile_sharp.txt",50);
	s1->setParent(sheead);
	s1->setColour(1.0, 0.0, 1.0, 1.0);
	s1->setPosition(-3.5, -1.5, 0.0);	
	s1->setScale(0.5);
	s1->setRotation('z', 90);*/

	

	/*neck = new cylinder(50);
	neck->setParent(sheead);
	neck->setColour(1.0, 0.0, 1.0, 1.0);
	neck->setDeformation(0.1, 0.1, 0.00011);
	neck->setPosition(-0.3, 0.25, 0.52);
	neck->setRotation('y', 180);*/


	// calculate the face and vertex normals
	//calculateNormals();
	
	
	// put the shape onto the shapeVector so it gets draw messages
	gShapeVector.push_back(this);
}



void complexobject::hide()
{
	sheead->hide();

	eye1->hide();
	eye2->hide();
	mouth->hide();
	crown->hide();

	body->hide();
	arm1->hide();
	arm2->hide();
	leg1->hide();
	leg2->hide();

	hear->hide();
	h1->hide();
	h2->hide();
	h3->hide();
	h4->hide();

	arm1c->hide();
	arm2c->hide();
	leg1c->hide();
	leg2c->hide();

	/*e1->hide();
	s1->hide()*/
}

void complexobject::show()
{
	sheead->show();

	eye1->show();
	eye2->show();
	mouth->show();
	crown->show();

	body->show();
	arm1->show();
	arm2->show();
	leg1->show();
	leg2->show();

	hear->show();
	h1->show();
	h2->show();
	h3->show();
	h4->show();

	arm1c->show();
	arm2c->show();
	leg1c->show();
	leg2c->show();

	/*e1->show();
	s1->show();*/
}
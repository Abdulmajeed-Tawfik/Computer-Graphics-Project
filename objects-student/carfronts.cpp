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
#include "carfronts.h"
#include "utility.h"



// -----------------------------------------------------------------------------------------
// globals
// -----------------------------------------------------------------------------------------
extern vector<object3d*> gShapeVector;



// -----------------------------------------------------------------------------------------
// constructor
// -----------------------------------------------------------------------------------------

carfronts::carfronts()
{
	// Initialise the object's state
	setName("carfronts");
	setColour(0.15, .85, .35, 1.0);					// default colour

	vertexCount = 6;
	faceCount = 4;
	polygonCount = 4;

	// allocate memory for the vertex and face arrays
	vertices.resize(vertexCount);
	faces.resize(faceCount);


	// Initialise the cube's vertices to create a cube centered around the origin
	vertices[0].set(-1, 1, 1);				// front, top, left
	vertices[1].set(-1, -1, 1);				// front, top, right
	vertices[2].set(1, -1, 1);				// front, bot, right
	vertices[3].set(-1, 1, -1);				// front, bot, left
	vertices[4].set(-1, -1, -1);				// back,  top, left
	vertices[5].set(1, -1, -1);			// back,  bot, left


	// now set up the faces - note that the vertex order is always
	// specified counter-clockwise when that face is viewed front on
	faces[0].init(0, 1, 2);					// front
	faces[1].init(0, 2, 5, 3);					// right
	faces[2].init(3, 5, 4);					// back
	faces[3].init(0, 3, 4, 1);							// bottom
	
	
	
	// calculate the face and vertex normals
	calculateNormals();
	
	
	// put the shape onto the shapeVector so it gets draw messages
	gShapeVector.push_back(this);
}




// *****************************************************************************************
// KXC354 - Computer Graphics & Animation - 2014
// Assignment 1 & 2
// 3D Engine Code
// *****************************************************************************************
//
// Author: Tony Gray
//
// cube.h
//
// This file declares the class for cube objects, based on the
// generic 3D object


#ifndef _COMPLEXOBJECT_H
#define _COMPLEXOBJECT_H



// -----------------------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------------------
#include "face.h"
#include "object3d.h"
#include "sweep.h"
#include "sphere.h"
#include "cylinder.h"
#include "cube.h"
#include "extrusion.h"

// -----------------------------------------------------------------------------------------
// class declaration
// -----------------------------------------------------------------------------------------

class complexobject : public object3d
{
	private:
		cube* sheead;
		sphere * eye1, * eye2, *mouth,* crown;
		cube* body, * arm1,* arm2, * leg1, * leg2,* hear,* h1,* h2,* h3, *h4,* arm1c,* arm2c,* leg1c,* leg2c;
		/*extrusion* e1;
		sweep* s1;*/

	public:
		complexobject();
		virtual void hide();
		virtual void show();
};


#endif // _COMPLEXOBJECT_H


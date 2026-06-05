// *****************************************************************************************
// KXC354 - Computer Graphics & Animation - 2014
// Assignment 1 & 2
// 3D Engine Code
// *****************************************************************************************
//
// wheel.h
//
// This file declares the class for wheel objects, based on the
// generic 3D object
// *****************************************************************************************

#ifndef _WHEEL_H
#define _WHEEL_H

#include "face.h"
#include "object3d.h"

class wheel : public object3d
{
public:
    // radius controls the size of the wheel
    // density controls how smooth the circle is
    // height = 2 units, origin is in the center
    wheel(double radius, int density);
};

#endif
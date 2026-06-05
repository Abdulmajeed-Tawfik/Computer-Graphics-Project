// *****************************************************************************************
// KXC354 - Computer Graphics & Animation - 2014
// Assignment 1 & 2
// 3D Engine Code
// *****************************************************************************************
//
// wheel.cpp
//
// This file defines the class for wheel objects
// *****************************************************************************************

#include "prefix.h"
#include "wheel.h"
#include "utility.h"

extern vector<object3d*> gShapeVector;

wheel::wheel(double radius, int density)
{
    setName("wheel");
    setColour(0.15, 0.85, 0.35, 1.0);

    // Make sure the wheel has at least 3 sides
    if (density < 3)
        density = 3;

    // Top ring + bottom ring + 2 centre vertices
    vertexCount = 2 * density + 2;

    // Top triangles + bottom triangles + side quads
    faceCount = 3 * density;
    polygonCount = faceCount;

    vertices.resize(vertexCount);
    faces.resize(faceCount);

    // Create circle vertices
    for (int i = 0; i < density; i++)
    {
        float angle = i * (360.0f / (float)density);

        float x = (float)(radius * cos_d(angle));
        float z = (float)(radius * sin_d(angle));

        // height = 2, so y goes from +1 to -1
        vertices[i].set(x, 1.0f, z);                  // top ring
        vertices[i + density].set(x, -1.0f, z);       // bottom ring
    }

    // Centre points
    int topCentre = 2 * density;
    int bottomCentre = 2 * density + 1;

    vertices[topCentre].set(0.0f, 1.0f, 0.0f);
    vertices[bottomCentre].set(0.0f, -1.0f, 0.0f);

    // Create faces
    for (int i = 0; i < density; i++)
    {
        int j = (i + 1) % density;

        // Top face triangle
        faces[i].init(topCentre, j, i);

        // Bottom face triangle
        faces[i + density].init(bottomCentre, i + density, j + density);

        // Side face quad
        faces[i + 2 * density].init(i, j, j + density, i + density);
    }

    calculateNormals();

    gShapeVector.push_back(this);
}
#include "prefix.h"
#include "pyramid.h"
#include "utility.h"

// -----------------------------------------------------------------------------------------
// globals
// -----------------------------------------------------------------------------------------
extern vector<object3d*> gShapeVector;


// -----------------------------------------------------------------------------------------
// constructor
// -----------------------------------------------------------------------------------------

pyramid::pyramid()
{
    // Initialise the object's state
    setName("pyramid");
    setColour(1.0, 0.0, 0.0, 1.0);   // default red colour

    vertexCount = 5;
    faceCount = 5;
    polygonCount = 5;

    // allocate memory for the vertex and face arrays
    vertices.resize(vertexCount);
    faces.resize(faceCount);

    // Pyramid vertices
    vertices[0].set(0, 1, 0);      // top point

    vertices[1].set(-1, -1, 1);     // front-left
    vertices[2].set(1, -1, 1);     // front-right
    vertices[3].set(1, -1, -1);     // back-right
    vertices[4].set(-1, -1, -1);     // back-left

    // Pyramid faces
    // Vertex order is counter-clockwise when viewed from outside

    faces[0].init(0, 1, 2);          // front triangular face
    faces[1].init(0, 2, 3);          // right triangular face
    faces[2].init(0, 3, 4);          // back triangular face
    faces[3].init(0, 4, 1);          // left triangular face

    faces[4].init(1, 4, 3, 2);       // bottom square base

    // calculate the face and vertex normals
    calculateNormals();

    // put the shape onto the shapeVector so it gets draw messages
    gShapeVector.push_back(this);
}
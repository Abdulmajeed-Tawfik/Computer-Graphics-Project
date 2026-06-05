// *****************************************************************************************
// KXC354 - Computer Graphics & Animation
// Assignment 1 & 2
// Student Letter Implementation
// *****************************************************************************************

#include "prefix.h"
#include "letterA.h"
#include "utility.h"

extern vector<object3d*> gShapeVector;

letterA::letterA()
{
    setName("letterA");
    setColour(0.0, 0.0, 1.0, 1.0);

    // Shape is built from 22 points (11 front + 11 back)
    // and 27 polygonal faces total
    const int NUM_PTS = 22;
    const int NUM_FACES = 27;

    vertices.resize(NUM_PTS);
    faces.resize(NUM_FACES);

    vertexCount = NUM_PTS;
    faceCount = NUM_FACES;

    // ------------------------------------------------------------------
    // Coordinate system:
    //   X axis : -0.7 (left)  to +0.7 (right)
    //   Y axis : -1.0 (bottom) to +1.0 (top)
    //   Z axis : +0.25 (front face) / -0.25 (back face)
    // ------------------------------------------------------------------
    const float zNear = 0.25f;
    const float zFar = -0.25f;

    // ---- FRONT OUTLINE (z = +0.25) ----
    // Outer silhouette going clockwise from top-right
    vertices[0].set(0.25f, 1.0f, zNear);   // apex right
    vertices[1].set(0.7f, -1.0f, zNear);   // foot outer-right
    vertices[2].set(0.3f, -1.0f, zNear);   // foot inner-right
    vertices[3].set(0.15f, -0.6f, zNear);   // crossbar lower-right
    vertices[4].set(-0.15f, -0.6f, zNear);   // crossbar lower-left
    vertices[5].set(-0.3f, -1.0f, zNear);   // foot inner-left
    vertices[6].set(-0.7f, -1.0f, zNear);   // foot outer-left
    vertices[7].set(-0.25f, 1.0f, zNear);   // apex left

    // Inner triangle (hollow centre of the A)
    vertices[8].set(0.15f, -0.2f, zNear);   // inner lower-right
    vertices[9].set(-0.15f, -0.2f, zNear);   // inner lower-left
    vertices[10].set(0.0f, 0.4f, zNear);   // inner apex

    // ---- BACK OUTLINE (z = -0.25) ¡ª mirrors above ----
    vertices[11].set(0.25f, 1.0f, zFar);
    vertices[12].set(0.7f, -1.0f, zFar);
    vertices[13].set(0.3f, -1.0f, zFar);
    vertices[14].set(0.15f, -0.6f, zFar);
    vertices[15].set(-0.15f, -0.6f, zFar);
    vertices[16].set(-0.3f, -1.0f, zFar);
    vertices[17].set(-0.7f, -1.0f, zFar);
    vertices[18].set(-0.25f, 1.0f, zFar);

    // Back inner triangle
    vertices[19].set(0.15f, -0.2f, zFar);
    vertices[20].set(-0.15f, -0.2f, zFar);
    vertices[21].set(0.0f, 0.4f, zFar);

    // ==================================================================
    // SIDE WALLS  (each quad bridges a front edge to its back mirror)
    // ==================================================================
    int f = 0;

    // Outer right slant  (apex-right -> foot-outer-right)
    faces[f++].init(0, 1, 12, 11);
    // Right foot base
    faces[f++].init(1, 2, 13, 12);
    // Right leg inner slant
    faces[f++].init(2, 3, 14, 13);
    // Crossbar bottom edge
    faces[f++].init(3, 4, 15, 14);
    // Left leg inner slant
    faces[f++].init(4, 5, 16, 15);
    // Left foot base
    faces[f++].init(5, 6, 17, 16);
    // Outer left slant  (foot-outer-left -> apex-left)
    faces[f++].init(6, 7, 18, 17);
    // Top edge (apex strip)
    faces[f++].init(7, 0, 11, 18);

    // Inner hollow walls
    faces[f++].init(8, 9, 20, 19);   // hole bottom
    faces[f++].init(9, 10, 21, 20);   // hole left side
    faces[f++].init(10, 8, 19, 21);   // hole right side

    // ==================================================================
    // FRONT FACE  (tessellated triangles + quads, counter-clockwise)
    // ==================================================================
    // Upper region ¡ª fills the space from apex down to the inner triangle
    faces[f++].init(0, 7, 10);        // top-centre tri
    faces[f++].init(0, 10, 8);         // upper-right tri
    faces[f++].init(7, 9, 10);        // upper-left  tri

    // Right leg region
    faces[f++].init(0, 8, 3);         // mid-right tri
    faces[f++].init(0, 3, 2, 1);     // lower-right leg quad

    // Left leg region
    faces[f++].init(7, 4, 9);         // mid-left tri
    faces[f++].init(7, 6, 5, 4);     // lower-left  leg quad

    // Crossbar fill
    faces[f++].init(8, 9, 4, 3);     // crossbar quad

    // ==================================================================
    // BACK FACE  (winding reversed so normals point outward)
    // ==================================================================
    faces[f++].init(11, 21, 18);        // top-centre tri
    faces[f++].init(11, 19, 21);        // upper-right tri
    faces[f++].init(18, 21, 20);        // upper-left  tri

    faces[f++].init(11, 14, 19);        // mid-right tri
    faces[f++].init(11, 12, 13, 14);    // lower-right leg quad

    faces[f++].init(18, 20, 15);        // mid-left tri
    faces[f++].init(18, 15, 16, 17);    // lower-left  leg quad

    faces[f++].init(19, 14, 15, 20);    // crossbar quad

    calculateNormals();
    gShapeVector.push_back(this);
}

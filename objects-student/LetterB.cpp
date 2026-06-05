// *****************************************************************************************
// KXC354 - Computer Graphics & Animation
// Assignment 1 & 2
// Student Letter Implementation
// *****************************************************************************************

#include "prefix.h"
#include "letterB.h"
#include "utility.h"


extern vector<object3d*> gShapeVector;

letterB::letterB()
{
    setName("letterB");
    setColour(0.0, 0.0, 1.0, 1.0);

    // Shape is built from 21 points (11 front + 11 back)
    // and 27 polygonal faces total
    const int NUM_PTS = 42;
    const int NUM_FACES = 43;

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
    const float zNear = 1.0f;
    const float zFar = -1.0f;

    // ---- FRONT OUTLINE (z = +0.25) ----
    // Outer silhouette going clockwise from top-right
    vertices[0].set(-2.0f, 3.5f, zNear);   // apex right
    vertices[1].set(-2.0f, -3.5f, zNear);   // foot outer-right
    vertices[2].set(1.5f, -3.5f, zNear);   // foot inner-right
    vertices[3].set(2.5f, -2.5f, zNear);   // crossbar lower-right
    vertices[4].set(2.5,  -1.0f, zNear);   // crossbar lower-left
    vertices[5].set(1.5f, 0.0f, zNear);   // foot inner-left
    vertices[6].set(2.5f, 1.0f, zNear);   // foot outer-left
    vertices[7].set(2.5f, 2.5f, zNear);   // apex left
    vertices[8].set(1.5f, 3.5f, zNear);   // inner lower-right
    vertices[9].set(-1.0f, 3.0f, zNear);   // inner lower-left
    vertices[10].set(-1.0f, 0.5f, zNear);   // inner apex
    vertices[11].set(1.5f, 0.5f, zNear);
    vertices[12].set(2.0f, 1.0f, zNear);
    vertices[13].set(2.0f, 2.5f, zNear);
    vertices[14].set(1.5f, 3.0f, zNear);
    vertices[15].set(-1.0f, -0.5f, zNear);
    vertices[16].set(-1.0f, -3.0f, zNear);
    vertices[17].set(1.5f, -3.0f, zNear);
    vertices[18].set(2.0f, -2.5f, zNear);
    vertices[19].set(2.0f, -1.0f, zNear);
    vertices[20].set(1.5f, -0.5f, zNear);

    // back side 
    vertices[21].set(-2.0f, 3.5f, zFar);   // apex right
    vertices[22].set(-2.0f, -3.5f, zFar);   // foot outer-right
    vertices[23].set(1.5f, -3.5f, zFar);   // foot inner-right
    vertices[24].set(2.5f, -2.5f, zFar);   // crossbar lower-right
    vertices[25].set(2.5, -1.0f, zFar);   // crossbar lower-left
    vertices[26].set(1.5f, 0.0f, zFar);   // foot inner-left
    vertices[27].set(2.5f, 1.0f, zFar);   // foot outer-left
    vertices[28].set(2.5f, 2.5f, zFar);   // apex left
    vertices[29].set(1.5f, 3.5f, zFar);   // inner lower-right
    vertices[30].set(-1.0f, 3.0f, zFar);   // inner lower-left
    vertices[31].set(-1.0f, 0.5f, zFar);   // inner apex
    vertices[32].set(1.5f, 0.5f, zFar);
    vertices[33].set(2.0f, 1.0f, zFar);
    vertices[34].set(2.0f, 2.5f, zFar);
    vertices[35].set(1.5f, 3.0f, zFar);
    vertices[36].set(-1.0f, -0.5f, zFar);
    vertices[37].set(-1.0f, -3.0f, zFar);
    vertices[38].set(1.5f, -3.0f, zFar);
    vertices[39].set(2.0f, -2.5f, zFar);
    vertices[40].set(2.0f, -1.0f, zFar);
    vertices[41].set(1.5f, -0.5f, zFar);

   // vertices[21].set(0.0f, 0.4f, zFar);

    // ==================================================================
    // SIDE WALLS  (each quad bridges a front edge to its back mirror)
    // ==================================================================
    int f = 0;

    
    faces[f++].init(0, 1, 16, 9);
   
    faces[f++].init(16, 1, 2, 17);
    
    faces[f++].init(18, 17, 2, 3);
    
    faces[f++].init(19, 18, 3, 4);
    
    faces[f++].init(20, 19, 4, 5);
    
    faces[f++].init(10, 15, 20, 11);
    
    faces[f++].init(11, 20, 5);
    
    faces[f++].init(12, 11, 5, 6);
    faces[f++].init(13, 12, 6, 7);   // hole left side
    faces[f++].init(14, 13, 7, 8);   // hole right side
    faces[f++].init(0, 9, 14, 8);   // hole right side
   

    // ---------------- BACK SIDE FACES ----------------
// Same as front faces, but using back vertices and reversed order

    faces[f++].init(30, 37, 22, 21);      // from front: 0, 1, 16, 9

    faces[f++].init(38, 23, 22, 37);      // from front: 16, 1, 2, 17

    faces[f++].init(24, 23, 38, 39);      // from front: 18, 17, 2, 3

    faces[f++].init(25, 24, 39, 40);      // from front: 19, 18, 3, 4

    faces[f++].init(26, 25, 40, 41);      // from front: 20, 19, 4, 5

    faces[f++].init(32, 41, 36, 31);      // from front: 10, 15, 20, 11

    faces[f++].init(26, 41, 32);          // from front: 11, 20, 5

    faces[f++].init(27, 26, 32, 33);      // from front: 12, 11, 5, 6

    faces[f++].init(28, 27, 33, 34);      // from front: 13, 12, 6, 7

    faces[f++].init(29, 28, 34, 35);      // from front: 14, 13, 7, 8

    faces[f++].init(29, 35, 30, 21);      // from front: 0, 9, 14, 8
   

    faces[f++].init(0, 8, 29, 21);      // from front: 0, 1, 16, 9

    faces[f++].init(8, 7, 28, 29);      // from front: 16, 1, 2, 17

    faces[f++].init(7, 6, 27, 28);      // from front: 18, 17, 2, 3

    faces[f++].init(6, 5, 26, 27);      // from front: 19, 18, 3, 4

    faces[f++].init(5, 4, 25, 26);      // from front: 20, 19, 4, 5

    faces[f++].init(4, 3, 24, 25);      // from front: 10, 15, 20, 11

    faces[f++].init(3, 2, 23, 24);      // from front: 19, 18, 3, 4

    faces[f++].init(2, 1, 22, 23);      // from front: 20, 19, 4, 5

    faces[f++].init(0, 21, 22, 1);      // from front: 10, 15, 20, 11
    

    // inner  faces

    faces[f++].init(9, 30, 35, 14);      // from front: 0, 1, 16, 9

    faces[f++].init(14, 35, 34, 13);      // from front: 16, 1, 2, 17

    faces[f++].init(13, 34, 33, 12);      // from front: 18, 17, 2, 3

    faces[f++].init(12, 33, 32, 11);      // from front: 19, 18, 3, 4

    faces[f++].init(10, 11, 32, 31);      // from front: 20, 19, 4, 5

    faces[f++].init(9, 10, 31, 30);      // from front: 10, 15, 20, 11



    faces[f++].init(15, 36, 41, 20);      // from front: 0, 1, 16, 9

    faces[f++].init(20, 41, 40, 19);      // from front: 16, 1, 2, 17

    faces[f++].init(19, 40, 39, 18);      // from front: 18, 17, 2, 3

    faces[f++].init(18, 39, 38, 17);      // from front: 19, 18, 3, 4

    faces[f++].init(16, 17, 38, 37);      // from front: 20, 19, 4, 5

    faces[f++].init(15, 16, 37, 36);      // from front: 10, 15, 20, 11


    calculateNormals();
    gShapeVector.push_back(this);
}

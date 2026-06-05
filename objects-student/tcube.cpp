// =========================================================================================
// Computer Graphics  - 2019
// 3D Engine Code
// =========================================================================================
//
// tcube.cpp
//
// This file defines the class for textured cubes
// =========================================================================================



// -----------------------------------------------------------------------------------------
// application includes
// -----------------------------------------------------------------------------------------
#include "prefix.h"
#include "tcube.h"
#include "utility.h"




// -----------------------------------------------------------------------------------------
// external globals
// -----------------------------------------------------------------------------------------
extern unsigned long     gPolygonCount;          // counts how many polygons get displayed each frame
extern bool              gWireFrameOnly;         // solid or wireframe drawing mode
extern vector<object3d*>  gShapeVector;




// -----------------------------------------------------------------------------------------
// constructor
// -----------------------------------------------------------------------------------------
tcube::tcube()
{
    // Initialise the object's state
    setColour(1, 1, 1, 1.0);                    // default colour

    vertexCount = 8;
    faceCount = 6;
    polygonCount = 6;

    // allocate memory for the vertex and face arrays
    vertices.resize(vertexCount);
    faces.resize(faceCount);


    // Initialise the tcube's vertices to create a tcube centered around the origin
    vertices[0].set(-1, 1, 1);                // front, top, left
    vertices[1].set(1, 1, 1);                // front, top, right
    vertices[2].set(1, -1, 1);                // front, bot, right
    vertices[3].set(-1, -1, 1);                // front, bot, left
    vertices[4].set(-1, 1, -1);                // back,  top, left
    vertices[5].set(1, 1, -1);                // back,  top, right
    vertices[6].set(1, -1, -1);                // back,  bot, right
    vertices[7].set(-1, -1, -1);                // back,  bot, left


    // now set up the faces - note that the vertex order is always
    // specified counter-clockwise when that face is viewed front on
    faces[0].init(0, 3, 2, 1);                  // front
    faces[1].init(1, 2, 6, 5);                  // right
    faces[2].init(5, 6, 7, 4);                  // back
    faces[3].init(4, 7, 3, 0);                  // left
    faces[4].init(4, 0, 1, 5);                  // top
    faces[5].init(3, 7, 6, 2);                  // bottom


    // calculate the face and vertex normals
    calculateNormals();


    // put the shape onto the shapeVector so it gets draw messages
    gShapeVector.push_back(this);
}




// -----------------------------------------------------------------------------------------
// privateDraw method
// -----------------------------------------------------------------------------------------
void tcube::privateDraw(bool drawMode)
{
    if (theTexture && !gWireFrameOnly)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, theTexture->id());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, theTexture->bestMagFilter());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, theTexture->bestMinFilter());

        glMatrixMode(GL_TEXTURE);
        glLoadIdentity();
        glScalef(textureScaleX, textureScaleY, 1.0);
        glMatrixMode(GL_MODELVIEW);
    }


    // -------------------------------------------------
    // Texture atlas layout:
    //
    //   No.1   No.2   No.3
    //   No.4   No.5   No.6
    //
    // 3 columns, 2 rows
    // -------------------------------------------------

    float x0, x1, y0, y1;

    glBegin(GL_QUADS);


    // -------------------------------------------------
    // FRONT FACE = No.1
    // -------------------------------------------------
    x0 = 0.0f / 3.0f;
    x1 = 1.0f / 3.0f;
    y0 = 1.0f / 2.0f;
    y1 = 2.0f / 2.0f;

    glNormal3fv(faces[0].faceNormal.data);

    glTexCoord2f(x0, y1);
    glVertex3fv(vertices[0].coordinate.data);       // top left

    glTexCoord2f(x0, y0);
    glVertex3fv(vertices[3].coordinate.data);       // bottom left

    glTexCoord2f(x1, y0);
    glVertex3fv(vertices[2].coordinate.data);       // bottom right

    glTexCoord2f(x1, y1);
    glVertex3fv(vertices[1].coordinate.data);       // top right



    // -------------------------------------------------
    // RIGHT FACE = No.3
    // -------------------------------------------------
    x0 = 2.0f / 3.0f;
    x1 = 3.0f / 3.0f;
    y0 = 1.0f / 2.0f;
    y1 = 2.0f / 2.0f;

    glNormal3fv(faces[1].faceNormal.data);

    glTexCoord2f(x0, y1);
    glVertex3fv(vertices[1].coordinate.data);       // top left

    glTexCoord2f(x0, y0);
    glVertex3fv(vertices[2].coordinate.data);       // bottom left

    glTexCoord2f(x1, y0);
    glVertex3fv(vertices[6].coordinate.data);       // bottom right

    glTexCoord2f(x1, y1);
    glVertex3fv(vertices[5].coordinate.data);       // top right



    // -------------------------------------------------
    // BACK FACE = No.4
    // -------------------------------------------------
    x0 = 0.0f / 3.0f;
    x1 = 1.0f / 3.0f;
    y0 = 0.0f / 2.0f;
    y1 = 1.0f / 2.0f;

    glNormal3fv(faces[2].faceNormal.data);

    glTexCoord2f(x0, y1);
    glVertex3fv(vertices[5].coordinate.data);       // top left

    glTexCoord2f(x0, y0);
    glVertex3fv(vertices[6].coordinate.data);       // bottom left

    glTexCoord2f(x1, y0);
    glVertex3fv(vertices[7].coordinate.data);       // bottom right

    glTexCoord2f(x1, y1);
    glVertex3fv(vertices[4].coordinate.data);       // top right



    // -------------------------------------------------
    // LEFT FACE = No.2
    // -------------------------------------------------
    x0 = 1.0f / 3.0f;
    x1 = 2.0f / 3.0f;
    y0 = 1.0f / 2.0f;
    y1 = 2.0f / 2.0f;

    glNormal3fv(faces[3].faceNormal.data);

    glTexCoord2f(x0, y1);
    glVertex3fv(vertices[4].coordinate.data);       // top left

    glTexCoord2f(x0, y0);
    glVertex3fv(vertices[7].coordinate.data);       // bottom left

    glTexCoord2f(x1, y0);
    glVertex3fv(vertices[3].coordinate.data);       // bottom right

    glTexCoord2f(x1, y1);
    glVertex3fv(vertices[0].coordinate.data);       // top right



    // -------------------------------------------------
    // TOP FACE = No.5
    // -------------------------------------------------
    x0 = 1.0f / 3.0f;
    x1 = 2.0f / 3.0f;
    y0 = 0.0f / 2.0f;
    y1 = 1.0f / 2.0f;

    glNormal3fv(faces[4].faceNormal.data);

    glTexCoord2f(x0, y0);
    glVertex3fv(vertices[0].coordinate.data);       // front left

    glTexCoord2f(x1, y0);
    glVertex3fv(vertices[1].coordinate.data);       // front right

    glTexCoord2f(x1, y1);
    glVertex3fv(vertices[5].coordinate.data);       // back right

    glTexCoord2f(x0, y1);
    glVertex3fv(vertices[4].coordinate.data);       // back left



    // -------------------------------------------------
    // BOTTOM FACE = No.6
    // -------------------------------------------------
    x0 = 2.0f / 3.0f;
    x1 = 3.0f / 3.0f;
    y0 = 0.0f / 2.0f;
    y1 = 1.0f / 2.0f;

    glNormal3fv(faces[5].faceNormal.data);

    glTexCoord2f(x0, y1);
    glVertex3fv(vertices[3].coordinate.data);       // front left

    glTexCoord2f(x0, y0);
    glVertex3fv(vertices[7].coordinate.data);       // back left

    glTexCoord2f(x1, y0);
    glVertex3fv(vertices[6].coordinate.data);       // back right

    glTexCoord2f(x1, y1);
    glVertex3fv(vertices[2].coordinate.data);       // front right


    glEnd();


    // disable texturing
    if (theTexture && !gWireFrameOnly)
        glDisable(GL_TEXTURE_2D);
}
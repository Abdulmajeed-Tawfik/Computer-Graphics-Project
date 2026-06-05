#ifndef CHAIR_H
#define CHAIR_H

#include "prefix.h"
#include "object3d.h"
#include <vector>

class Chair : public object3d
{
private:
    std::vector<object3d*> parts;

    // Chair components
    object3d* seat;
    object3d* backrest;
    object3d* legFrontLeft;
    object3d* legFrontRight;
    object3d* legBackLeft;
    object3d* legBackRight;

    void rememberPart(object3d* part);
protected:
    void privateDraw(bool drawMode);
public:
    Chair();
    ~Chair();

    void show();
    void hide();
};

#endif
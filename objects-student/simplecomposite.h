#ifndef _simplecomposite_H
#define _simplecomposite_H



// -----------------------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------------------
#include "face.h"
#include "object3d.h"
#include "pyramid.h"
#include "torus.h"
#include "sphere.h"
#include "extrusion.h"
#include "sweep.h"

// -----------------------------------------------------------------------------------------
// class declaration
// -----------------------------------------------------------------------------------------

class simplecomposite : public object3d
{
private:
	pyramid* py;
	torus* to1, * to2,* to3,* to4;
	sphere* sp1, * sp2;
	extrusion* ex1;
	sweep* sw1;

	public:
		simplecomposite();
		void hide(void);
		void show(void);
};


#endif // simplecomposite_H


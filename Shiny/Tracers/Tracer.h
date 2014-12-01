///////////////////////////////////////////////////////////////////////////////
//	File:    Tracer.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////

#ifndef __TRACER__
#define __TRACER__

#include "Constants.h"
#include "Ray.h"
#include "RGBColor.h"

class World;

class Tracer {
protected:
	
	World* pWorld;
public:
	Tracer(void);									
	Tracer(World* world);							
	virtual	~Tracer(void);									
	virtual RGBColor TraceRay(const Ray& ray) const;
	virtual RGBColor TraceRay(const Ray ray, const int depth) const;
};

#endif
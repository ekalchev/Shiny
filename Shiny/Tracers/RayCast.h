///////////////////////////////////////////////////////////////////////////////
//	File:    RayCast.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////

#ifndef __RAYCAST__
#define __RAYCAST__

#include "Tracer.h"

class RayCast: public Tracer 
{
public:
	
	RayCast(void);
	RayCast(World* world);		
	virtual	~RayCast(void);		
	virtual RGBColor TraceRay(const Ray& ray) const;
	virtual RGBColor TraceRay(const Ray ray, const int depth) const;
};

#endif
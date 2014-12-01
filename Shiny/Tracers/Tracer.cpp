///////////////////////////////////////////////////////////////////////////////
//	File:    Tracer.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Tracer.h"

// -------------------------------------------------------------------- default constructor

Tracer::Tracer(void) : pWorld(NULL)
{
}


// -------------------------------------------------------------------- constructor

Tracer::Tracer(World* world) : pWorld(world)
{
}



// -------------------------------------------------------------------- destructor

Tracer::~Tracer(void) 
{
	if (pWorld)
		pWorld = NULL;
}


// -------------------------------------------------------------------- trace_ray

RGBColor Tracer::TraceRay(const Ray& ray) const 
{
	return (black);
}


// -------------------------------------------------------------------- trace_ray

RGBColor Tracer::TraceRay(const Ray ray, const int depth) const 
{
	return (black);
}
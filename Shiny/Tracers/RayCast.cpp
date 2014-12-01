///////////////////////////////////////////////////////////////////////////////
//	File:    RayCast.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RayCast.h"
#include "World.h"
#include "ShadeRec.h"
#include "Material.h"

// -------------------------------------------------------------------- default constructor

RayCast::RayCast(void) : Tracer()
{
}


// -------------------------------------------------------------------- constructor
		
RayCast::RayCast(World* world) : Tracer(world)
{
}


// ------------------------- ------------------------------------------- destructor

RayCast::~RayCast(void) 
{
}


// -------------------------------------------------------------------- trace_ray

RGBColor RayCast::TraceRay(const Ray& ray) const 
{
	assert(pWorld != NULL);
	ShadeRec sr(pWorld->HitObjects(ray));
	sr.nDepth += 1;
		
	if (sr.bHitAnObject) 
	{
		sr.ray = ray;			// used for specular shading
		return (sr.pMaterial->Shade(sr));
	}   
	else
		return (RenderConfig::backgroundColor);
}


// -------------------------------------------------------------------- trace_ray
// this ignores the depth argument

RGBColor RayCast::TraceRay(const Ray ray, const int depth) const 
{
	assert(pWorld != NULL);
	ShadeRec sr(pWorld->HitObjects(ray));
	sr.nDepth = depth;
		
	if (sr.bHitAnObject) 
	{
		sr.ray = ray;			// used for specular shading
		return (sr.pMaterial->Shade(sr));

	}   
	else
		return (RenderConfig::backgroundColor);
}
///////////////////////////////////////////////////////////////////////////////
//	File:    Plane.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "Plane.h"

Plane::Plane() : n(0,1,0),a(0,0,0)
{
	epsilon = 0.001;
}

bool Plane::Collide(const Ray& ray,float& tmin,ShadeRec& sr) const
{
	float t = (a - ray.o) * n / (ray.d * n); 
														
	if (t > epsilon) 
	{
		tmin = t;
		sr.normal = n;
		sr.hitPoint = ray.o + t * ray.d;
		
		return true;	
	}

	return false;
}

bool Plane::ShadowHit(const Ray& ray,float& tmin) const
{
	float t = (a - ray.o) * n / (ray.d * n); 
														
	if (t > epsilon) 
	{
		tmin = t;
		return true;	
	}

	return false;
}

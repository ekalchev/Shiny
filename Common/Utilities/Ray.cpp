///////////////////////////////////////////////////////////////////////////////
//	File:    Ray.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "Ray.h"
#include <float.h>


Ray::Ray() : o(0.0, 0.0, 0.0),d(0.0, 0.0, 1.0),tmin(FLT_MAX)
{
}

Ray::Ray(const Point3D& origin, const Vector3D& dir) : o(origin),d(dir),tmin(FLT_MAX)
{
}

Ray::Ray(const Ray& ray) : o(ray.o), d(ray.d) 
{
}


Ray& Ray::operator= (const Ray& rhs) 
{
	
	if (this == &rhs)
		return (*this);
		
	o = rhs.o; 
	d = rhs.d; 

	return (*this);	
}
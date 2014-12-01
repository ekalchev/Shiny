///////////////////////////////////////////////////////////////////////////////
//	File:    Ray.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __RAY__
#define __RAY__

#include "ShinyMath.h"

class Ray
{
public:
	Point3D	o;
	Vector3D d;
	float tmin;
public:
	Ray();
	Ray(const Point3D& origin, const Vector3D& dir); 
	Ray(const Ray& ray);
	Ray& operator= (const Ray& rhs);
};

#endif
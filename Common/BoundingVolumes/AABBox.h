///////////////////////////////////////////////////////////////////////////////
//	File:    AABBox.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////



#ifndef __AABBOX__
#define __AABBOX__

#include <Point3D.h>
#include <Ray.h>

class AABBox
{
public:
	Point3D min;
	Point3D max;


public:
	AABBox(const Point3D& pmin,const Point3D& pmax);
	static AABBox* Union(const AABBox* a,const AABBox* b);
	int IntersectRay(const Ray& ray,float& tmin, float& tmax);
	static void LimitBounds(AABBox* a);
};

#endif
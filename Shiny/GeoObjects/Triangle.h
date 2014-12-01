///////////////////////////////////////////////////////////////////////////////
//	File:    Triangle.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////

#ifndef __TRIANGLE__
#define __TRIANGLE__

#include "GeoObject.h"

class Triangle : public GeoObject
{
public:
	Point3D v0,v1,v2;
	Normal normal;

public:
	Triangle();
	Triangle(Point3D& a,Point3D& b,Point3D& c);
	virtual bool Collide(const Ray& ray,float& tmin,ShadeRec& sr) const;
	virtual bool ShadowHit(const Ray& ray,float& tmin) const;
	virtual AABBox* GetAABBox();
	void InvertNormal();
};

inline void Triangle::InvertNormal()
{
	normal = -normal;
}

#endif
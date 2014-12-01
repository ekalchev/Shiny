///////////////////////////////////////////////////////////////////////////////
//	File:    Plane.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __PLANE__
#define __PLANE__

#include "GeoObject.h"

class Plane : public GeoObject
{
private:
	Normal n;
	Point3D a;
public:
	Plane();
	virtual bool Collide(const Ray& ray,float& tmin,ShadeRec& sr) const;
	virtual bool ShadowHit(const Ray& ray,float& tmin) const;
	void SetPoint(Point3D& point);
};

inline void Plane::SetPoint(Point3D& point)
{
	a = point;
}

#endif
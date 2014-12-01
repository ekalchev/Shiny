///////////////////////////////////////////////////////////////////////////////
//	File:    Sphere.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __SPHERE__
#define __SPHERE__

#include "GeoObject.h"

class Sphere : public GeoObject
{
public:
	Point3D center;
	float radius;

public:
	Sphere();
	void SetCenter(Point3D _center);
	void SetRadius(float _radius);
	virtual bool Collide(const Ray& ray,float& tmin,ShadeRec& sr) const;
	virtual bool ShadowHit(const Ray& ray,float& tmin) const;
	virtual AABBox* GetAABBox();
};

#endif
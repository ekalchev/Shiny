///////////////////////////////////////////////////////////////////////////////
//	File:    GeoObjectAdapter.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __GEOOBJECTADAPTER__
#define __GEOOBJECTADAPTER__

#include <Ray.h>
#include <ShadeRec.h>
#include <GeoObject.h>

class GeoObjectAdapter
{
public:
	bool HitAnObject(const ShadeRec *sr) const;
	bool Intersect(const GeoObject* obj,const Ray& ray,ShadeRec *in,ShadeRec *out) const;
	float GetDistance(const ShadeRec *sr) const;
	AABBox* GetAABBox(GeoObject* obj) const;
};

inline bool GeoObjectAdapter::HitAnObject(const ShadeRec *sr) const
{
	return sr->bHitAnObject;
}

inline AABBox* GeoObjectAdapter::GetAABBox(GeoObject* obj) const
{
	return obj->GetAABBox();
}

inline float GeoObjectAdapter::GetDistance(const ShadeRec *sr) const
{
	return sr->fDistance;
}
#endif
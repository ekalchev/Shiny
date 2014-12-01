///////////////////////////////////////////////////////////////////////////////
//	File:    GeoObjectAdapter.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GeoObjectAdapter.h"


bool GeoObjectAdapter::Intersect(const GeoObject* obj,const Ray& ray,ShadeRec *in,ShadeRec *out) const
{
	bool ret = false;
	float t;

	ShadeRec tmpRec;

	if(obj->Collide(ray,t,tmpRec) && t < in->fDistance)
	{
		tmpRec.fDistance = t;
		tmpRec.bHitAnObject = true;
		tmpRec.hitPoint = ray.o + t * ray.d;
		tmpRec.pMaterial = obj->GetMaterial();
		tmpRec.ray = ray;
	}

	if(tmpRec.bHitAnObject)
	{
		*out = tmpRec;
		ret = true;
	}

	return ret;
}
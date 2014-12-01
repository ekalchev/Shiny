///////////////////////////////////////////////////////////////////////////////
//	File:    GeoObject.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
//  Description: This is base class of all geometric object
///////////////////////////////////////////////////////////////////////////////


#ifndef __GEOOBJECT__
#define __GEOOBJECT__


#include "Ray.h"
#include "ShadeRec.h"
#include "ShinyMath.h"
#include <AABBox.h>

class Material;


class GeoObject
{
protected:
	Material* pMaterial;
	float epsilon;
	AABBox* aabbox;
public:
	GeoObject::GeoObject();
	virtual ~GeoObject();
	//ray - ray we are colliding object with 
	//tmin - min value of t param
	//si - shading data needed to compute pixel color
	virtual bool Collide(const Ray& ray,float& tmin,ShadeRec& si) const = 0;
	virtual bool ShadowHit(const Ray& ray,float& tmin) const = 0;
	virtual AABBox* GetAABBox();
	void SetMaterial(Material* material);
	
	Material* GetMaterial() const;
};

inline void GeoObject::SetMaterial(Material* material)
{
	pMaterial = material;
}

inline Material* GeoObject::GetMaterial() const
{
	return pMaterial;
}
#endif
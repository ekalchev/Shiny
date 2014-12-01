///////////////////////////////////////////////////////////////////////////////
//	File:    PointLight.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "PointLight.h"
#include "GeoObject.h"
#include "World.h"
#include <vector>

PointLight::PointLight() : ls(1.0),color(1.0f,1.0f,1.0f),position(0.0f,0.0f,0.0f)
{
}

Vector3D PointLight::GetDirection(ShadeRec& sr)
{
	Vector3D dir;
	dir = position - sr.hitPoint;
	dir.normalize();
	return dir;
}

RGBColor PointLight::L(ShadeRec& sr)
{
	Vector3D dist;
	dist = sr.hitPoint - position;
	float len = dist.length();
	return (ls * color) / (float)len*len;
}

bool PointLight::InShadow(const Ray& ray,const ShadeRec& sr) const
{
	/*float t;
	vector<GeoObject*> objects = sr.pWorld->GetWorldObjects();
	vector<GeoObject*>::iterator iter;

	for(iter = objects.begin(); iter != objects.end(); ++iter)
	{
		if((*iter)->ShadowHit(ray,t))
		{
			Vector3D dist;
			dist = sr.hitPoint - position;
			float len = dist.length();
			if(t <= len)
				return true;
		}
	}*/

	return false;
}
///////////////////////////////////////////////////////////////////////////////
//	File:    DirectionalLight.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "DirectionalLight.h"
#include "GeoObject.h"
#include "World.h"
#include <vector>


DirectionalLight::DirectionalLight() : ls(1.0),color(1.0f,1.0f,1.0f),direction(0.0f,0.0f,0.0f)
{
	direction.normalize();
}

Vector3D DirectionalLight::GetDirection(ShadeRec& sr)
{
	return direction;
}
RGBColor DirectionalLight::L(ShadeRec& sr)
{
	return ls * color;
}

bool DirectionalLight::InShadow(const Ray& ray,const ShadeRec& sr) const
{
	float t;
	vector<GeoObject*> objects = sr.pWorld->GetWorldObjects();
	vector<GeoObject*>::iterator iter;

	for(iter = objects.begin(); iter != objects.end(); ++iter)
	{
		if((*iter)->ShadowHit(ray,t))
		{
			return true;
		}
	}

	return false;
}
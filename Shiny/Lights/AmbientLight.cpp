///////////////////////////////////////////////////////////////////////////////
//	File:    AmbientLight.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "AmbientLight.h"

AmbientLight::AmbientLight() : ls(1.0),color(1.0f,1.0f,1.0f)
{
}

RGBColor AmbientLight::L(ShadeRec& sr)
{
	return (ls*color);
}

Vector3D AmbientLight::GetDirection(ShadeRec& sr)
{
	return Vector3D(0.0f,0.0f,0.0f);
}

bool AmbientLight::InShadow(const Ray& ray,const ShadeRec& sr) const
{
	return false;
}
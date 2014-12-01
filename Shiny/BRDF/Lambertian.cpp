///////////////////////////////////////////////////////////////////////////////
//	File:    Lambertian.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Lambertian.h"


Lambertian::Lambertian() : kd(0.0),	cd(0.0)
{
}

Lambertian::Lambertian(float _kd,float _cd) : kd(_kd),	cd(_cd)
{
}

RGBColor Lambertian::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const
{
	return (kd * cd * (float)invPI);
}

RGBColor Lambertian::rho(const ShadeRec& sr, const Vector3D& wo) const
{
	return (kd * cd);
}

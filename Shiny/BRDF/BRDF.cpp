///////////////////////////////////////////////////////////////////////////////
//	File:    BRDF.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "BRDF.h"


BRDF::BRDF()
{
}

BRDF::~BRDF()
{
}

RGBColor BRDF::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const
{
	return (black);
}


RGBColor BRDF::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const 
{
	return (black);
}


RGBColor BRDF::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const 
{
	return (black);
}

	
RGBColor BRDF::rho(const ShadeRec& sr, const Vector3D& wo) const 
{
	return (black);
}
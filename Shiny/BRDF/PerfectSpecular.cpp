///////////////////////////////////////////////////////////////////////////////
//	File:    PerfectSpecular.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "PerfectSpecular.h"


PerfectSpecular::PerfectSpecular() : cr(1.0f,1.0f,1.0f),kr(1.0f)
{
}

RGBColor PerfectSpecular::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const
{
	float fNdotWO = sr.normal * wo;
	wi = -wo + 2.0f * sr.normal * fNdotWO;

	//TODO: check if you can replace (sr.normal * wi) with fNdotWO
	return (kr * cr / (float)(sr.normal * wi));
}
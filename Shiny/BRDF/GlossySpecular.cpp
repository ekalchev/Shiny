///////////////////////////////////////////////////////////////////////////////
//	File:    GlossySpecular.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GlossySpecular.h"
#include <math.h>

GlossySpecular::GlossySpecular() : ks(1.0f),exp(10.0f)
{
}


RGBColor GlossySpecular::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const
{
	RGBColor L;
	float fNdotWI = sr.normal * wi;
	Vector3D r(-wi + 2.0f * sr.normal * fNdotWI);
	float fRdotWO = r * wo;

	if(fRdotWO > 0.0)
	{
		L = ks * pow(fRdotWO,exp);
	}

	Utils::MaxToOne(&L);

	return L;
}
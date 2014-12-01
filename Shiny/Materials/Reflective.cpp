///////////////////////////////////////////////////////////////////////////////
//	File:    Reflective.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Reflective.h"
#include "PerfectSpecular.h"
#include "World.h"
#include "Tracer.h"

Reflective::Reflective()
{
	perfectSpecularBRDF = new PerfectSpecular();
}

Reflective::~Reflective()
{
	delete perfectSpecularBRDF;
}

RGBColor Reflective::Shade(ShadeRec& sr)
{
	RGBColor L(Phong::Shade(sr));
	if(sr.nDepth < MAX_REFLECTIVE_DEPTH)
	{
		Vector3D vWO = -sr.ray.d;
		Vector3D vWI;
		RGBColor brdfColor = perfectSpecularBRDF->sample_f(sr,vWO,vWI);
		Ray reflectedRay(sr.hitPoint,vWI);
		L += brdfColor*sr.pWorld->pTracer->TraceRay(reflectedRay, sr.nDepth + 1)*(float)(sr.normal*vWI);
	}
	Utils::MaxToOne(&L);
	return L;
}
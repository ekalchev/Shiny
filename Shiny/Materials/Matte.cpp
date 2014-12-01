///////////////////////////////////////////////////////////////////////////////
//	File:    Matte.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "Matte.h"
#include "Lambertian.h"
#include "World.h"
#include "AmbientLight.h"

Matte::Matte() : ambientBRDF(new Lambertian),diffuseBRDF(new Lambertian)
{
}

Matte::~Matte()
{
	delete ambientBRDF;
	delete diffuseBRDF;
}

RGBColor Matte::Shade(ShadeRec& sr)
{
	Vector3D 	vWO 		= -sr.ray.d;
	RGBColor 	L(0,0,0);
	if(sr.pWorld->pAmbientLight)
	{
		L = ambientBRDF->rho(sr, vWO) * sr.pWorld->pAmbientLight->L(sr);
	}
	int nNumLights	= sr.pWorld->lights.size();
	
	for (int i = 0; i < nNumLights; i++) 
	{
		Light* pCurrentLight = sr.pWorld->lights[i];
		Vector3D vWI = pCurrentLight->GetDirection(sr);
		float fNdotWI = sr.normal * vWI;
	
		if (fNdotWI > 0.0) 
		{
			bool bInShadow = false;
			if(pCurrentLight->CastShadows())
			{
				Ray shadowRay(sr.hitPoint,vWI);
				bInShadow = pCurrentLight->InShadow(shadowRay,sr);
			}
			if(!bInShadow)
			{
				L += diffuseBRDF->f(sr, vWO, vWI) * pCurrentLight->L(sr) * fNdotWI;
			}
			Utils::MaxToOne(&L);
		}
	}
	
	return L;
}
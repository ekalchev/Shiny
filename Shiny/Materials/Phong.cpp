///////////////////////////////////////////////////////////////////////////////
//	File:    Phong.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "Phong.h"
#include "Lambertian.h"
#include "World.h"
#include "AmbientLight.h"
#include "GlossySpecular.h"

Phong::Phong() : ambientBRDF(new Lambertian),diffuseBRDF(new Lambertian),specularBRDF(new GlossySpecular)
{
}

Phong::~Phong()
{
	delete ambientBRDF;
	delete diffuseBRDF;
	delete specularBRDF;
}

RGBColor Phong::Shade(ShadeRec& sr)
{
	Vector3D 	vWO 		= -sr.ray.d;
	RGBColor 	L(1,1,1);


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
				L += (diffuseBRDF->f(sr, vWO, vWI) +
					 specularBRDF->f(sr, vWO, vWI)) *
					 pCurrentLight->L(sr) * fNdotWI;
			}
			Utils::MaxToOne(&L);
		}
	}
	
	return L;
}
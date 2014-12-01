///////////////////////////////////////////////////////////////////////////////
//	File:    BRDF.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __BRDF__
#define __BRDF__

#include "RGBColor.h"
#include "Vector3d.h"
#include "ShadeRec.h"

class BRDF
{
public:
	BRDF();
	virtual ~BRDF();
	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;
		
	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const;
		
	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;
		
	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;
};

#endif
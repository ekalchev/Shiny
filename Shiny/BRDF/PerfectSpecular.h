///////////////////////////////////////////////////////////////////////////////
//	File:    PerfectSpecular.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __PERFECTSPECULAR__
#define __PERFECTSPECULAR__

#include "BRDF.h"

class PerfectSpecular : public BRDF
{
private:
	RGBColor cr;
	float kr;
public:
	PerfectSpecular();
	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const;
};

#endif
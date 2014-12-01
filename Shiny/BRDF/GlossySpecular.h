///////////////////////////////////////////////////////////////////////////////
//	File:    GlossySpecular.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __GLOSSYSPECULAR__
#define __GLOSSYSPECULAR__

#include "BRDF.h"

class GlossySpecular : public BRDF
{
private:
	RGBColor ks;
	float exp;
public:
	GlossySpecular();
	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;
	void SetKs(RGBColor  pks);
	void SetExp(float pexp);
};

inline void GlossySpecular::SetKs(RGBColor pks)
{
	ks = pks;
}

inline void GlossySpecular::SetExp(float pexp)
{
	exp = pexp;
}

#endif
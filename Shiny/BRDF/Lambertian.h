///////////////////////////////////////////////////////////////////////////////
//	File:    Lambertian.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __LAMBERTIAN__
#define __LAMBERTIAN__

#include "BRDF.h"

class Lambertian : public BRDF
{
private:
	float		kd;
	RGBColor 	cd;
public:
	Lambertian();
	Lambertian(float _kd,float _cd);
	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;	
	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;
		
	void SetKd(float kd);
	void SetCd(RGBColor c);
	void SetCd(float r,float g,float b);
	void SetCd(float c);
};


inline void Lambertian::SetKd(float k) 
{
	kd = k;
}


inline void Lambertian::SetCd(RGBColor c) 
{
	cd = c;
}


inline void	Lambertian::SetCd(float r,float g,float b) 
{
	cd.r = r; cd.g = g; cd.b = b;
}

inline void	Lambertian::SetCd(float c) 
{
	cd.r = c; cd.g = c; cd.b = c;
}

#endif


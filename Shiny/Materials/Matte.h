///////////////////////////////////////////////////////////////////////////////
//	File:    Matte.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __MATTE__
#define __MATTE__

#include "Material.h"
#include "Lambertian.h"

class Matte : public Material
{
private:
	Lambertian* ambientBRDF;
	Lambertian* diffuseBRDF;

public:
	Matte();
	~Matte();
	virtual RGBColor Shade(ShadeRec& sr);
	void SetKd(const float k); 
	void SetCd(const RGBColor& c);
	void SetCd(float r,float g,float b);
	void SetCd(float c) ;
};


inline void Matte::SetKd(const float k) 
{
	ambientBRDF->SetKd(k);
	diffuseBRDF->SetKd(k);
}


inline void Matte::SetCd(const RGBColor& c) 
{
	ambientBRDF->SetCd(c);
	diffuseBRDF->SetCd(c);
}

inline void	Matte::SetCd(float r,float g,float b) 
{
	ambientBRDF->SetCd(r,g,b);
	diffuseBRDF->SetCd(r,g,b);
}

inline void	Matte::SetCd(float c) 
{
	ambientBRDF->SetCd(c);
	diffuseBRDF->SetCd(c);
}

#endif

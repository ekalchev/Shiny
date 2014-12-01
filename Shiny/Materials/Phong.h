///////////////////////////////////////////////////////////////////////////////
//	File:    Phong.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __PHONG__
#define __PHONG__

#include "Material.h"
#include "Lambertian.h"
#include "GlossySpecular.h"

class Phong : public Material
{
private:
	Lambertian* ambientBRDF;
	Lambertian* diffuseBRDF;
	GlossySpecular* specularBRDF;

public:
	Phong();
	~Phong();
	virtual RGBColor Shade(ShadeRec& sr);
	void SetKd(const float k); 
	void SetCd(const RGBColor& c);
	void SetCd(float r,float g,float b);
	void SetCd(float c) ;
	void SetExp(float pexp);
	void SetKs(RGBColor& pks);
};


inline void Phong::SetKd(const float k) 
{
	ambientBRDF->SetKd(k);
	diffuseBRDF->SetKd(k);
}


inline void Phong::SetCd(const RGBColor& c) 
{
	ambientBRDF->SetCd(c);
	diffuseBRDF->SetCd(c);
}

inline void	Phong::SetCd(float r,float g,float b) 
{
	ambientBRDF->SetCd(r,g,b);
	diffuseBRDF->SetCd(r,g,b);
}

inline void	Phong::SetCd(float c) 
{
	ambientBRDF->SetCd(c);
	diffuseBRDF->SetCd(c);
}

inline void	Phong::SetExp(float pexp) 
{
	specularBRDF->SetExp(pexp);
}

inline void	Phong::SetKs(RGBColor& pks) 
{
	specularBRDF->SetKs(pks);
}

#endif
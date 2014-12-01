///////////////////////////////////////////////////////////////////////////////
//	File:    Reflective.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __REFLECTIVE__
#define __REFLECTIVE__

#include "Material.h"
#include "Phong.h"

class PerfectSpecular;

class Reflective : public Phong
{
private:
	PerfectSpecular* perfectSpecularBRDF;
public:
	Reflective();
	~Reflective();
	virtual RGBColor Shade(ShadeRec& sr);
};
#endif
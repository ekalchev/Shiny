///////////////////////////////////////////////////////////////////////////////
//	File:    Material.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __MATERIAL__
#define __MATERIAL__

#include "RGBColor.h"
#include "ShadeRec.h"

class Material
{
public:
	virtual RGBColor Shade(ShadeRec& sr);	
};

#endif
///////////////////////////////////////////////////////////////////////////////
//	File:    Light.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////



#ifndef __LIGHT__
#define __LIGHT__

#include "RGBColor.h"
#include "ShadeRec.h"
#include "Ray.h"

class Light
{
private:
	bool castShadows;
public:
	Light();
	virtual ~Light();
	virtual Vector3D GetDirection(ShadeRec& sr) = 0;
	virtual RGBColor L(ShadeRec& sr) = 0;
	virtual bool InShadow(const Ray& ray,const ShadeRec& sr) const = 0;
	bool CastShadows() const;
};

inline bool Light::CastShadows() const
{
	return castShadows;
}

#endif
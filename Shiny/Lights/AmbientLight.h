///////////////////////////////////////////////////////////////////////////////
//	File:    AmbientLight.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __AMBIENTLIGHT__
#define __AMBIENTLIGHT__

#include "Light.h"

class AmbientLight : public Light
{
private:
	float ls;
	RGBColor color;
public:
	AmbientLight();
	virtual RGBColor L(ShadeRec& sr);
	virtual Vector3D GetDirection(ShadeRec& sr);
	virtual bool InShadow(const Ray& ray,const ShadeRec& sr) const;
	void ScaleRadiance(float scale);
	void SetColor(RGBColor col);
};

inline void AmbientLight::ScaleRadiance(float scale)
{
	ls = scale;
}

inline void AmbientLight::SetColor(RGBColor col)
{
	color = col;
}

#endif
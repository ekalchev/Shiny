///////////////////////////////////////////////////////////////////////////////
//	File:    DirectionalLight.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __DIRECTIONALLIGHT__
#define __DIRECTIONALLIGHT__

#include "Light.h"
#include "Vector3D.h"
#include "RGBColor.h"
#include "ShadeRec.h"

class DirectionalLight : public Light
{
private:
	float ls;
	RGBColor color;
	Vector3D direction;

public:
	DirectionalLight();
	virtual Vector3D GetDirection(ShadeRec& sr);
	virtual RGBColor L(ShadeRec& sr);
	virtual bool InShadow(const Ray& ray,const ShadeRec& sr) const;
	void SetDirection(Vector3D dir);
	void SetColor(RGBColor col);
	void ScaleRadiance(float scale);
};

inline void DirectionalLight::SetDirection(Vector3D dir)
{
	direction = dir;
	direction.normalize();
}

inline void DirectionalLight::SetColor(RGBColor col)
{
	color = col;
}

inline void DirectionalLight::ScaleRadiance(float scale)
{
	ls = scale;
}

#endif
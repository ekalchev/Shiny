///////////////////////////////////////////////////////////////////////////////
//	File:    PointLight.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __POINTLIGHT__
#define __POINTLIGHT__

#include "Light.h"
#include "Vector3D.h"
#include "RGBColor.h"
#include "ShadeRec.h"

class PointLight : public Light
{
private:
	float ls;
	RGBColor color;
	Point3D position;

public:
	PointLight();
	virtual Vector3D GetDirection(ShadeRec& sr);
	virtual RGBColor L(ShadeRec& sr);
	virtual bool InShadow(const Ray& ray,const ShadeRec& sr) const;
	void SetColor(RGBColor col);
	void ScaleRadiance(float scale);
	void SetPosition(Point3D pos);
	Point3D GetPosition();
};

inline void PointLight::SetPosition(Point3D pos)
{
	position = pos;
}

inline void PointLight::SetColor(RGBColor col)
{
	color = col;
}

inline void PointLight::ScaleRadiance(float scale)
{
	ls = scale;
}

inline Point3D PointLight::GetPosition()
{
	return position;
}

#endif
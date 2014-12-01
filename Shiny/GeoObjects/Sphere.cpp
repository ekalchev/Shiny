///////////////////////////////////////////////////////////////////////////////
//	File:    Sphere.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "Sphere.h"
#include "math.h"

Sphere::Sphere()
{

}

void Sphere::SetCenter(Point3D _center)
{
	center = _center;
}
void Sphere::SetRadius(float _radius)
{
	radius = _radius;
}

//solving quadratic equation
// (ray.d*ray.d)*t*t + (2*(ray.o - center)*ray.d)*t + (ray.o - center)*(ray.o - center) - radius*radius = 0;
// a = ray.d*ray.d
// b = 2.0*(ray.o - center)*ray.d
// c = (ray.o - center)*(ray.o - center) - radius*radius
bool Sphere::Collide(const Ray& ray,float& tmin,ShadeRec& sr) const
{
	float t;
	Vector3D oc = ray.o - center;
	float a = ray.d * ray.d;
	float b = 2.0 * oc * ray.d;
	float c = (oc * oc) - radius*radius;
	float disc = b * b - 4.0 * a * c;

	if(disc >= 0.0)
	{
		float denom = 2.0 * a;
		float e = sqrt(disc);
		t = (-b - e) / denom; //smaller root

		if(t > epsilon)
		{
			tmin = t;
			sr.normal = (oc + t * ray.d) / radius;
			sr.hitPoint = ray.o + t * ray.d;
			return true;
		}

		t = (-b + e) / denom; //larger root

		if(t > epsilon)
		{
			tmin = t;
			sr.normal = (oc + t * ray.d) / radius;
			sr.hitPoint = ray.o + t * ray.d;
			return true;
		}
	}

	return false;
}
//this function is light weight version of function Collide because its used for
//shadow calculation and we can skip calculation of normals and hit points
bool Sphere::ShadowHit(const Ray& ray,float& tmin) const
{
	float t;
	Vector3D oc = ray.o - center;
	float a = ray.d * ray.d;
	float b = 2.0 * oc * ray.d;
	float c = (oc * oc) - radius*radius;
	float disc = b * b - 4.0 * a * c;

	if(disc >= 0.0)
	{
		float denom = 2.0 * a;
		float e = sqrt(disc);
		t = (-b - e) / denom; //smaller root

		if(t > epsilon)
		{
			tmin = t;
			return true;
		}

		t = (-b + e) / denom; //larger root

		if(t > epsilon)
		{
			tmin = t;
			return true;
		}
	}

	return false;
}

AABBox* Sphere::GetAABBox()
{
	Point3D min;
	Point3D max;

	min.x = center.x - radius;
	min.y = center.y - radius;
	min.z = center.z - radius;

	max.x = center.x + radius;
	max.y = center.y + radius;
	max.z = center.z + radius;

	return new AABBox(min,max);

}
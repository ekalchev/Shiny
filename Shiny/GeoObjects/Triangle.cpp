///////////////////////////////////////////////////////////////////////////////
//	File:    Triangle.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Triangle.h"
#include "math.h"
#include <AABBox.h>

using namespace std;

Triangle::Triangle() : v0(0,0,0),v1(0,0,1),v2(1,0,0),normal(0,1,0)
{
}

Triangle::Triangle(Point3D& a,Point3D& b,Point3D& c) : v0(a),v1(b),v2(c)
{
	normal = (v1 - v0) ^ (v2 - v0);
	normal.normalize();
}

bool Triangle::Collide(const Ray& ray,float& tmin,ShadeRec& sr) const
{
	double a = v0.x - v1.x;
	double b = v0.x - v2.x;
	double c = ray.d.x;
	double d = v0.x - ray.o.x;

	double e = v0.y - v1.y;
	double f = v0.y - v2.y;
	double g = ray.d.y;
	double h = v0.y - ray.o.y;

	double i = v0.z - v1.z;
	double j = v0.z - v2.z;
	double k = ray.d.z;
	double l = v0.z - ray.o.z;

	double m = f*k - g*j;
	double n = h*k - g*l;
	double p = f*l - h*j;
	double q = g*i - e*k;
	double s = e*j - f*i;

	double inv_denominator = 1.0 / (a * m + b * q + c * s);

	double chisl1 = d * m - b * n - c * p;
	double beta = chisl1 * inv_denominator;

	if(beta < 0.0)
	{
		return false;
	}

	double r = e * l - h * i;
	double chisl2 = a * n + d * q + c * r;
	double gamma = chisl2 * inv_denominator;

	if(gamma < 0.0)
	{
		return false;
	}

	if(beta + gamma > 1.0)
	{
		return false;
	}

	double e3 = a * p - b * r + d * s;
	double t = e3 * inv_denominator;

	if(t < epsilon)
	{
		return false;
	}

	tmin = t;

	sr.normal = normal;
	sr.hitPoint = ray.o + t * ray.d;

	return true;
}

bool Triangle::ShadowHit(const Ray& ray,float& tmin) const
{
	float a = v0.x - v1.x;
	float b = v0.x - v2.x;
	float c = ray.d.x;
	float d = v0.x - ray.o.x;

	float e = v0.y - v1.y;
	float f = v0.y - v2.y;
	float g = ray.d.y;
	float h = v0.y - ray.o.y;

	float i = v0.z - v1.z;
	float j = v0.z - v2.z;
	float k = ray.d.z;
	float l = v0.z - ray.o.z;

	float m = f*k - g*j;
	float n = h*k - g*l;
	float p = f*l - h*j;
	float q = g*i - e*k;
	float s = e*j - f*i;

	float inv_denominator = 1.0 / (a * m + b * q + c * s);

	float chisl1 = d * m - b * n - c * p;
	float beta = chisl1 * inv_denominator;

	if(beta < 0.0)
	{
		return false;
	}

	float r = e * l - h * i;
	float chisl2 = a * n + d * q + c * r;
	float gamma = chisl2 * inv_denominator;

	if(gamma < 0.0)
	{
		return false;
	}

	if(beta + gamma > 1.0)
	{
		return false;
	}

	float e3 = a * p - b * r + d * s;
	float t = e3 * inv_denominator;

	if(t < epsilon)
	{
		return false;
	}

	tmin = t;

	return true;
}

AABBox* Triangle::GetAABBox()
{
	if(aabbox == NULL)
	{
		Point3D min,max;

		max.x = std::max(std::max(v0.x,v1.x),v2.x);
		max.y = std::max(std::max(v0.y,v1.y),v2.y);
		max.z = std::max(std::max(v0.z,v1.z),v2.z);

		min.x = std::min(std::min(v0.x,v1.x),v2.x);
		min.y = std::min(std::min(v0.y,v1.y),v2.y);
		min.z = std::min(std::min(v0.z,v1.z),v2.z);

		this->aabbox = new AABBox(min,max);
	}

	return this->aabbox;
}
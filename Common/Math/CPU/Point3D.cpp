///////////////////////////////////////////////////////////////////////////////
//	File:    Point3D.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "Point3D.h"
#include <math.h>


Point3D::Point3D()
{
}

Point3D::Point3D(float _x,float _y,float _z) : x(_x), y(_y), z(_z)
{
}

Point3D::Point3D(const Point3D& point) : x(point.x), y(point.y), z(point.z)
{
}

float Point3D::distance(const Point3D& p) const 
{
	return (sqrt(
		(x - p.x) * (x - p.x) + 
		(y - p.y) * (y - p.y) + 
		(z - p.z) * (z - p.z)
		));
}

Point3D& Point3D::operator= (const Point3D& rhs) 
{
	
	if (this == &rhs)
		return (*this);

	x = rhs.x; y = rhs.y; z = rhs.z;

	return (*this);
}
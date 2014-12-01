///////////////////////////////////////////////////////////////////////////////
//	File:    Vector3D.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "Vector3D.h"
#include "Point3D.h"
#include "math.h"

Vector3D::Vector3D()
{

}

Vector3D::Vector3D(float _x,float _y,float _z) : x(_x), y(_y), z(_z)
{

}

Vector3D::Vector3D(const Vector3D& vector3f) : x(vector3f.x), y(vector3f.y), z(vector3f.z)
{

}

Vector3D::Vector3D(const Point3D& p) : x(p.x), y(p.y), z(p.z)
{

}

Vector3D& Vector3D::operator= (const Vector3D& rhs)
{
	x = rhs.x; y = rhs.y; z = rhs.z;
	return (*this);
}

void Vector3D::normalize() 
{	
	computeUnitVector(*this);
}

const Vector3D& Vector3D::unit()
{
	return computeUnitVector(*this);
}

const Vector3D& Vector3D::computeUnitVector(Vector3D& vector)
{
	float length = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	vector.x /= length; vector.y /= length; vector.z /= length;
	return (vector);
}

Vector3D operator* (const Matrix& mat, const Vector3D& v) 
{
	return (Point3D(mat.m[0][0] * v.x + mat.m[0][1] * v.y + mat.m[0][2] * v.z,
					mat.m[1][0] * v.x + mat.m[1][1] * v.y + mat.m[1][2] * v.z,
					mat.m[2][0] * v.x + mat.m[2][1] * v.y + mat.m[2][2] * v.z));
}
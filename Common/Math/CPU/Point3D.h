///////////////////////////////////////////////////////////////////////////////
//	File:    Point3D.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __POINT3D__
#define __POINT3D__

#include "ShinyMath.h"
#include "Vector3D.h"

class Point3D
{
public:
	union
	{
		struct
		{
			float x,y,z;
		};
		float axis[3];
	};

public:
	Point3D();
	Point3D(float _x,float _y,float _z);
	Point3D(const Point3D& point);
	float distance(const Point3D& p) const;
	Point3D& operator= (const Point3D& rhs);

	Point3D operator- () const;				    			// unary minus
	Vector3D operator- (const Point3D& p) const;				// vector joining two points
	Point3D operator+ (const Vector3D& v) const;				// addition of a vector				
	Point3D operator- (const Vector3D& v) const;			    // subtraction of a vector		
	Point3D operator* (const float a) const;			    	// multiplication by a float on the right
	float distSquared(const Point3D& p) const;				// square of distance bertween two points
};



// inlined member functions

// -------------------------------------------------------------- operator-
// unary minus

inline Point3D Point3D::operator- () const 
{
	return (Point3D(-x, -y, -z));
}


// -------------------------------------------------------------- operator-
// the vector that joins two points

inline Vector3D Point3D::operator- (const Point3D& p) const 
{
	return (Vector3D(x - p.x,y - p.y,z - p.z));
}


// -------------------------------------------------------------- operator+
// addition of a vector to a point that returns a new point

inline Point3D Point3D::operator+ (const Vector3D& v) const 
{
	return (Point3D(x + v.x, y + v.y, z + v.z));
}


// -------------------------------------------------------------- operator-
// subtraction of a vector from a point that returns a new point

inline Point3D Point3D::operator- (const Vector3D& v) const 
{
	return (Point3D(x - v.x, y - v.y, z - v.z));
}


// -------------------------------------------------------------- operator*
// mutliplication by a float on the right

inline Point3D Point3D::operator* (const float a) const 
{
	return (Point3D(x * a,y * a,z * a));
}


// -------------------------------------------------------------- distSquared
// the square of the distance between the two points as a member function

inline float Point3D::distSquared(const Point3D& p) const 
{

	return (	(x - p.x) * (x - p.x) 
			+ 	(y - p.y) * (y - p.y)
			+	(z - p.z) * (z - p.z) );
}

// inlined non-member function

// -------------------------------------------------------------- operator*
// multiplication by a float on the left

Point3D operator* (float a, const Point3D& p);

inline Point3D operator* (float a, const Point3D& p) 
{
	return (Point3D(a * p.x, a * p.y, a * p.z));
}


// non-inlined non-member function

// -------------------------------------------------------------- operator*
// multiplication by a matrix on the left

Point3D operator* (const Matrix& mat, const Point3D& p);						

#endif

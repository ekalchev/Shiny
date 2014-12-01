///////////////////////////////////////////////////////////////////////////////
//	File:    Vector3D.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __VECTOR3D__
#define __VECTOR3D__

#include "Matrix.h"
#include <math.h>

class Point3D;

class Vector3D
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
	Vector3D();
	Vector3D(float _x,float _y,float _z);
	Vector3D(const Vector3D& vector3f);
	Vector3D(const Point3D& p);

	void normalize() ;
	const Vector3D& unit();

	Vector3D& operator= (const Vector3D& rhs);

	Vector3D operator- (void) const;           			// unary minus							
	float length(void);	                        		// length	
	float lenSquared(void);		                		// square of the length
	Vector3D operator* (const float a) const;	    		// multiplication by a float on the right	
	Vector3D operator/ (const float a) const;				// division by a float
	Vector3D operator+ (const Vector3D& v) const;			// addition
	Vector3D& operator+= (const Vector3D& v);				// compound addition
	Vector3D operator- (const Vector3D& v) const;			// subtraction
	float operator* (const Vector3D& b) const;	    	// dot product							
	Vector3D operator^ (const Vector3D& v) const;			// cross product				
		

private:
	inline static const Vector3D& computeUnitVector(Vector3D& vector);
};

inline float Vector3D::length(void)
{
	return sqrt(x * x + y * y + z * z);
}

inline Vector3D Vector3D::operator- () const 
{
	return (Vector3D(-x, -y, -z));    
}


// ---------------------------------------------------------------------  len_squared
// the square of the length

inline float Vector3D::lenSquared() 
{	
	return (x * x + y * y + z * z);
}


// ----------------------------------------------------------------------- operator*
// multiplication by a float on the right

inline Vector3D Vector3D::operator* (const float a) const 
{	
	return (Vector3D(x * a, y * a, z * a));	
}

// ----------------------------------------------------------------------- operator/
// division by a float

inline Vector3D Vector3D::operator/ (const float a) const 
{	
	return (Vector3D(x / a, y / a, z / a));	
}


// ----------------------------------------------------------------------- operator+
// addition

inline Vector3D Vector3D::operator+ (const Vector3D& v) const 
{
	return (Vector3D(x + v.x, y + v.y, z + v.z));
}


// ----------------------------------------------------------------------- operator-
// subtraction

inline Vector3D Vector3D::operator- (const Vector3D& v) const 
{
	return (Vector3D(x - v.x, y - v.y, z - v.z));
}


// ----------------------------------------------------------------------- operator*
// dot product

inline float Vector3D::operator* (const Vector3D& v) const 
{
	return (x * v.x + y * v.y + z * v.z);
} 


// ----------------------------------------------------------------------- operator^
// cross product

inline Vector3D Vector3D::operator^ (const Vector3D& v) const 
{
	return (Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x));
}


// ---------------------------------------------------------------------  operator+=
// compound addition

inline Vector3D& Vector3D::operator+= (const Vector3D& v) 
{
	x += v.x; y += v.y; z += v.z;
	return (*this);
}




// inlined non-member function

// ----------------------------------------------------------------------- operator*
// multiplication by a float on the left

Vector3D operator* (const float a, const Vector3D& v);

inline Vector3D operator* (const float a, const Vector3D& v) 
{
	return (Vector3D(a * v.x, a * v.y, a * v.z));	
}



// non-inlined non-member function

// ----------------------------------------------------------------------- operator* 
// multiplication by a matrix on the left

Vector3D operator* (const Matrix& mat, const Vector3D& v);

#endif
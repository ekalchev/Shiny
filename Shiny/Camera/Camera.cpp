///////////////////////////////////////////////////////////////////////////////
//	File:    Camera.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "Camera.h"

Camera::Camera()		
	:	eye(0, 0, 500),
		lookAt(0,0,0),
		ra(0),
		up(0, 1, 0),
		u(1, 0, 0),
		v(0, 1, 0),
		w(0, 0, 1),
		exposureTime(1.0f)
{
}


// ----------------------------------------------------------------- copy constructor

Camera::Camera(const Camera& c)   		
	: 	eye(c.eye),
		lookAt(c.lookAt),
		ra(c.ra),
		up(c.up),
		u(c.u),
		v(c.v),
		w(c.w),
		exposureTime(c.exposureTime)
{
}

Camera::~Camera()
{
}

void Camera::computeUVW()
{
	w = eye - lookAt;
	w.normalize();
	u = up ^ w;
	u.normalize();
	v = w ^ u;

	// take care of the singularity by hardwiring in specific camera orientations
	
	if (eye.x == lookAt.x && eye.z == lookAt.z && eye.y > lookAt.y) 
	{ 
		// camera looking vertically down
		u = Vector3D(0, 0, 1);
		v = Vector3D(1, 0, 0);
		w = Vector3D(0, 1, 0);	
	}
	
	if (eye.x == lookAt.x && eye.z == lookAt.z && eye.y < lookAt.y) 
	{ 
		// camera looking vertically up
		u = Vector3D(1, 0, 0);
		v = Vector3D(0, 0, 1);
		w = Vector3D(0, -1, 0);
	}
}

void Camera::setEye(const Point3D& p)
{
	eye = p;
	computeUVW();
}

void Camera::setLookAt(const Point3D& p)
{
	lookAt = p;
	computeUVW();
}

void Camera::setRollAngle(float angle)
{
	ra = angle;
}
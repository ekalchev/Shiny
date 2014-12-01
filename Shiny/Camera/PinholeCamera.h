///////////////////////////////////////////////////////////////////////////////
//	File:    PinholeCamera.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __PINHOLECAMERA__
#define __PINHOLECAMERA__

#include "Camera.h"
class Vector3D;


class PinholeCamera : public Camera
{
private:
	float	distance;// view plane distance
	float	zoom;	 // zoom factor
	ViewPane* viewPane;
	const World* pWorld;

public:
	PinholeCamera();
	~PinholeCamera();
	virtual void render(const World& w,ViewPane& vPane);
	void RayCast(int px,int py,int width,int height);
	void setViewDistance(float dist);
private:
	Vector3D GetDirection(const Point3D& p) const; 
};

inline void PinholeCamera::setViewDistance(float dist)
{
	distance = dist;
}

#endif
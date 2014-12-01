///////////////////////////////////////////////////////////////////////////////
//	File:    Camera.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __CAMERA__
#define __CAMERA__

#include "Vector3D.h"
#include "Point3D.h"

class ViewPane;
class World;

class Camera
{
public:
	Point3D eye;
	Point3D lookAt;
	Vector3D up;
	Vector3D u,v,w;
	float exposureTime;
	float ra;

public:
	Camera();
	Camera(const Camera& c);
	virtual ~Camera();
	void setEye(const Point3D& p);
	void setLookAt(const Point3D& p);
	void setRollAngle(float angle);
	virtual void render(const World& w,ViewPane& viewPane) = 0;
	void computeUVW();

private:
	
};

#endif
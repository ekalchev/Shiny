///////////////////////////////////////////////////////////////////////////////
//	File:    ShadeRec.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __SHADEREC__
#define __SHADEREC__

#include "ShinyMath.h"
#include "Ray.h"

class Point3D;
class World;
class Material;

class ShadeRec
{
public:
	float fDistance;
	int nColor;
	int bHitAnObject;
	Ray ray;
	Point3D hitPoint;
	World*	pWorld;
	Vector3D normal;
	Material* pMaterial;
	int nDepth;
public:
	ShadeRec();
	ShadeRec(World* world);
};

#endif
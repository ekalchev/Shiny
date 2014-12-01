///////////////////////////////////////////////////////////////////////////////
//	File:    AABBox.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "AABBox.h"
#include <algorithm>
#include <math.h>
#include <float.h>
#include <algorithm>

#define EPSILON 0.000001f
#define WORLD_BOUNDS_MAX 100000.f
#define WORLD_BOUNDS_MIN -100000.f

AABBox::AABBox(const Point3D& pmin,const Point3D& pmax)
{
	min = pmin;
	max = pmax;
}

AABBox* AABBox::Union(const AABBox* a,const AABBox* b)
{
	AABBox* result;
	Point3D pmin,pmax;

#ifdef _DEBUG
	if(a == NULL && b == NULL)
	{
		assert(false);
	}
#endif

	if(a != NULL && b != NULL)
	{
		pmax.x = std::max(a->max.x,b->max.x);
		pmax.y = std::max(a->max.y,b->max.y);
		pmax.z = std::max(a->max.z,b->max.z);

		pmin.x = std::min(a->min.x,b->min.x);
		pmin.y = std::min(a->min.y,b->min.y);
		pmin.z = std::min(a->min.z,b->min.z);
	
		result = new AABBox(pmin,pmax);
	}
	else if(a == NULL)
	{
		result = new AABBox(b->min,b->max);
	}
	else if(b == NULL)
	{
		result = new AABBox(a->min,a->max);
	}

	return result;
}

int AABBox::IntersectRay(const Ray& ray,float& tmin, float& tmax)
{
	tmin = 0.0f;
	tmax = FLT_MAX;

	for(int i = 0; i < 3; ++i)
	{
		if(abs(ray.d.axis[i]) < EPSILON)
		{
			if(ray.o.axis[i] < min.axis[i] || ray.o.axis[i] > max.axis[i])
			{
				return 0;
			}
		}
		else
		{
			float ood = 1.0f / ray.d.axis[i];
			float t1 = (min.axis[i] - ray.o.axis[i]) * ood;
			float t2 = (max.axis[i] - ray.o.axis[i]) * ood;

			if(t1 > t2)
			{
				float temp = t1;
				t1 = t2;
				t2 = temp;
			}

			tmin = std::max(tmin,t1);
			tmax = std::min(tmax,t2);

			if(tmin > tmax)
			{
				return 0;
			}
		}
	}

	return 1;
}

void AABBox::LimitBounds(AABBox* a)
{
	a->max.x = std::min(a->max.x,WORLD_BOUNDS_MAX);
	a->max.y = std::min(a->max.y,WORLD_BOUNDS_MAX);
	a->max.z = std::min(a->max.z,WORLD_BOUNDS_MAX);

	a->min.x = std::max(a->min.x,WORLD_BOUNDS_MIN);
	a->min.y = std::max(a->min.y,WORLD_BOUNDS_MIN);
	a->min.z = std::max(a->min.z,WORLD_BOUNDS_MIN);
}



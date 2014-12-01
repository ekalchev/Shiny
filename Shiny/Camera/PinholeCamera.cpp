///////////////////////////////////////////////////////////////////////////////
//	File:    PinholeCamera.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////



#include "stdafx.h"
#include "PinholeCamera.h"
#include "World.h"
#include "ShinyMath.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "ViewPane.h"
#include "GeoObject.h"
#include "TaskManager.h"
#include "PinholeCameraRenderTask.h"
#include "SingleLock.h"
#include "Tracer.h"




PinholeCamera::PinholeCamera() : distance(500),zoom(1.0)
{
	
}

PinholeCamera::~PinholeCamera()
{
	
}


void PinholeCamera::render(const World& w,ViewPane& vPane)
{
	viewPane = &vPane;
	pWorld = &w;
	TaskManager& taskManager = *TaskManager::getInstance();
	PinholeCameraRenderTask* task[NUM_TASKS];

	int renderWindowHeight = viewPane->getHeight() / NUM_TASKS;
	int renderWindowY = 0;

	for(int i = 0; i < NUM_TASKS; ++i)
	{
		task[i] = new PinholeCameraRenderTask(this,0,renderWindowY,viewPane->getWidth(),renderWindowHeight);
		renderWindowY += renderWindowHeight;
		taskManager.addTask(task[i]);
	}
	
	taskManager.StartTasks();
	taskManager.WaitForAllTasks();
	taskManager.clearTasks();
}

Vector3D PinholeCamera::GetDirection(const Point3D& p) const 
{
	Vector3D dir = p.x * u - p.y * v - distance * w;
	dir.normalize();
	
	return(dir);
}

void PinholeCamera::RayCast(int px,int py,int width,int height)
{	
	////////////////////////////
	Ray ray;
	float		s		= 1;
	float		zw		= 100.0; // hardwired in
	float		tmin    = 1.0E10;
	Point3D		localCoordsPoint;
	int			vPaneWidth = viewPane->getWidth();
	int			vPaneHeight = viewPane->getHeight();
	RGBColor	L;
	int n = NUM_SAMPLES;
	

	vector<GeoObject*>	objects = pWorld->GetWorldObjects();
	vector<GeoObject*>::iterator iter;

	ray.o = eye;
	for (int y = py; y < (py + height); y++) 
	{	
		for (int x = px; x < (px + width); x++)		
		{
			L = black;
			for (int p = 0; p < n; p++)
			{ 
				for (int q = 0; q < n; q++) 
				{
					localCoordsPoint.x = s * (x - vPaneWidth * 0.5 + (p + 0.5) / n);
					localCoordsPoint.y = s * (y - vPaneHeight * 0.5 + (q + 0.5) / n);
					ray.d = GetDirection(localCoordsPoint);
					L += pWorld->pTracer->TraceRay(ray);
				}	
			}

			//L.r == 0.0f && L.g == 0.0f && L.b == 0.0f
			L /= n*n;
			viewPane->SetPixel(x,y,L);
		}	
	}
}
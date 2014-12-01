///////////////////////////////////////////////////////////////////////////////
//	File:    PinholeCameraRenderTask.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PinholeCameraRenderTask.h"
#include "PinholeCamera.h"

PinholeCameraRenderTask::PinholeCameraRenderTask(PinholeCamera* pinholeCamera,int x,int y,int width,int height)
{
	this->camera = pinholeCamera;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

PinholeCameraRenderTask::~PinholeCameraRenderTask()
{

}

void PinholeCameraRenderTask::Do()
{
	camera->RayCast(x,y,width,height);
}
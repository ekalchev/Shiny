///////////////////////////////////////////////////////////////////////////////
//	File:    PinholeCameraRenderTask.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __RENDERTASK__
#define __RENDERTASK__

class PinholeCamera;

#include <Task.h>

class PinholeCameraRenderTask : public Task
{
private:
	PinholeCamera* camera;
	int x,y;
	int width,height;
public:
	PinholeCameraRenderTask(PinholeCamera* pinholeCamera,int x,int y,int width,int height);
	~PinholeCameraRenderTask();
	virtual void Do();
};
#endif
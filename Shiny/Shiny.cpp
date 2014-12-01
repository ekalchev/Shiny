///////////////////////////////////////////////////////////////////////////////
//	File:    Shiny.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "Shiny.h"
#include "ViewPane.h"
#include "World.h"
#include "Timer.h"
#include "TaskManager.h"
#include "Mesh.h"


Shiny::Shiny(int width,int height)
{
	viewPane = new ViewPane(width,height);
	world = new World();
	world->build();
}

Shiny::~Shiny()
{
	delete viewPane;
	delete world;

	TaskManager::DestroySingleton();
}

void Shiny::render()
{
	Timer timer;
	assert(viewPane != NULL);
	assert(world != NULL);
	timer.StartCounter();
	world->render(*viewPane);
	timer.StopCounter();
	renderTime = timer.GetTimeDiff();
}

void* Shiny::getFrameBuffer()
{
	return viewPane->getBuffer();
}

double Shiny::getRenderTime()
{
	return renderTime;
}
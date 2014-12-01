///////////////////////////////////////////////////////////////////////////////
//	File:    GeoObject.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "GeoObject.h"
#include <string>
#include <Logger.h>

using namespace std;

GeoObject::GeoObject() : pMaterial(NULL),epsilon(DEFAULT_EPSILON)
{
	aabbox = NULL;
}

GeoObject::~GeoObject()
{
	if(aabbox != NULL)
	{
		delete aabbox;
	}
}

AABBox* GeoObject::GetAABBox()
{
	string message;
	message.append("GetAABBox() is not implemented for object ");
	message.append(typeid(*this).name());
	Logger::Log(message.c_str());
	assert(false && "GetAABBox() is not implemented for this object");
	return NULL;
}
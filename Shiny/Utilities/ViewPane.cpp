///////////////////////////////////////////////////////////////////////////////
//	File:    ViewPane.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ViewPane.h"
#include <memory.h>

#define DEFAULT_RESX		 640
#define DEFAULT_RESY		 480
#define DEFAULT_PIXELSIZE	   1 //this is not color bits

ViewPane::ViewPane() : nWidth(DEFAULT_RESX), nHeight(DEFAULT_RESY), nPixelSize(DEFAULT_PIXELSIZE)
{
	allocateViewBuffer();
}

ViewPane::ViewPane(int _width,int _height,int _pixelSize) : nWidth(_width), nHeight(_height), nPixelSize(_pixelSize)
{
	allocateViewBuffer();
}

ViewPane::~ViewPane()
{
	delete[] pBuff;
}

void ViewPane::allocateViewBuffer()
{
	pBuff = new int[nWidth*nHeight];
}

void* ViewPane::getBuffer()
{
	return pBuff;
}

void ViewPane::clearBuffer(int color)
{
	assert(pBuff != NULL);
	memset(pBuff,0,nWidth*nHeight*sizeof(int));
}
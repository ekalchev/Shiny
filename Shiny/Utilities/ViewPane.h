///////////////////////////////////////////////////////////////////////////////
//	File:    ViewPane.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __VIEWPANE__
#define __VIEWPANE__

#include "RGBColor.h"

using namespace std;

class ViewPane 
{
private:
	int nWidth;
	int nHeight;
	int nPixelSize;
	int* pBuff;
	static const int nBytesPerPixel = 4; // 32 bit per pixel

public:
	ViewPane();
	ViewPane(int _width,int _height,int _pixelSize = 1);
	~ViewPane();

	int getWidth() const { return nWidth; }
	int getHeight() const { return nHeight; }

	void* getBuffer();
	void clearBuffer(int color);
	void SetPixel(int x,int y,int color);
	void SetPixel(int x,int y,RGBColor& color);

private: 
	void allocateViewBuffer();
};

inline void ViewPane::SetPixel(int x,int y,int color)
{
	assert(x < nWidth);
	assert(y < nHeight);
	pBuff[y*nWidth + x] = color;
}

inline void ViewPane::SetPixel(int x,int y,RGBColor& color)
{
	assert(x < nWidth);
	assert(y < nHeight);
	float fMaxValue = max(color.r, max(color.g, color.b));
	
	if (fMaxValue > 1.0)
		color /= fMaxValue;

	int nColor = color.ToInt();
	pBuff[y*nWidth + x] = nColor;
}

#endif

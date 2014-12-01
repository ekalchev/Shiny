///////////////////////////////////////////////////////////////////////////////
//	File:    Utils.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////

#ifndef __UTILS__
#define __UTILS__

#include "RGBColor.h"
using namespace std;

class Utils
{
public:
	static void MaxToOne(RGBColor* color);
};

inline void Utils::MaxToOne(RGBColor* color)
{
	float fMaxValue = max(color->r, max(color->g, color->b));
	
	if (fMaxValue > 1.0)
		*color /= fMaxValue;
}

#endif
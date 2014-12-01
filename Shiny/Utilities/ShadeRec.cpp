///////////////////////////////////////////////////////////////////////////////
//	File:    ShadeRec.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "ShadeRec.h"


ShadeRec::ShadeRec() : bHitAnObject(false),nDepth(0),fDistance(kHugeValue)
{
}

ShadeRec::ShadeRec(World* world) : bHitAnObject(false),pWorld(world),nDepth(0),fDistance(kHugeValue)
{
}
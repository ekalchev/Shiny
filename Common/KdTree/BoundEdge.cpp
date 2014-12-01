///////////////////////////////////////////////////////////////////////////////
//	File:    BoundEdge.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "BoundEdge.h"


BoundEdge::BoundEdge()
{
}

BoundEdge::BoundEdge(float tt, int pn, bool starting)
{
	t = tt;
	primNum = pn;
	type = starting ? START : END;
}

bool BoundEdge::operator<(const BoundEdge &e) const
{
	if(t == e.t)
	{
		return (int)type < (int)e.type;
	}
	else
	{
		return t < e.t;
	}
}
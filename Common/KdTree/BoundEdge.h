///////////////////////////////////////////////////////////////////////////////
//	File:    BoundEdge.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////



#ifndef __BOUNDEDGE__
#define __BOUNDEDGE__

class BoundEdge
{
public:
	float t;
	int primNum;
	enum
	{
		START,
		END
	} type;
public:
	BoundEdge();
	BoundEdge(float tt, int pn, bool starting);
	bool operator<(const BoundEdge &e) const;
};
#endif




































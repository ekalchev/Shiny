  ///////////////////////////////////////////////////////////////////////////////
//	File:    KdTreeNode.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __KDTREENODE__
#define __KDTREENODE__

#include <SlabAllocator.h>
#include "MailboxPrim.h"


template <class Primitive> 
class KdTreeNode
{

private:
	union
	{
		int flags;
		float split;
		int nPrims;
	};

public:
	union
	{
		int aboveChild;
		MailboxPrim<Primitive>* onePrimitive;
		MailboxPrim<Primitive>** primitives;
	};

public:
	void InitLeaf(int *primNums, int np, MailboxPrim<Primitive>* prims, SlabAllocator& memoryManager);
	void InitInterior(int axis, float s);
	float SplitPos() const { return split; }
	int NumPrimitives() const { return nPrims >> 2; }
	int SplitAxis() const { return flags & 3; }
	bool IsLeaf() const { return (flags & 3) == 3; }
};


template <class Primitive>
void KdTreeNode<Primitive>::InitLeaf(int *primNums, int np, MailboxPrim<Primitive>* prims, SlabAllocator& memoryManager)
{
	nPrims = np << 2;
	flags |= 3;

	if(np == 0)
	{
		this->onePrimitive = NULL;
	}
	else if(np == 1)
	{
		this->onePrimitive = &prims[primNums[0]];
	}
	else
	{
		primitives = (MailboxPrim<Primitive>**)memoryManager.Alloc(np * sizeof(Primitive*));
		for(int i = 0; i < np; ++i)
		{
			primitives[i] = &prims[primNums[i]];
		}
	}
}

template <class Primitive>
void KdTreeNode<Primitive>::InitInterior(int axis, float s)
{
	split = s;
	flags &= ~3;
	flags |= axis;
}

#endif
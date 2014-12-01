///////////////////////////////////////////////////////////////////////////////
//	File:    KdTree.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////



#ifndef __KDTREE__
#define __KDTREE__

#include <vector>
#include "KdTreeNode.h"
#include <SlabAllocator.h>
#include "KdTree.h"
#include <AABBox.h>
#include <math.h>
#include "KdTreeNode.h"
#include <malloc.h>
#include "BoundEdge.h"
#include <Point3D.h>
#include <Vector3D.h>
#include <algorithm>
#include <Mem.h>
#include <float.h>
#include <GlobalDefs.h>

#define MAX_PRIMS 3
#define EMPTY_BONUS -1.0f
#define MAX_TODO 64


template<class Primitive,class PrimitiveAdapter,class Intersection>
class KdTree
{
private:
	template<class Prim>
	struct KdToDo
	{
		const KdTreeNode<Prim> *node;
		float tmin, tmax;
	};

	enum E_SPLITING_AXIS
	{
		E_AXIS_X = 0,
		E_AXIS_Y = 1,
		E_AXIS_Z = 2,
	};

public:
	enum E_KDTREE_THREADING
	{
		SINGLE_THREADED = 0,
		MULTI_THREADED = 1
	};

	KdTreeNode<Primitive> *nodes;
	int nNextFreeNode;
	int nAllocatedNodes;
	int nMaxDepth;
	SlabAllocator memoryAllocator;
	AABBox *bounds;
	int maxPrims;
	vector<Primitive*>& prims;
	unsigned int nMailboxes;
	MailboxPrim<Primitive> *mailboxPrims;
	int maxDepth, traversalCost;
	mutable int nCurMailboxId;
	int multiThreaded;
	PrimitiveAdapter primitiveAdapter;

#ifdef _DEBUG
	static int numNodes;
	static int numLeafNodes;
	static int numInteriorNodes;
#endif

public:
	KdTree(vector<Primitive*>& objects,int mt);
	~KdTree();
	void Build();
	bool Intersect(const Ray& ray,Intersection* isect) const;
private:
	void BuildTreeRC(int nodeNum, const AABBox& nodeBounds, const vector<AABBox>& allPrimBounds,
		int* primNums, int nPrims, int depth, BoundEdge* edge[3], int* prims0, int* prims1, int badRefines = 0);

	bool CheckOnePrimitive(MailboxPrim<Primitive> *prim,Ray& ray);
};

//static member initialization

#ifdef _DEBUG
template<class Primitive,class PrimitiveAdapter,class Intersection>
int KdTree<Primitive,PrimitiveAdapter,Intersection>::numNodes = 0;

template<class Primitive,class PrimitiveAdapter,class Intersection>
int KdTree<Primitive,PrimitiveAdapter,Intersection>::numLeafNodes = 0;

template<class Primitive,class PrimitiveAdapter,class Intersection>
int KdTree<Primitive,PrimitiveAdapter,Intersection>::numInteriorNodes = 0;
#endif


template<class Primitive,class PrimitiveAdapter,class Intersection>
KdTree<Primitive,PrimitiveAdapter,Intersection>::KdTree(vector<Primitive*>& objects,int mt) : prims(objects),nCurMailboxId(0),multiThreaded(mt)
{
	bounds = NULL;
	maxPrims = MAX_PRIMS;
	nMailboxes = (unsigned int)prims.size();
	mailboxPrims = (MailboxPrim<Primitive> *)Mem::AllocAligned(nMailboxes * sizeof(MailboxPrim<Primitive>));
	maxDepth = -1;
	traversalCost = 1;

	for (unsigned int i = 0; i < nMailboxes; ++i)
	{
		new (&mailboxPrims[i]) MailboxPrim<Primitive>(prims[i]);
	}
}

template<class Primitive,class PrimitiveAdapter,class Intersection>
KdTree<Primitive,PrimitiveAdapter,Intersection>::~KdTree()
{
	if(bounds != NULL)
	{
		delete bounds;
	}

	for (unsigned int i = 0; i < nMailboxes; ++i)
	{
		mailboxPrims[i].~MailboxPrim<Primitive>();
	}

	Mem::FreeAligned(mailboxPrims);
	Mem::FreeAligned(nodes);
}

template<class Primitive,class PrimitiveAdapter,class Intersection>
void KdTree<Primitive,PrimitiveAdapter,Intersection>::Build()
{
	AABBox* oldBounds;

	nNextFreeNode = nAllocatedNodes = 0;
	if(maxDepth <= 0)
	{
		maxDepth = (int)(8 + 1.3f * log((double)prims.size()) + 0.5f);
	}

	vector<AABBox> primBounds;
	primBounds.reserve(prims.size());
	for(unsigned int i = 0; i < prims.size(); ++i)
	{
		AABBox* aabbox = primitiveAdapter.GetAABBox(prims[i]);
		
		oldBounds = bounds;
		bounds = AABBox::Union(bounds,aabbox);

		if(oldBounds != NULL)
		{
			delete oldBounds;
		}

		primBounds.push_back(*aabbox);
	}

	BoundEdge *edges[3];

	for(int i = 0; i < 3; ++i)
	{
		edges[i] = new BoundEdge[2*prims.size()];
	}

	int *prims0 = new int[prims.size()];
	int *prims1 = new int[(maxDepth + 1) * prims.size()];

	int *primNums = new int[prims.size()];
	for(unsigned int i = 0; i < prims.size(); ++i)
	{
		primNums[i] = i;
	}

	BuildTreeRC(0, *bounds, primBounds, primNums, prims.size(), maxDepth, edges, prims0, prims1);

	//---------------- END OF RECURSION--------------
	for(int i = 0; i < 3; ++i)
	{
		delete[] edges[i];
	}

	delete[] prims0;
	delete[] prims1;
	delete[] primNums;
}

template<class Primitive,class PrimitiveAdapter,class Intersection>
void KdTree<Primitive,PrimitiveAdapter,Intersection>::BuildTreeRC(int nodeNum, const AABBox& nodeBounds, const vector<AABBox>& allPrimBounds,
		int* primNums, int nPrims, int depth, BoundEdge* edges[3], int* prims0, int* prims1, int badRefines)
{
	if(nNextFreeNode == nAllocatedNodes)
	{
		int nAlloc = max(2 * nAllocatedNodes,512);
		KdTreeNode<Primitive>* n = (KdTreeNode<Primitive>*)malloc(nAlloc*sizeof(KdTreeNode<Primitive>));

		if(nAllocatedNodes > 0)
		{
			memcpy(n, nodes,nAllocatedNodes * sizeof(KdTreeNode<Primitive>));
			free(nodes);
		}

		nodes = n;
		nAllocatedNodes = nAlloc;
	}

	++nNextFreeNode;

	if(nPrims <= maxPrims || depth == 0)
	{
#ifdef _DEBUG
			numLeafNodes++;
			numNodes++;
#endif
		nodes[nodeNum].InitLeaf(primNums,nPrims, mailboxPrims, memoryAllocator);
		return; //exit from recursion
	}

	int isectCost = 1; // this is value indicating the cost for finding collision with primitives in the node
	int bestAxis = -1;
	int bestOffset = -1;
	float bestCost = FLT_MAX;
	float oldCost = isectCost * (float)nPrims;
	Vector3D d = nodeBounds.max - nodeBounds.min;
	float totalSA = (2.0f * (d.x*d.y + d.x*d.z + d.y*d.z));
	float invTotalSA = 1.0f / totalSA;
	
	//choose axis to split along

	int axis;
	if(d.x > d.y && d.x > d.z)
	{
		axis = E_AXIS_X;
	}
	else
	{
		axis = (d.y > d.z) ? E_AXIS_Y : E_AXIS_Z;
	}

	int nBelow = 0,nAbove = nPrims;
	int retries = 0;
//WARNING WARNING !!!! :)
retrySplit:

	//initialize edges for axis

	for(int i = 0; i < nPrims; ++i)
	{
		int pn = primNums[i];
		const AABBox* aabbox = &(allPrimBounds[pn]);
		edges[axis][2*i] = BoundEdge((float)aabbox->min.axis[axis],pn,true);
		edges[axis][2*i + 1] = BoundEdge((float)aabbox->max.axis[axis],pn,false);
	}

	sort(&edges[axis][0], &edges[axis][2*nPrims]);

	for(int i = 0;i < 2*nPrims; ++i)
	{
		if(edges[axis][i].type == BoundEdge::END)
		{
			--nAbove;
		}

		float edget = edges[axis][i].t;
		if(edget > nodeBounds.min.axis[axis] && edget < nodeBounds.max.axis[axis])
		{
			//compute cost for split
			int otherAxis[3][2] = { {1,2}, {0,2}, {0,1} };
			int otherAxis0 = otherAxis[axis][0];
			int otherAxis1 = otherAxis[axis][1];

			float belowSA = 2 * (d.axis[otherAxis0] * d.axis[otherAxis1] +
				(edget - nodeBounds.min.axis[axis]) *
				(d.axis[otherAxis0] + d.axis[otherAxis1]));

			float aboveSA = 2 * (d.axis[otherAxis0] * d.axis[otherAxis1] +
				(nodeBounds.max.axis[axis] - edget) *
				(d.axis[otherAxis0] + d.axis[otherAxis1]));

			float pBelow = belowSA * invTotalSA;
			float pAbove = aboveSA * invTotalSA;

			float emptyBonus = (nAbove == 0 || nBelow == 0) ? EMPTY_BONUS : 0.0f;

			float cost = traversalCost + isectCost * (1.0f - emptyBonus) * (pBelow * nBelow + pAbove * nAbove);

			if(cost < bestCost)
			{
				bestCost = cost;
				bestAxis = axis;
				bestOffset = i;
			}
		}
		
		if(edges[axis][i].type == BoundEdge::START)
		{
			++nBelow;
		}
	}

		if(bestAxis == -1 && retries < 2)
		{
			++retries;
			axis = (axis + 1) % 3;
			//TODO: get rid of this
			goto retrySplit;
		}

		if(bestCost > oldCost)
		{
			++badRefines;
		}

		if(( (bestCost > 4.0f * oldCost) && (nPrims < 16) || 
			bestAxis == -1 || badRefines == 3))
		{

#ifdef _DEBUG
			numLeafNodes++;
			numNodes++;
#endif
			nodes[nodeNum].InitLeaf(primNums, nPrims, mailboxPrims, memoryAllocator);
			return;
		}

		int n0 = 0, n1 = 0;
		for(int i = 0; i < bestOffset; ++i)
		{
			if(edges[bestAxis][i].type == BoundEdge::START)
			{
				prims0[n0++] = edges[bestAxis][i].primNum;
			}
		}

		for(int i = bestOffset+1; i < 2*nPrims; ++i)
		{
			if(edges[bestAxis][i].type == BoundEdge::END)
			{
				prims1[n1++] = edges[bestAxis][i].primNum;
			}
		}

		//recursively initialize children nodes
		float tsplit = edges[bestAxis][bestOffset].t;
		//if(tsplit == 0.0f) tsplit = 0.1f;

		nodes[nodeNum].InitInterior(bestAxis,tsplit);
#ifdef _DEBUG
		numInteriorNodes++;
		numNodes++;
#endif
		AABBox bounds0 = nodeBounds, bounds1 = nodeBounds;
		bounds0.max.axis[bestAxis] = bounds1.min.axis[bestAxis] = tsplit;

		BuildTreeRC(nodeNum + 1,bounds0, allPrimBounds, prims0, n0, depth - 1, edges, prims0, prims1 + nPrims, badRefines);
		nodes[nodeNum].aboveChild = nNextFreeNode;
		BuildTreeRC(nodes[nodeNum].aboveChild, bounds1, allPrimBounds, prims1, n1, depth - 1, edges, prims0, prims1 + nPrims, badRefines);
}

template<class Primitive,class PrimitiveAdapter,class Intersection>
bool KdTree<Primitive,PrimitiveAdapter,Intersection>::Intersect(const Ray& ray,Intersection* isect) const
{
	float tmin,tmax;

	if(bounds->IntersectRay(ray,tmin,tmax) == 0)
	{
		return false;
	}

	int rayId = nCurMailboxId++;
	Vector3D invDir(1.0f / ray.d.x, 1.0f / ray.d.y, 1.0f / ray.d.z);
	
	KdToDo<Primitive> todo[MAX_TODO];
	int todoPos = 0;

	bool hit = false;
	const KdTreeNode<Primitive> *node = &nodes[0];

	Intersection *isectIn,*isectOut;
	isectIn = isect;
	isectOut = &Intersection();
	while(node != NULL)
	{
		if(primitiveAdapter.GetDistance(isectOut) < tmin)
		{
			*isect = *isectOut;
			break;
		}

		if(node->IsLeaf())
		{
			int nPrimitives = node->NumPrimitives();

			if(nPrimitives == 1)
			{
				MailboxPrim<Primitive> *mp = node->onePrimitive;
				if(primitiveAdapter.Intersect(mp->primitive,ray,isectIn,isectOut) == true)
				{
					hit = primitiveAdapter.HitAnObject(isectOut);
				}				
			}
			else
			{
				
				MailboxPrim<Primitive> **prims = node->primitives;
				MailboxPrim<Primitive> *mp;
				 
				for(int i = 0; i < nPrimitives; ++i)
				{
					mp = prims[i];
					if(primitiveAdapter.Intersect(mp->primitive,ray,isectIn,isectOut) == true)
					{
						isectIn = isectOut;
					}
				}
				
				hit = primitiveAdapter.HitAnObject(isectOut);
				
			}

			if(todoPos > 0)
			{
				--todoPos;
				node = todo[todoPos].node;
				tmin = todo[todoPos].tmin;
				tmax = todo[todoPos].tmax;
			}
			else
			{
				if(isectOut != NULL)
				{
					*isect = *isectOut;
				}
				break;
			}
		}
		else
		{
			int axis = node->SplitAxis();
			float tsplit = (node->SplitPos() - ray.o.axis[axis]) * invDir.axis[axis];
			const KdTreeNode<Primitive> *firstChild, *secondChild;
			int belowFirst = ray.o.axis[axis] <= node->SplitPos();

			if(belowFirst)
			{
				firstChild = node + 1;
				secondChild = &nodes[node->aboveChild];
			}
			else
			{
				firstChild = &nodes[node->aboveChild];
				secondChild = node + 1;
			}

			if(tsplit == 0.0f)
			{
				node = firstChild;
				//add to todo list
				todo[todoPos].node = secondChild;
				todo[todoPos].tmin = tmin;
				todo[todoPos].tmax = tmax;
				++todoPos;
			}
			else
			{
				if(tsplit > tmax || tsplit < 0.0f)
				{
					node = firstChild;
				}
				else if(tsplit < tmin)
				{
					node = secondChild;
				}
				else
				{
					//add to todo list
					todo[todoPos].node = secondChild;
					todo[todoPos].tmin = tsplit;
					todo[todoPos].tmax = tmax;
					++todoPos;

					node = firstChild;
					tmax = tsplit;
				}
			}
		}
	}

	return hit;

}

#endif
///////////////////////////////////////////////////////////////////////////////
//	File:    PlyLoader.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __PLYLOADER__
#define __PLYLOADER__

#include <stdio.h>
class Vertex;

class PlyLoader
{
private:
	struct PlyVertex
	{
		double x,y,z;
		double nx,ny,nz;
		void *other_props;
	};

	struct PlyFace 
	{
		unsigned char nverts;    /* number of vertex indices in list */
		int *verts;              /* vertex index list */
		void *other_props;       /* other properties */
	};

	PlyLoader();
public:
	static bool Load(FILE *fp,Vertex**& vList,unsigned int &numVertices,int*& indicesList,unsigned int &numIndices);
	
};

#endif
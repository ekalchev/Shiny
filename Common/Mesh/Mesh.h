///////////////////////////////////////////////////////////////////////////////
//	File:    Mesh.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////



#ifndef __MESH__
#define __MESH__


#include <string>
class Vertex;

using namespace std;

class Mesh
{
public:
	Vertex** vertexList;
	unsigned int numVertices;
	int* indicesList;
	unsigned int numIndices;
private:
	bool FileFormat(string filename,string fileExtension);
public:
	Mesh();
	Mesh(Vertex** vList,int nVertices);
	bool LoadFromFile(string filename);
	virtual ~Mesh();
};

#endif